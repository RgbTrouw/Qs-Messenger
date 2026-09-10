/*   QsMessenger Server v 1.0.2b Rev 4 Instant Messaging Application
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

#include <client.h>


#include <QtNetwork/QSslError>
#include <QtCore/QByteArray>
#include <QWebSocketServer>
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QSqlQuery>
#include <QFile>
#include <QList>



class QsMessengerServer : public QObject
{
    Q_OBJECT
public:
    explicit QsMessengerServer(quint16 port, bool log, bool verbose, QObject *parent = nullptr);
    ~QsMessengerServer() override;


private Q_SLOTS:
    void onNewConnection();
    void onSslErrors(QList<QSslError> errors);

    void close_client(QString session_id);
    void logData(QString data);

    void clearDatabase();

    void generateUniqueLoginToken(QString sessionId,QString email);
    void checkSignedIn(QString email, QString loginToken);
    void disconnectOther(QString otherEmail, QString myLoginToken);

    void fwMessage(QString senderEmail, QString recipientEmail, QString message, QString timeMseconds);
    void fwFileRequest(QString senderEmail, QString recipientEmail, QString fileName, QString fileSize);
    void fwFileResponse(QString senderEmail, QString recipientEmail, QString fileName, QString response);
    void updateStatus(QString email, QStringList peersList);
    void fwFriendRequest(QString myEmail, QString peerEmail);
    void fwAcceptedFriendRequest(QString myEmail, QString peerEmail);
    void fwUnfriended(QString myEmail, QString peerEmail);

    void openDataBase();

private:

    bool startVerbose = false;

    bool startLogging = false;
    bool openLogOnce = false;


    int clients_id = 0;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    QWebSocketServer *m_pWebSocketServer;

    QList<client *> clients;


    QList<QWebSocket *> m_clients;

    QString response;

    QString session_id_request="session_id";

    QString logPath;

    QString mysqlUsername;
    QString mysqlPassword;


};
