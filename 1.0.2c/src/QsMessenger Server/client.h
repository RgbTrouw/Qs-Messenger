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


#ifndef CLIENT_H
#define CLIENT_H

#include <QRandomGenerator>
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
    client(QHostAddress ip_address, quint16 remote_port, QString session_id_code, int clients_id, bool verbose);

public slots:
    void process_text_message(QString message);
    void process_binary_message(QByteArray data);
    void socket_disconnected();

    //void getNewMessages();
    //void get_list();

    void receiveUniqueLoginToken(QString sessionId, QString email, QString loginToken);

    void completeSignIn(bool signedIn, QString myEmail, QString loginToken);

    void receiveDisconnectFromOther();


    void receiveMessage(QString senderEmail, QString receiverEmail, QString Message, QString timeMseconds );
    void receiveFileRequest(QString senderEmail, QString receiverEmail, QString transferId, QString fileName, QString fileSize);
    void receiveFileResponse(QString senderEmail, QString receiverEmail, QString transferId, QString response);
    void receiveFilePayload(QString senderEmail, QString receiverEmail, QString transferId, QByteArray payload);
    void receiveStatusUpdate(QString peerEmail);
    void receiveFriendRequest(QString peerEmail, QString myEmail);
    void receiveAcceptedFriendRequest(QString peerEmail);
    void receiveRemovedFromList(QString peerEmail);

    void getOfflineMessages();
    void getOfflineFriendRequests();


signals:
    void emit_text_msg(QString message);
    void emit_binary_data(QByteArray data);
    void emit_close(QString session_id);

    void emit_logData(QString data);

    void emit_sendMsg(QString myEmail, QString peerEmail, QString message, QString mseconds);
    void emit_sendFileRequest(QString myEmail, QString peerEmail, QString transferId, QString fileName, QString fileSize);
    void emit_sendFileResponse(QString myEmail, QString peerEmail, QString transferId, QString response);
    void emit_sendFilePayload(QString myEmail, QString peerEmail, QString transferId, QByteArray payload);
    void emit_statusUpdate(QString myEmail, QStringList myPeers);
    void emit_friendRequest(QString myEmail, QString peerEmail);
    void emit_acceptedFriendRequest(QString myEmail, QString peerEmail);
    void emit_removedFromList(QString myEmail, QString peerEmail);

    void emit_getUniqueLoginToken(QString sessionId, QString email);
    void emit_checkSignedIn( QString myEmail, QString loginToken);

    void emit_disconnectOther(QString otherEmail, QString myLoginToken);



public:
    QString myEmail = "unsigned";

    QString loginToken = "";

private:

    bool startVerbose = false;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", QString::number(QRandomGenerator::global()->bounded(1000000,10000000)));
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    int client_id;

    QHostAddress IPaddress;
    qint16 remotePort;
    QString RemotePortString;

    QString logPath;

    QList<QString> myPeers;


    QString loginQuery;

    QString respondAddNewUserRequest="respondAddNewUserRequest:*:*";
    QString resendActivationCodeRequest="resendActivationCode:*:*";
    QString registerNewUserRequest="register:*:*:*:*:*:*:*:true";
    QString activateNewUserRequest="activate_user_account:*:*";
    QString getPeerGroupNameRequest="getPeerGroupName:*";
    QString setAvailabilityRequest="set_availability:*";
    QString disconnectOther="disconnectOtherSession:*";
    QString recoverPasswordRequest="recoverPassword:*";
    QString resetPasswordRequest="resetPassword:*:*";
    QString retrieveAvatarRequest="retrieve_avatar";
    QString uploadAvatarRequest="upload_avatar:*";
    QString getPeerAvatarRequest="peer_avatar:*";
    QString clearArchiveRequest="clearArchive:*";
    QString moveToGroupRequest="moveToGroup:*:*";
    QString loadPreviousRequest="previous:*:*";
    QString addNewUserRequest="addNewUser:*:*";
    QString removeGroupRequest="removeGroup:*";
    QString addNewGroupRequest="addNewGroup:*";
    QString toggleListRequest="toggle_list:*";
    QString removeUserRequest="removeUser:*";
    QString session_id_request="session_id";
    QString setStatusRequest="set_status:*";
    QString loginRequest="login:*:*:[0,2]";
    QString haveReadRequest="have_read:*";
    QString sendFileRequest="file:request:*:*:*:*";
    QString sendFileResponseRequest="file:response:*:*:*";
    QString signOutRequest="sign_out";
    QString getListRequest="getlist";
    QString infoRequest="getMyInfo";
    QString imRequest="im:*:*";

    QString uname;
    QString userid = "unsigned";

    QString loginAvailability;

    bool updateStatusUponLogin = false;
    QString logInChallenge = "";
    int logInChallengeCount = 0;


    QString previousRequestBuffer;





};

#endif // CLIENT_H
