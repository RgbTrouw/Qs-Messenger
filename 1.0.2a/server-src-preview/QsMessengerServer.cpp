
/*   QsMessenger Server v 1.0.2a Instant Messaging Application
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


QsMessengerServer::QsMessengerServer(quint16 port, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(nullptr)
{

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
        qInfo().noquote() << "Qs Messenger Server listening on port SSL:" << QString::number(port);
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection, this, &QsMessengerServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::sslErrors, this, &QsMessengerServer::onSslErrors);
        connect(m_pWebSocketServer, &QWebSocketServer::acceptError, this, [=](QAbstractSocket::SocketError socketErr){qInfo() << socketErr;} );


    }


    QDir dir("logs");
    if (!dir.exists()){
        QDir().mkpath("./logs/");
    }

    qint64 logName = QDateTime::currentMSecsSinceEpoch();

    logPath = "./logs/";
    logPath += QString::number(logName);
    logPath += ".log";

    QFile logFile(logPath);
    if(logFile.open(QIODevice::WriteOnly | QIODevice::Append)){
    logFile.write("Log Start: \n");
    logFile.close();
    }

}


QsMessengerServer::~QsMessengerServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}


void QsMessengerServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    m_clients << pSocket;

    QProcess process;
    process.start("openssl rand -hex 24");
    process.waitForFinished(-1);
    QString session_id_code=process.readAllStandardOutput();
    session_id_code = session_id_code.trimmed();


    clients_id += 1;
    clients.append(new client(pSocket->peerAddress(), pSocket->peerPort(), session_id_code, clients_id));



    connect(pSocket, &QWebSocket::textMessageReceived, clients.last(), &client::process_text_message);
    connect(pSocket, &QWebSocket::binaryMessageReceived, clients.last(), &client::process_binary_message);
    connect(pSocket, &QWebSocket::disconnected, clients.last(), &client::socket_disconnected);
    connect(clients.last(), SIGNAL(emit_close(QString)), this, SLOT(close_client(QString)) );
    connect(clients.last(), SIGNAL(emit_logData(QString)), this, SLOT(logData(QString)));
    connect(clients.last(), SIGNAL(emit_sendMsg(QString,QString,QString,QString)), this, SLOT(fwMessage(QString,QString,QString,QString)));
    connect(clients.last(), SIGNAL(emit_statusUpdate(QString, QStringList)), this, SLOT(updateStatus(QString, QStringList)));
    connect(clients.last(), SIGNAL(emit_friendRequest(QString,QString)), this, SLOT(fwFriendRequest(QString,QString)));


    dateTime();
}



void QsMessengerServer::onSslErrors(QList<QSslError> errors)
{
    //qDebug() << "Ssl errors occurred";
}



void QsMessengerServer::logData(QString data){

    QByteArray wData = (data + "\n").toUtf8();

    QFile logFile(logPath);
    if(logFile.open(QIODevice::WriteOnly | QIODevice::Append)){
    logFile.write(wData);
    logFile.close();
    }

}




void QsMessengerServer::dateTime(){
    QTimer::singleShot(1000, this, [=](){dateTime();});
}

void QsMessengerServer::close_client(QString session_id){
        for (int i = 0; i< clients.count(); i++ ){
            if (clients.at(i)->session_id == session_id){
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

    //db.close();
}

