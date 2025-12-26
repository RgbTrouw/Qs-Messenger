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


#ifndef CLIENT_H
#define CLIENT_H


#include <QHostAddress>
#include <QSqlDatabase>
#include <QWebSocket>
#include <QObject>
#include <QTimer>
#include <QFile>
#include <QDir>



class client : public QObject

{
     Q_OBJECT

public:
    QString session_id;
    client(QHostAddress ip_address, quint16 remote_port, QString session_id_code, int clients_id);

public slots:
    void process_text_message(QString message);
    void process_binary_message(QByteArray data);
    void socket_disconnected();

    //void getNewMessages();
    //void get_list();

    void receiveMessage(QString senderEmail, QString receiverEmail, QString Message, QString timeMseconds );
    void receiveStatusUpdate(QString peerEmail);
    void receiveFriendRequest(QString peerEmail, QString myEmail);

    void getOfflineMessages();
    void getOfflineFriendRequests();

signals:
    void emit_text_msg(QString message);
    void emit_binary_data(QByteArray data);
    void emit_close(QString session_id);

    void emit_logData(QString data);

    void emit_sendMsg(QString myEmail, QString peerEmail, QString message, QString mseconds);
    void emit_statusUpdate(QString myEmail, QStringList myPeers);
    void emit_friendRequest(QString myEmail, QString peerEmail);

public:
    QString myEmail = "unsigned";

private:

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    int client_id;

    QHostAddress IPaddress;
    qint16 remotePort;
    QString RemotePortString;

    QString logPath;

    QList<QString> myPeers;

    QString session_id_request="session_id";
    //QString sql_request="sql:*:*:*";
    QString loginRequest="login:*:*:[0,2]:*";
    QString infoRequest="getMyInfo:*";
    QString uploadAvatarRequest="upload_avatar:*";
    QString retrieveAvatarRequest="retrieve_avatar:*";
    QString getPeerAvatarRequest="peer_avatar:*:*";
    QString imRequest="im:*:*:*";
    QString haveReadRequest="have_read:*:*";
    QString loadPreviousRequest="previous:*:*:*";
    QString registerNewUserRequest="register:*:*:*:*:*:*:*:true:*";
    QString addNewUserRequest="addNewUser:*:*:*";
    QString removeUserRequest="removeUser:*:*";
    QString removeGroupRequest="removeGroup:*:*";
    QString addNewGroupRequest="addNewGroup:*:*";
    QString moveToGroupRequest="moveToGroup:*:*:*";

    QString respondAddNewUserRequest="respondAddNewUserRequest:*:*:*";

    QString setAvailabilityRequest="set_availability:*:*";
    QString setStatusRequest="set_status:*:*";
    QString signOutRequest="sign_out:*";
    QString getListRequest="getlist:*";
    QString toggleListRequest="toggle_list:*";
    QString activateNewUserRequest="activate_user_account:*:*";
    QString resendActivationCodeRequest="resendActivationCode:*:*"; // !
    QString recoverPasswordRequest="recoverPassword:*:*";
    QString resetPasswordRequest="resetPassword:*:*:*";

    QString getPeerGroupNameRequest="getPeerGroupName:*";

    QString sp;
    QString uname;
    QString userid = "unsigned";


    QString response;
    QString previousRequestBuffer;



};

#endif // CLIENT_H
