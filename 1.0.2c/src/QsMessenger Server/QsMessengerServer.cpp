/*   Qs Messenger Server v 1.0.2c Instant Messaging Application
     Copyright (C) 2026  Radu G. Balaban G.

     This program is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program.  If not, see <https://www.gnu.org/licenses/>. */


#include "QsMessengerServer.h"

#include <QtNetwork/QSslCertificate>
#include <QRegularExpressionMatch>
#include <QFileSystemWatcher>
#include <QRegularExpression>
#include <QtNetwork/QSslKey>
#include <QtWebSockets>
#include <QtCore/QFile>
#include <QProcess>
#include <client.h>
#include <QRegExp>
#include <QTimer>


    // #include <QDebug>


QsMessengerServer::QsMessengerServer(quint16 port, bool log, bool verbose, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(nullptr)
{

    if (log){
        startLogging = true;
    }

    if(verbose){
        startVerbose = true;
    }

    openDataBase();

    clearDatabase();

    //qInfo() << port;




    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("SSL QsMessenger Server"), QWebSocketServer::SecureMode, nullptr);
    QSslConfiguration sslConfiguration;
    QFile certFile("./crt/certificate.crt");
    QFile keyFile("./crt/private.key");

    certFile.open(QIODevice::ReadOnly);
    keyFile.open(QIODevice::ReadOnly);

    QSslCertificate certificate(&certFile, QSsl::Pem);
    QSslKey sslKey(&keyFile, QSsl::Rsa, QSsl::Pem);
    certFile.close();
    keyFile.close();

    sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
    sslConfiguration.setLocalCertificate(certificate);
    sslConfiguration.setPrivateKey(sslKey);
    sslConfiguration.setCaCertificates(QSslCertificate::fromPath("./crt/ca_bundle.crt"));

    m_pWebSocketServer->setSslConfiguration(sslConfiguration);
    m_pWebSocketServer->setServerName("QsMessengerServer");


    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        //QTextStream out(stdout);
        QFile log("logs/QsMessenger.log");
        log.open(QIODevice::Append);
        QTextStream out(&log);

        qInfo() << "QsMessenger Server listening on port SSL:" << QString::number(port);
        out << QDateTime::currentDateTimeUtc().toString() + " QsMessenger Server listening on port SSL:" + QString::number(port) << endl;

        log.close();

        connect(m_pWebSocketServer, &QWebSocketServer::newConnection, this, &QsMessengerServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::sslErrors, this, &QsMessengerServer::onSslErrors);
        connect(m_pWebSocketServer, &QWebSocketServer::acceptError, this, [=](QAbstractSocket::SocketError socketErr){qInfo() << socketErr;} );


    }


    QDir dir("logs");
    if (!dir.exists()){
        QDir().mkpath("./logs/");
    }

    if(startLogging){
        qint64 logName = QDateTime::currentMSecsSinceEpoch();

        logPath = "./logs/";
        logPath += QString::number(logName);
        logPath += ".log";

        QFile logFile(logPath);

        if(logFile.open(QIODevice::WriteOnly | QIODevice::Append)){
        logFile.write("Log Start: \n");
        //logFile.close();
        }
    }

}


QsMessengerServer::~QsMessengerServer()
{
    m_pWebSocketServer->close();
    //logFile.close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}


void QsMessengerServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    m_clients << pSocket;

    QString session_id_code;

    bool uniqueMatch = false;

    while(uniqueMatch != true){



       session_id_code  = "sessionId-" + QString::number(QRandomGenerator::global()->bounded(1000000,10000000));

    bool match = false;

        for(int i=0; i< clients.size(); i++){
            if(clients.at(i)->session_id == session_id_code){
                match = true;
            }

        }

        if(match){

            uniqueMatch = false;

        } else {

            uniqueMatch = true;
        }

    }

    qInfo().noquote() << "client connected: " + pSocket->peerAddress().toString().split(":").last();

    QFile log("logs/QsMessenger.log");
    log.open(QIODevice::Append);
    QTextStream out(&log);

    out << QDateTime::currentDateTimeUtc().toString() + " " + "client connected: " + pSocket->peerAddress().toString().split(":").last() << endl;

    log.close();


    clients_id += 1;



            clients.append(new client(pSocket->peerAddress(), pSocket->peerPort(), session_id_code, clients_id, startVerbose));

            for(int i=0; i< clients.size(); i++){

                if(clients.at(i)->session_id == session_id_code){

                    connect(pSocket, &QWebSocket::textMessageReceived, clients.at(i), &client::process_text_message);
                    connect(pSocket, &QWebSocket::binaryMessageReceived, clients.at(i), &client::process_binary_message);
                    connect(pSocket, &QWebSocket::disconnected, clients.at(i), &client::socket_disconnected);
                    connect(clients.at(i), SIGNAL(emit_close(QString)), this, SLOT(close_client(QString)) );
                    connect(clients.at(i), SIGNAL(emit_logData(QString)), this, SLOT(logData(QString)));
                    connect(clients.at(i), SIGNAL(emit_sendMsg(QString,QString,QString,QString)), this, SLOT(fwMessage(QString,QString,QString,QString)));
                    connect(clients.at(i), SIGNAL(emit_sendFileRequest(QString,QString,QString,QString,QString)), this, SLOT(fwFileRequest(QString,QString,QString,QString,QString)));
                    connect(clients.at(i), SIGNAL(emit_sendFileResponse(QString,QString,QString,QString)), this, SLOT(fwFileResponse(QString,QString,QString,QString)));
                    connect(clients.at(i), SIGNAL(emit_sendFilePayload(QString,QString,QString,QByteArray)), this, SLOT(fwFilePayload(QString,QString,QString,QByteArray)));
                    connect(clients.at(i), SIGNAL(emit_statusUpdate(QString, QStringList)), this, SLOT(updateStatus(QString, QStringList)));
                    connect(clients.at(i), SIGNAL(emit_friendRequest(QString,QString)), this, SLOT(fwFriendRequest(QString,QString)));
                    connect(clients.at(i), SIGNAL(emit_checkSignedIn(QString, QString)), this, SLOT(checkSignedIn(QString,QString)));
                    connect(clients.at(i), SIGNAL(emit_getUniqueLoginToken(QString,QString)),this,SLOT(generateUniqueLoginToken(QString,QString)));
                    connect(clients.at(i), SIGNAL(emit_disconnectOther(QString, QString)), this, SLOT(disconnectOther(QString,QString)));
                    connect(clients.at(i), SIGNAL(emit_acceptedFriendRequest(QString,QString)), this, SLOT(fwAcceptedFriendRequest(QString,QString)));
                    connect(clients.at(i), SIGNAL(emit_removedFromList(QString,QString)), this, SLOT(fwUnfriended(QString,QString)));

                    i=clients.size();
                }

            }


}



void QsMessengerServer::onSslErrors(QList<QSslError> errors)
{
    qInfo() << "Ssl errors occurred";
    for(int i=0; i<errors.size(); i++){
        qInfo() << errors.at(i);
    }
}



void QsMessengerServer::logData(QString data){

    QByteArray wData = (data + "\n").toUtf8();

    QFile logFile(logPath);

    if(openLogOnce == false){


        logFile.open(QIODevice::WriteOnly | QIODevice::Append);
        openLogOnce = true;
    }

    logFile.write(wData);
    //logFile.close();


}



void QsMessengerServer::close_client(QString session_id){
        for (int i = 0; i< clients.size(); i++ ){
            if (clients.at(i)->session_id == session_id){


                delete clients.at(i);
                clients.removeAt(i);


            }
        }
}


void QsMessengerServer::fwMessage(QString senderEmail, QString receiverEmail, QString message, QString timeMseconds){

    for (int i=0; i<clients.size(); i++){

        if(clients.at(i)->myEmail == receiverEmail){


            clients.at(i)->receiveMessage(senderEmail, receiverEmail, message, timeMseconds);

            QSqlQuery query;
            query.exec("UPDATE `messages` SET `server_sent` = '1' WHERE `fromEmail` = '" + senderEmail + "' AND `toEmail` = '" + receiverEmail + "' AND `time` = '" + timeMseconds + "' AND `server_sent` = '0';");

        }

    }

}

void QsMessengerServer::fwFileRequest(QString senderEmail, QString receiverEmail, QString transferId, QString fileName, QString fileSize){

    for (int i=0; i<clients.size(); i++){

        if(clients.at(i)->myEmail == receiverEmail){
            clients.at(i)->receiveFileRequest(senderEmail, receiverEmail, transferId, fileName, fileSize);
        }

    }
}

void QsMessengerServer::fwFileResponse(QString senderEmail, QString receiverEmail, QString transferId, QString response){

    for (int i=0; i<clients.size(); i++){

        if(clients.at(i)->myEmail == receiverEmail){
            clients.at(i)->receiveFileResponse(senderEmail, receiverEmail, transferId, response);
        }

    }
}

void QsMessengerServer::fwFilePayload(QString senderEmail, QString receiverEmail, QString transferId, QByteArray payload){

    for (int i=0; i<clients.size(); i++){

        if(clients.at(i)->myEmail == receiverEmail){
            clients.at(i)->receiveFilePayload(senderEmail, receiverEmail, transferId, payload);
        }

    }
}

void QsMessengerServer::updateStatus(QString email, QStringList peersList){

    for(int i=0; i< clients.size(); i++){

        for (int a=0; a< peersList.size(); a++){

            if(peersList.at(a) == clients.at(i)->myEmail){
                clients.at(i)->receiveStatusUpdate(email);
            }

        }
    }

}

void QsMessengerServer::fwFriendRequest(QString myEmail, QString peerEmail){

    for(int i=0; i< clients.size(); i++){

            if(peerEmail == clients.at(i)->myEmail){

                clients.at(i)->receiveFriendRequest(myEmail, peerEmail);

                i=clients.size();
            }


    }

}

void QsMessengerServer::openDataBase(){


    QFile sqlSettingsFile("./assets/mysql_credentials");

    if (sqlSettingsFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&sqlSettingsFile);

          mysqlUsername = in.readLine();
          mysqlPassword = in.readLine();

       sqlSettingsFile.close();
    }

    //qInfo() << mysqlUsername;
    //qInfo() << mysqlPassword;

    db = QSqlDatabase::addDatabase("QMYSQL", "buffer");
    db.removeDatabase("qt_sql_default_connection");
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.removeDatabase("buffer");

    db.setHostName("localhost");
    db.setDatabaseName("messenger");
    db.setUserName(mysqlUsername);
    db.setPassword(mysqlPassword);

    db.open();
}

void QsMessengerServer::clearDatabase(){

    QSqlQuery query;
    query.exec("UPDATE `users` SET `availability` = '3';");

}

void QsMessengerServer::generateUniqueLoginToken(QString sessionId, QString email){

    bool tokenGenerated=false;

    while (!tokenGenerated) {

        QString token = "loginToken-" + QString::number(QRandomGenerator::global()->bounded(1000000,10000000));
        bool match = false;

        for(int i=0; i<clients.size(); i++){

           if(clients.at(i)->loginToken == token){
               match = true;
           }
        }

        if(match != true){

            for(int i=0; i<clients.size(); i++){

                if(clients.at(i)->session_id == sessionId){
                    clients.at(i)->receiveUniqueLoginToken(sessionId, email, token);
                }
            }

            //qInfo() << "generatedToken: ";
            //qInfo() << token;
            tokenGenerated = true;

        }

    }

}

void QsMessengerServer::checkSignedIn(QString email, QString loginToken){

    bool signedIn = false;

    for(int i=0; i< clients.size(); i++){
      //  qInfo() << "client: " + clients.at(i)->session_id + " token: " + clients.at(i)->loginToken + " email " + clients.at(i)->myEmail;

        if(clients.at(i)->myEmail == email && clients.at(i)->loginToken != loginToken){

            signedIn = true;

            i=clients.size();
        }
    }

    for(int i=0; i< clients.size(); i++){

        if(clients.at(i)->myEmail == "unsigned" && clients.at(i)->loginToken == loginToken){

            clients.at(i)->completeSignIn(signedIn, email, loginToken);

            i=clients.size();
        }
    }

    //qInfo() << "__________________________________________________________________";
}


void QsMessengerServer::disconnectOther(QString otherEmail, QString myLoginToken){

    for(int i=0; i< clients.size(); i++){
        if(clients.at(i)->myEmail == otherEmail){

            clients.at(i)->receiveDisconnectFromOther();

            i=clients.size();
        }
    }
    for(int i=0; i< clients.size(); i++){
        if(clients.at(i)->loginToken == myLoginToken){

            QTimer::singleShot(2400, this, [=](){clients.at(i)->completeSignIn(false, otherEmail, myLoginToken);});

            i=clients.size();
        }
    }

}


void QsMessengerServer::fwAcceptedFriendRequest(QString myEmail, QString peerEmail){


    for(int i=0; i< clients.size(); i++){
        if(clients.at(i)->myEmail == peerEmail){

            clients.at(i)->receiveAcceptedFriendRequest(myEmail);

            i=clients.size();
        }
    }


}

void QsMessengerServer::fwUnfriended(QString myEmail, QString peerEmail){

    for(int i=0; i< clients.size(); i++){
        if(clients.at(i)->myEmail == peerEmail){

            clients.at(i)->receiveRemovedFromList(myEmail);

            i=clients.size();
        }
    }

}


/////////////////////////////////////////////////////////////////////////////////// END ////////////////////////////////////////////////////////////////////////////////////////////////
