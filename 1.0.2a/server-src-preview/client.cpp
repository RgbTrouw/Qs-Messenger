
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


#include "client.h"

#include <QCryptographicHash>
#include <QWebSocket>
#include <QSqlQuery>
#include <QDateTime>
#include <QSqlError>
#include <QFileInfo>
#include <QProcess>
#include <QFile>

    // include <QDebug>



client::client(QHostAddress ip_address, quint16 remote_port, QString session_id_code, int clients_id)
{

    IPaddress = ip_address;
    remotePort = remote_port;

    session_id = session_id_code;
    client_id = clients_id;
    //qInfo() << session_id;

    db.close();



    QString mysqlUsername;
    QString mysqlPassword;

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

   RemotePortString  = QString::number(remotePort, 10);

}


void client::process_text_message(QString message){


     pClient = qobject_cast<QWebSocket *>(sender());

    if (message != previousRequestBuffer ){

        if(message.indexOf("peer_avatar:") != 0){
     //qInfo() << "new message: " + message;



     }

     if (pClient && message.indexOf("'") == -1 && message.indexOf("\"") == -1)
     {
         //pClient->sendTextMessage(message);

         response = "";

         QRegExp challenge(session_id_request);
         challenge.setPatternSyntax(QRegExp::Wildcard);

         challenge.setPattern(session_id_request);
         if ( challenge.exactMatch(message)){

             response = "session_id:" + session_id;
             pClient->sendTextMessage(response.toUtf8());
              pClient->flush();
             //qInfo() << response;

              emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" +"  Request: " + message + " ->" + "\n" + "  Delivery: " + response);

         }



         challenge.setPattern(loginRequest);
         challenge.setPatternSyntax(QRegExp::Wildcard);


         if (challenge.exactMatch(message)){

             //qInfo() << "login request...";
             //qInfo() << message;
             //qInfo() << message;
             QStringList login_params = message.split(":");
             //qInfo() << login_params;
             QString username = login_params.at(1);

             QString password = login_params.at(2);
             QString visibility = login_params.at(3);
             QString session_id = login_params.at(4);

             QByteArray re_hash = password.toUtf8();

             QString rpasswordh = QCryptographicHash::hash(re_hash, QCryptographicHash::Sha256).toHex();


             QString lastLogin;

             QSqlQuery query;

             //qInfo() <<
             query.exec("SELECT * FROM `users` WHERE `email` = '" + username + "' AND password = '" + rpasswordh + "' AND `status` != '0';");

              if ( query.size() == 1 ) {

                      while (query.next()) {

                      userid = query.value(0).toString();
                      uname = query.value(2).toString();
                      QString password = query.value(6).toString();
                      lastLogin = query.value(14).toString();

                      myEmail = username;
                      //QString last_login = query.value(3).toString();
                      //qInfo() << query.value(2);

                      }
 //                     qInfo() << userid;
 //                     qInfo() << uname;
 //                     qInfo() << session_id;
 //                     qInfo() << "1";

                      QString dt = QDateTime::currentDateTimeUtc().toString() + 2;

                      if (visibility == "2"){

                         query.exec("UPDATE `users` SET `availability` = '2' WHERE `id` = '" + userid + "';");

                      } else if ( visibility == "0")
                      {

                           //qInfo() <<
                           query.exec("UPDATE `users` SET `availability` = '0' WHERE `id` = '" + userid + "';");
                      }

                      QString mseconds;
                      mseconds = QString::number(QDateTime::currentMSecsSinceEpoch());


                      query.exec("UPDATE `users` SET `lastLogin` = '" + mseconds + "' WHERE `id` = '" + userid + "';");


                      //QTimer::singleShot(1000, this, [=]() { getNewMessages(); });


                      response = "login was successful... :" + lastLogin;





              } else {
                       response = "Could not login...";

              }

              pClient->sendTextMessage(response);
              pClient->flush();



              emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + response);

         }


         challenge.setPattern(getListRequest);
         if (challenge.exactMatch(message)){

             QString session_id = message.split(":").at(1);

             if (userid != "unsigned"){

                 //qInfo() << "get list request...";

                 myPeers.clear();

                 QSqlQuery query;
                 query.exec("SELECT `list`, `group_name` FROM `friends_list` WHERE `ownerEmail` = '" + myEmail + "';");

                 //qInfo() << myEmail;
                 //qInfo() << query.size();

                 QString list;
                 QString group_name = "";

                 response = "friends_list";

                 peersList.clear();

                 while(query.next()){

                     myPeers += query.value(0).toString().split(",");
                 //qInfo() << query.value(1).toString();
                 group_name = query.value(1).toString();
                 list = query.value(0).toString();

                 QStringList slist = list.split(",");
                 list = "";

                 for (int i =0; i< slist.size(); i++){
                     list.append("'");
                     list.append(slist.at(i));
                     list.append("'");
                     if (i != slist.size() -1){
                         list.append(",");
                     }
                 }



                 //qInfo() << list;
                 QSqlQuery qs;
                 qs.exec("SELECT `nickname`, `availability`, `status_message`, `full_name`,`email`,`picture` FROM `users` WHERE `email` IN (" + list + ") ORDER BY `nickname`;");
                //qInfo() << query.size();
                 list = "";

                 while (qs.next()) {
                    QString availability = qs.value(1).toString();
                    if (availability == "3"){availability = "2";}
                     list.append(":" + qs.value(0).toString() + "/" +  availability + "/" +  qs.value(2).toString() + "/picture/" + qs.value(4).toString());
                     peersList.append(qs.value(0).toString() + "/" +  availability + "/" +  qs.value(2).toString() + "/picture/" + qs.value(4).toString());
                 }

                 //qInfo() << list;

                 response.append(":|" + group_name  + "/3//picture/");
                 response.append(list);

                 }
                //qInfo() << list;

                 //previous_list = response;
                 //qInfo() << response;

                 //ss->singleShot(1000, this, SLOT(get_list()));

                 for(int i=0; i<myPeers.size(); i++){

                     if(myPeers.at(i) == ""){

                         myPeers.removeAt(i);
                     }
                 }

             } else if (userid == "unsigned") { //qInfo() << "user not signed in...";
             }

             pClient->sendTextMessage(response.toUtf8());
             pClient->flush();
             //qInfo() << response;

             emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + response);


         }


         challenge.setPattern(infoRequest);
         if (challenge.exactMatch(message)){

              QString session_id = message.split(":").at(1);

             if (userid != "unsigned"){
             //qInfo() << "my info request...";

             QSqlQuery query;
             query.exec("SELECT * FROM `users` WHERE `id` = '" + userid + "';");
             query.next();

             myEmail = query.value(6).toString();
             QString nickname = query.value(2).toString();
             QString status_message = query.value(10).toString();
             QString availability = query.value(8).toString();
             QString lastLogin = query.value(14).toString();

             //qInfo() << nickname << " " << status_ if (userid != "unsigned"){message << " " << availability;

             response = "userInfo:";
             response.append(nickname);
             response.append(":");
             response.append(status_message);
             response.append(":");
             response.append(availability);
             response.append(":");
             response.append(query.value(6).toString());

             pClient->sendTextMessage(response.toUtf8());
              pClient->flush();

              QTimer::singleShot(1000, this, SLOT(getOfflineMessages()));
              QTimer::singleShot(1000, this, SLOT(getOfflineFriendRequests()));

             //qInfo() << response;
              emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + response);

             }
         }

         challenge.setPattern(uploadAvatarRequest);
         if ( challenge.exactMatch(message)){

              QString session_id = message.split(":").at(1);

             if (userid != "unsigned"){
             //qInfo() << "upload avatar request...";
             pending_binary = "avatar_upload";
             response = "ok_upload_avatar";

             pClient->sendTextMessage(response.toUtf8());
             //qInfo() << response;
              pClient->flush();
              emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + response);


             }
         }

         challenge.setPattern(retrieveAvatarRequest);
         if ( challenge.exactMatch(message)){

            QString session_id = message.split(":").at(1);

            if (userid != "unsigned"){
             //qInfo() << "retrieve avatar request...";

             QString path = "./avatars/";
             path.append(myEmail);

             QFileInfo check_file(path);


             if (check_file.exists() && check_file.isFile()) {

             QString path = "./avatars/";
             path.append(myEmail);

             QFile picfile(path);
             picfile.open(QIODevice::ReadOnly);

             QByteArray ba;
             ba=picfile.readAll();

             ba.prepend("your_avatar:");
             pClient->sendBinaryMessage(ba);
             pClient->flush();

             emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + "your_avatar: ( data )");

                }
             }
         }

         challenge.setPattern(getPeerAvatarRequest);
         if ( challenge.exactMatch(message)){

              QString session_id = message.split(":").at(2);

             if (userid != "unsigned"){
             //qInfo() << "get peer avatar request...";
             QStringList parameters = message.split(":");
             QString peerEmail = parameters.at(1);

             QString path = "./avatars/";
             path.append(peerEmail);

            // qInfo() << path;
             QFileInfo check_file(path);

                if (check_file.exists() && check_file.isFile()) {
                    // qInfo() << "avatar exists...";
                 QFile picfile(path);
                 picfile.open(QIODevice::ReadOnly);

                 //qInfo() << path;
                 QByteArray ba;
                 ba=picfile.readAll();

                    if (ba.size() > 0){
                     //qInfo() << ba.size();
                     QString prep = "peer_avatar:" + peerEmail + ":";
                     ba.prepend(prep.toUtf8());
                     pClient->sendBinaryMessage(ba);
                     pClient->flush();
                     //qInfo() << ba.left(34);

                      emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch())  + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + prep + " ( data )");

                     }
                 }
             }

         }

         challenge.setPattern(imRequest);
         if (challenge.exactMatch(message)){

             //qInfo() << "im request...";
             //qInfo() << message;

             if (userid != "unsigned"){

             QStringList parameters = message.split(":");

             QString toEmail;
             toEmail = parameters.at(1);

             for(int i=0; i< myPeers.size(); i++){

                 if(toEmail == myPeers.at(i)){

                     QString mseconds;
                     mseconds = QString::number(QDateTime::currentMSecsSinceEpoch());

                     QSqlQuery query;
                     query.exec("INSERT INTO `messages` (`toEmail`, `fromEmail`, `txt_message`, `time`, `has_read`, `server_sent`) VALUES ('" + toEmail + "', '" + myEmail + "', '" + parameters.at(2) + "', '" + mseconds + "', '0', '0');");

                     emit emit_sendMsg(myEmail, parameters.at(1), parameters.at(2), mseconds);

                     i=myPeers.size();

                 }
             }

//             pClient->sendTextMessage(response.toUtf8());
//             pClient->flush();

              emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + "( none )");

             }

         }

         challenge.setPattern(haveReadRequest);
         if (challenge.exactMatch(message)){

             QString session_id = message.split(":").at(2);
             if (userid != "unsigned"){
                 
                 QString peerEmail = message.split(":").at(1);
                 
                 for(int i=0; i< myPeers.size(); i++){

                     if(peerEmail == myPeers.at(i)){

                         QString mseconds;
                         mseconds = QString::number(QDateTime::currentMSecsSinceEpoch());

                         QSqlQuery query;
                         query.exec("UPDATE `messages` SET `has_read` = '1' , `read_time` = '" + mseconds + "' WHERE `fromEmail` = '" + peerEmail + "' AND `toEmail` = '" + myEmail + "' AND `has_read` = '0';");

                         emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + "( none )");

                      }
                   }

             }
         }

         challenge.setPattern(loadPreviousRequest);
         if (challenge.exactMatch(message)){


              QString session_id = message.split(":").at(3);

             if (userid != "unsigned"){

                 //qInfo() << "previous messages request...";
                 QStringList parameters = message.split(":");
                 QString peerEmail = parameters.at(1);
                 QString index = parameters.at(2);

                 //qInfo() << peerid;

                 QSqlQuery query;
                 query.exec("SELECT * FROM `messages` WHERE (`fromEmail` = '" + peerEmail + "' AND `toEmail` = '" + myEmail + "' AND NOT `txt_message` = '3c64696e673e' ) OR (`fromEmail` = '" + myEmail + "' AND `toEmail` = '" + peerEmail + "' AND NOT `txt_message` = '3c64696e673e' ) ORDER BY `time` DESC LIMIT " + index + ", 10;");

                 //qInfo() << query.size();

                        while (query.next()){

                            QString msgFrom = query.value(8).toString();
                            QString msgTo = query.value(9).toString();

                            QString pmessage="pm:";
                            pmessage.append(msgFrom);
                            pmessage.append(":");

                            pmessage.append(msgTo);
                            pmessage.append(":");

                            pmessage.append(query.value(3).toString());
                            pmessage.append(":");

                            pmessage.append(query.value(4).toString());

                            pClient->sendTextMessage(pmessage.toUtf8());
                            //qInfo() << pmessage;
                            pClient->flush();

                             emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + pmessage);

                        }
                 }
         }


         challenge.setPattern(registerNewUserRequest);
         if ( challenge.exactMatch(message)){

             //qInfo() << "registration request...";

             //qInfo() << message;

             QString session_id = message.split(":").at(9);

             QStringList register_params = message.split(":");

             QString fname = register_params.at(1);
             QString uname =  register_params.at(2);
             QString date_of_birth = register_params.at(3);
             QString gender = register_params.at(4);
             QString country = register_params.at(5);
             QString email = register_params.at(6);
             QString password = register_params.at(7);
             QString agreement = register_params.at(8);

             QByteArray hash = password.toUtf8();
             password = QCryptographicHash::hash(hash, QCryptographicHash::Sha256).toHex();

             QProcess process;
             process.start("openssl rand -hex 10");
             process.waitForFinished(-1);
             QString scode=process.readAllStandardOutput();
             scode = scode.trimmed();

             //qInfo() << "registration request...";

             QSqlQuery query;

             query.exec("SELECT `id` FROM `users` WHERE `email` = '" + email + "'" );

             if ( query.size() == 0 ) {


              if (query.exec("INSERT INTO `users` (`full_name`, `nickname`, `gender`, `country`,`email`, `password`, `hex`, `status`, `date_of_birth`, `lastLogin`) VALUES ('" + fname + "', '" + uname + "', '" + gender + "', '" + country + "', '" + email + "', '" + password + "', '" + scode + "', '0', '" + date_of_birth + "', '0');" )) {

              process.execute("php ./assets/mail_to_register.php " + email + " " + scode);
              process.waitForFinished(-1);

              response = "Registration success... Please activate your account...";

              } else { QSqlError err = query.lastError();
                 // qInfo() << err;
              }
             } else { response = "Email already in use or not activated..."; }

             pClient->sendTextMessage(response.toUtf8());
             //qInfo() << response;
             pClient->flush();

              emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + response);

         }

         challenge.setPattern(resendActivationCodeRequest);
         if (challenge.exactMatch(message)){


             QString session_id = message.split(":").at(2);
             QString email = message.split(":").at(1);

                QSqlQuery query;
                if(query.exec("SELECT `hex` from `users` WHERE `email` = '" + email + "' AND `status` != '1';")){
                query.next();
                if(query.size() == 1){

                    QProcess process;

                    process.start("openssl rand -hex 10");
                    process.waitForFinished(-1);

                    QString scode=process.readAllStandardOutput();
                    scode = scode.trimmed();

                    if(query.exec("UPDATE `users` SET `hex` = '" + scode + "' WHERE `email` = '" + email + "' AND `status` != '1';")){

                    process.start("php ./assets/mail_to_register.php " + email + " " + scode);
                    process.waitForFinished(-1);

                    pClient->sendTextMessage("Activation code resent...");
                    pClient->flush();


                    emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + "Activation code resent...");

                } else {

                        QSqlError err = query.lastError();
                       // qInfo() << err;
                }

                } else {

                    pClient->sendTextMessage("Email not registered or already activated...");
                    pClient->flush();

                     emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + "Email not registered or already activated...");
                }
                } else {
                        QSqlError err = query.lastError();
                        //qInfo() << err;
                }



         }

         challenge.setPattern(addNewUserRequest);
         if (challenge.exactMatch(message)){

             QString session_id = message.split(":").at(3);

             if (userid != "unsigned"){
             //qInfo() << "friend request...";

             QStringList parameters;
             parameters = message.split(":");

             QString peerEmail = parameters.at(1);

             QSqlQuery query;
             query.exec("SELECT `id` FROM `users` where `email` = '" + peerEmail + "';");
             query.next();

             if (query.size() == 1){

                 //qInfo() << "email exists...";
                 QString peerid = query.value(0).toString();

                 bool allready_friends = false;

                 for(int i=0; i< myPeers.size(); i++){

                     if(peerEmail == myPeers.at(i)){
                         allready_friends = true;
                     }
                 }

                 if (allready_friends) {

                 response =  "You are allready friends...";
                 } else {

                  query.exec("SELECT * FROM `friendship_requests` WHERE `fromEmail` = '" + myEmail + "' AND `toEmail` = '" + peerEmail + "' AND `fstatus` = '0';");
                  query.next();

                  //qInfo() << query.lastError();

                  if (query.size() == 0){


                      query.exec("INSERT INTO `friendship_requests` ( `fromEmail`, `toEmail`, `fstatus`, `groupName`) VALUES ( '" + myEmail + "', '" + peerEmail + "', '0', '" + parameters.at(2) + "');");
                      //qInfo() << query.lastError();

                      emit_friendRequest(myEmail, peerEmail);

                      response = "Friendship request has been sent...";

                  } else { response = "Request allready sent...";}

                 }


             } else { response = "Email is not registered...";}

                 pClient->sendTextMessage(response.toUtf8());
                 //qInfo() << response;
                 pClient->flush();

                 emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + response);
             }

         }


         challenge.setPattern(removeUserRequest);
         if (challenge.exactMatch(message)){

             if (userid != "unsigned"){
                 QStringList parameters = message.split(":");

                 QString peerEmail = parameters.at(1);

                 QSqlQuery query;
                 QString groupName;

                 query.exec("SELECT * FROM `friends_list` WHERE `ownerEmail` = '" + myEmail + "';");

                 QStringList friendsList;

                 while (query.next()){

                     friendsList = query.value(3).toString().split(",");

                     for (int i =0; i<friendsList.size(); i++){

                         if (friendsList.at(i) == peerEmail){

                             groupName = query.value(2).toString();

                             friendsList.removeAt(i);

                             QString list;

                             for (int a =0; a<friendsList.count(); a++){
                                 list += friendsList.at(a);
                                 list += ",";
                             }

                             list = list.left(list.size() - 1);

                             //qInfo() << friendsList;
                             //qInfo() << groupName;

                             //qInfo() << list;

                             QSqlQuery sq;
                             sq.exec("UPDATE `friends_list` SET `list` = '" + list + "' WHERE `ownerEmail` = '" + myEmail + "' AND `group_name` = '" + groupName + "' ;");

                             pClient->sendTextMessage("userRemovedFromList:" + peerEmail);
                             pClient->flush();

                             emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + "userRemovedFromList:" + peerEmail);

                         }
                     }
                 }
             }
         }


         challenge.setPattern(removeGroupRequest);
         if (challenge.exactMatch(message)){

             if (userid != "unsigned"){
                 QStringList parameters = message.split(":");

                 QString groupName = parameters.at(1);

                 int x = QString::compare(groupName, "Friends", Qt::CaseInsensitive);
                 if(x != 0 ){
                 QSqlQuery query;
                 query.exec("DELETE FROM `friends_list` WHERE `ownerEmail` = '" + myEmail + "' AND `group_name` = '" + groupName +"';");

                 pClient->sendTextMessage("Group Deleted:" + groupName);
                 pClient->flush();

                  emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + "Group Deleted:" + groupName );

                 }
             }

         }


         challenge.setPattern(respondAddNewUserRequest);
         if (challenge.exactMatch(message)){

              QString session_id = message.split(":").at(3);

             if (userid != "unsigned"){
             //qInfo() << "respond friend request...";

             QStringList parameters = message.split(":");
             QString peerEmail = parameters.at(1);


             if (parameters.at(2) == "yes"){

             QSqlQuery query;
             query.exec("SELECT `groupName` FROM `friendship_requests` WHERE `fromEmail` = '" + peerEmail + "' AND `toEmail` = '" + myEmail + "' AND `fstatus` = '0';");
             query.next();

             QString groupName = query.value(0).toString();


             query.exec("UPDATE `friendship_requests` SET `fstatus` = '1' WHERE `fromEmail` = '" + peerEmail + "' AND `toEmail` = '" + myEmail + "' AND `fstatus` = '0';");


             /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if(peerEmail != myEmail){

             query.exec("SELECT `list` FROM `friends_list` WHERE `ownerEmail` =  '" + myEmail + "' AND `group_name` = 'Friends';");

             query.next();

             QString friends_list = query.value(0).toString();
             friends_list.append(",");
             friends_list.append(peerEmail);
             //qInfo() << friends_list;



             query.exec("UPDATE `friends_list` SET `list` = '" + friends_list + "' WHERE `ownerEmail` = '" + myEmail + "' AND `group_name` = 'Friends';");

             }
             /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

             query.exec("SELECT `list` FROM `friends_list` WHERE `ownerEmail` =  '" + peerEmail + "' AND `group_name` = '" + groupName + "';");
             //qInfo() << uid << " " << userid;
             query.next();

             QString ufriends_list = query.value(0).toString();
             if (ufriends_list != ""){
             ufriends_list.append(",");}
             ufriends_list.append(myEmail);
             //qInfo() << ufriends_list;


             query.exec("UPDATE `friends_list` SET `list` = '" + ufriends_list + "' WHERE `ownerEmail` = '" + peerEmail + "' AND `group_name` = '" + groupName + "';");
             ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

             pClient->sendTextMessage("Friendship request accepted...");
             pClient->flush();



               emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + "Friendship request accepted...");
             }

             else if (parameters.at(2) == "no"){

                 QSqlQuery query;


                 query.exec("UPDATE `friendship_requests` SET `fstatus` = '2' WHERE `fromEmail` = '" + peerEmail + "' AND `toEmail` = '" + myEmail + "';");

               pClient->sendTextMessage("Friendship request declined...");
               pClient->flush();

               emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + "Friendship request declined...");
             }


             }


         }



         challenge.setPattern(setAvailabilityRequest);
         if (challenge.exactMatch(message)){
//            if(false){
              QString session_id = message.split(":").at(2);

             if (userid != "unsigned"){

             QStringList parameters = message.split(":");

             //qInfo() << "set availability request...";

             QSqlQuery query;
             query.exec("UPDATE `users` SET `availability` = '" + parameters.at(1) + "' WHERE `email` = '" + myEmail + "';");

             if (parameters.at(1) == "2"){
                 query.exec("UPDATE `users` SET `status_message` = '' WHERE `email` = '" + myEmail + "';");

                 emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + " ( none ) ");

             }

             emit emit_statusUpdate(myEmail, myPeers);

             }

         }

         challenge.setPattern(setStatusRequest);
         if (challenge.exactMatch(message)){

              QString session_id = message.split(":").at(2);

             if (userid != "unsigned"){
             //qInfo() << "set status request...";

             QStringList parameters = message.split(":");

             QSqlQuery query;
             query.exec("SELECT `availability` FROM `users` WHERE `status` = '1' AND `email` = '" + myEmail + "';");

             query.next();

             QString availability = query.value(0).toString();

             if (availability != "2"){

             query.exec("UPDATE `users` SET `status_message` = '" + parameters.at(1) + "' WHERE `email` = '" + myEmail + "';");

             } else {
                  query.exec("UPDATE `users` SET `status_message` = '' WHERE `email` = '" + myEmail + "';");
             }

             emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + " ( none ) ");

             emit emit_statusUpdate(myEmail, myPeers);

             }

         }

         challenge.setPattern(signOutRequest);
         if (challenge.exactMatch(message)){

               if (userid != "unsigned"){
              QString session_id = message.split(":").at(1);

             //qInfo() << "sign out request...";
             QSqlQuery query;
             query.exec("UPDATE `users` SET `availability` = '3' WHERE `email` = '" + myEmail + "';");
             query.exec("UPDATE `users` SET `status_message` = '' WHERE `email` = '" + myEmail + "';");

             userid = "unsigned";

             emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + " ( none ) ");

            }
         }

         challenge.setPattern(activateNewUserRequest);
         if (challenge.exactMatch(message)){

             QString session_id = message.split(":").at(2);

             QStringList activate_params = message.split(":");

             if(activate_params.at(1).size() == 20){

             QSqlQuery query;
             //qInfo() <<
             if(query.exec("UPDATE `users` SET `status` = '1' WHERE `hex` = '" + activate_params.at(1) + "';")){

                 QString email;
                 query.exec("SELECT `email` FROM `users` WHERE `hex` = '" + activate_params.at(1) + "';");
                 query.next();

                // qInfo() << query.size();

                 email = query.value(0).toString();

                 QProcess process;
                 process.start("openssl rand -hex 40");
                 process.waitForFinished(-1);

                 QString scode=process.readAllStandardOutput();
                 scode = scode.trimmed();

                 if (query.exec("UPDATE `users` SET `hex` = '" + scode +"' WHERE `hex` = '" + activate_params.at(1) + "';")){

                 if(query.exec("INSERT INTO `friends_list` (`ownerEmail`, `group_name`) VALUES ('" + email + "', 'Friends')")){

               pClient->sendTextMessage("Activation success...");
               pClient->flush();

                emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + "Activation success...");



             } else { QSqlError err = query.lastError();
                    // qInfo() << err;
                     pClient->sendTextMessage("Activation failed...");
                     pClient->flush();

                      emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + "Activation failed...");

                 }


             } else { QSqlError err = query.lastError();
            // qInfo() << err;

             pClient->sendTextMessage("Activation failed...");
             pClient->flush();
               emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + "Activation failed...");

             }

             } else { QSqlError err = query.lastError();
            // qInfo() << err;

             pClient->sendTextMessage("Activation failed...");
             pClient->flush();
               emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + "Activation failed...");

             }
         } else {
                 pClient->sendTextMessage("Activation failed...");
                 pClient->flush();
                   emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + "Activation failed...");

             }

         }

         challenge.setPattern(recoverPasswordRequest);
         if (challenge.exactMatch(message)){

              QString session_id = message.split(":").at(2);

             //qInfo() << "recover password request...";
             QStringList reset_params = message.split(":");
                        QString email;

                        //qInfo() << reset_params;

                        email = reset_params.at(1);

                        QSqlQuery query;
                        query.exec("SELECT * FROM `users` WHERE `email` = '" + email + "' AND `status` != '0';");

                        if (query.size() == 1) {

                            QProcess process;

                            process.start("openssl rand -hex 10");
                            process.waitForFinished(-1);

                            QString scode=process.readAllStandardOutput();
                            scode = scode.trimmed();

                            query.exec("UPDATE `users` SET `hex` = '" + scode + "' WHERE `email` = '" + email + "' AND `status` != '0';");


                            process.start("php ./assets/mail_to_recover.php " + email + " " + scode);
                            process.waitForFinished(-1);

                            response = "Reset code sent...";

             //               db.close();
                            //db.removeDatabase("qt_sql_default_connection");

                        } else { response = "Email is not registered or activated..."; }

                    //    qInfo() << "reset password request";
             pClient->sendTextMessage(response.toUtf8());
              pClient->flush();
             //qInfo() << response;
              emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + response);


         }

         challenge.setPattern(resetPasswordRequest);
         if (challenge.exactMatch(message)){

              QString session_id = message.split(":").at(3);

             //qInfo() << "reset password request...";
             //qInfo() << "new password request";

                        QStringList recover_params = message.split(":");

                        //qInfo() << recover_params;

                        QString password;
                        QString scode;

                        scode = recover_params.at(1);
                        password = recover_params.at(2);

                        if(password != "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855" ){

                        QByteArray re_hash = password.toUtf8();
                        QString rpasswordh = QCryptographicHash::hash(re_hash, QCryptographicHash::Sha256).toHex();

                        QSqlQuery query;
                        query.exec("SELECT * FROM `users` WHERE `hex` = '" + scode + "' AND `status` != '0';");


                        if (query.size() == 1) {

                            QProcess process;

                            process.start("openssl rand -hex 20");
                            process.waitForFinished(-1);

                            QString scode2=process.readAllStandardOutput();
                            scode2 = scode2.trimmed();

                            query.exec("UPDATE `users` SET `password` = '" + rpasswordh + "', `hex` = '" + scode2 + "' WHERE `hex` = '" + scode + "';");


                            pClient->sendTextMessage("Password changed...");
                            pClient->flush();

                               emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + "Password changed...");


                        } else {
                            pClient->sendTextMessage("Reset code not validated...");
                            pClient->flush();
                            emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + "Reset code not validated...");
                        }


                        } else {
                            pClient->sendTextMessage("Password must not be null...");
                            pClient->flush();
                            emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + "Password must not be null...");
                        }

         }


         challenge.setPattern(addNewGroupRequest);
         if (challenge.exactMatch(message)){

             QString session_id = message.split(":").at(2);
             QString groupName = message.split(":").at(1);

             if (userid != "unsigned" && groupName.size() > 2 && groupName.size() < 17 && groupName.indexOf(" ") == -1){

                 QSqlQuery query;

                 query.exec("SELECT `id` FROM `friends_list` WHERE `group_name` = '" + groupName + "' AND `ownerEmail` = '" + myEmail + "';");
                 query.next();

                 if (query.size() == 0){

                     query.exec("INSERT INTO `friends_list` (`ownerEmail`, `group_name`) VALUES ('" + myEmail +"', '" + groupName + "')");

                     pClient->sendTextMessage("New Group Created:" + groupName);
                     pClient->flush();

                     emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + "New Group Created:" + groupName);


                 } else {

                     pClient->sendTextMessage("Group already exists:" + groupName);
                     pClient->flush();

                    emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + "Group already exists:" + groupName);
                 }

             }
         }

         challenge.setPattern(moveToGroupRequest);
         if (challenge.exactMatch(message)){

             QString session_id = message.split(":").at(2);
             QString peerEmail = message.split(":").at(1);
             QString targetGroupName = message.split(":").at(2);

             if (userid != "unsigned" && targetGroupName.size()>2){

                 //qInfo() << "move " + email + " to group " + targetGroupName;

                 QSqlQuery query;

                 ///////// locate & remove from list

                 query.exec("SELECT `list`, `group_name` FROM `friends_list` WHERE `ownerEmail` = '" + myEmail + "';");

                 QStringList groupList;
                 QString groupName;

                 while (query.next()){

                     groupList = query.value(0).toString().split(",");
                     groupName = query.value(1).toString();

                     for (int i=0; i< groupList.size(); i++) {

                         if(peerEmail == groupList.at(i)){

                             groupList.removeAt(i);

                             QString newList;

                             for (int a=0; a< groupList.size(); a++){

                                 newList += groupList.at(a);
                                 newList += ",";

                             }

                             newList = newList.left(newList.count() - 1);

                             QSqlQuery qr;
                             qr.exec("UPDATE `friends_list` SET `list` = '" + newList + "' WHERE `ownerEmail` = '" + myEmail + "' AND `group_name` = '" + groupName + "';");

                         }

                     }

                 }

                 ///// update new list

                 query.exec("SELECT `list` FROM `friends_list` WHERE `ownerEmail` = '" + myEmail + "' AND `group_name` = '" + targetGroupName + "';");
                 query.next();
                 QString targetGroupList = query.value(0).toString();
                 targetGroupList.append(",").append(peerEmail);

                 query.exec("UPDATE `friends_list` SET `list` = '" + targetGroupList + "' WHERE `ownerEmail` = '" + myEmail + "' AND `group_name` = '" + targetGroupName + "';");

                 pClient->sendTextMessage("userMovedToGroup:" + peerEmail + ":" + targetGroupName);
                 pClient->flush();

                 emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + "userMovedToGroup:" + peerEmail + ":" + targetGroupName);
             }
         }


        previousRequestBuffer = message;
            }

    }

}

void client::process_binary_message(QByteArray data){

    if (pClient)
    {

        if(userid != "unsigned"){

            QString header = data.left(9);

            if (header == "myAvatar:"){

                data = data.right(data.size() - 9);

                QString path = "./avatars/";
                path.append(myEmail);

                QFile avatar(path);
                avatar.open(QIODevice::WriteOnly);
                //qInfo() <<
                avatar.write(data);

                emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + "myAvatar: ( data ) " + " ->" + "\n" + "  Delivery: " + " ( none ) ");
            }

        }

    }


}

void client::socket_disconnected(){



    QSqlQuery query;
    query.exec("UPDATE `users` SET `availability` = '3' WHERE `email` = '" + myEmail + "';");
    query.exec("UPDATE `users` SET `status_message` = '' WHERE `email` = '" + myEmail + "';");

    userid = "unsigned";
    myEmail = "unsigned";

    //list_type = false;

    QTimer::singleShot(1000, this, [=](){emit emit_close(session_id);});

    emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "  DISCONNECTED");

}

void client::receiveMessage(QString senderEmail, QString receiverEmail, QString message, QString timeMseconds){


    QString qr;
    qr = "im:";
    qr.append(senderEmail);
    qr.append(":");
    qr.append(message);
    qr.append(":");
    qr.append(timeMseconds);


    pClient->sendTextMessage(qr.toUtf8());
    pClient->flush();

    emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + "none" + " ->" + "\n" + "  Delivery: " + qr);


}


void client::getOfflineMessages(){

    if (userid != "unsigned"){

        QSqlQuery query;
        query.exec("SELECT * FROM `messages` WHERE `toEmail` = '" + myEmail + "' AND (`server_sent` = '0' OR `has_read` = '0');");

        query.next();

        //qInfo() << query.size();
        if (query.size() > 0){


            for (int i=0; i<query.size(); i++){

                QString qr;
                qr = "im:";
                qr.append(query.value(8).toString());
                qr.append(":");
                qr.append(query.value(3).toString());
                qr.append(":");
                qr.append(query.value(4).toString());


                pClient->sendTextMessage(qr.toUtf8());
                pClient->flush();

                if(query.value(6).toString() == "0"){

                    QSqlQuery query2;

                    query2.exec("UPDATE `messages` SET `server_sent` = '1' WHERE `id` = '" + query.value(0).toString() + ";");

                }

                emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + "none" + " ->" + "\n" + "  Delivery: " + qr);


            }

        }
    }


}

void client::getOfflineFriendRequests(){

    if (userid != "unsigned"){

        QSqlQuery query;
        query.exec("SELECT * FROM `friendship_requests` WHERE `toEmail` = '" + myEmail + "' AND `fstatus` = '0';");

        for(int i=0; i<query.size(); i++){
            query.next();

            QString response;
            response="newfriendshiprequest:";
            response.append(query.value(5).toString());

            pClient->sendTextMessage(response);

            pClient->flush();

            emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + " ( none ) " + " ->" + "\n" + "  Delivery: " + response);
            response = "";

        }

    }

}

void client::receiveFriendRequest(QString peerEmail, QString myEmail)
{

    // parameters reversed

      if (userid != "unsigned"){

          QSqlQuery query;
          query.exec("SELECT * FROM `friendship_requests` WHERE `toEmail` = '" + myEmail + "' AND `fromEmail` = '" + peerEmail + "' AND `fstatus` = '0';");
          query.next();

          if (query.size() == 1){

              QString response;
              response="newfriendshiprequest:";
              response.append(query.value(5).toString());

              pClient->sendTextMessage(response);

              pClient->flush();

              emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + " ( none ) " + " ->" + "\n" + "  Delivery: " + response);
              response = "";

          }

      }


}

void client::receiveStatusUpdate(QString peerEmail){


    if (userid != "unsigned"){

        QString list;


    for (int i =0; i< myPeers.size(); i++){
        list.append("'");
        list.append(myPeers.at(i));
        list.append("'");
        list.append(",");
    }

    list = list.left(list.size() - 1);

    //qInfo() << list;
    //qInfo() << myPeers;

    QSqlQuery query;
    query.exec("SELECT `nickname`, `availability`, `status_message`, `full_name`,`email`,`picture` FROM `users` WHERE `email` IN (" + list + ") AND `email` = '" + peerEmail + "';");
    query.next();

    //qInfo() << query.size();

    QString updateString = "updateUser:";
    QString availability;

    availability = query.value(1).toString();
    //if (availability == "3") { availability = "2";}

    updateString.append(query.value(0).toString() + "/" +  availability + "/" +  query.value(2).toString() + "/picture/" + query.value(4).toString());

    pClient->sendTextMessage(updateString.toUtf8());
    pClient->flush();

    emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + " ( update status ) " + " ->" + "\n" + "  Delivery: " + updateString);

    }

}
//void client::getNewMessages(){



//    if (userid != "unsigned"){
//   //qInfo() << "get new messages...";


//    QSqlQuery query;
//    query.exec("SELECT * FROM `messages` WHERE `msg_to` = '" + userid + "' AND `server_sent` = '0';");

////    for(int i=0; i<query.size(); i++){
////        query.next();
        
////    }
////    }
//    while (query.next()){

//    //qInfo() << "nr of messages: " + QString::number(query.size());
//    QString from;
//    from = query.value(1).toString();


//    QString message;
//    message = query.value(3).toString();


//    QSqlQuery qrs;
//    qrs.exec("SELECT `list` FROM `friends_list` WHERE `owner_id` = '" + userid + "';");
//    //qInfo() << "nr of lists: " + QString::number(qrs.size());
//    while(qrs.next()){

//    QString list = qrs.value(0).toString();

//    QStringList slist = list.split(",");
//    list = "";
//    for (int i =0; i< slist.size(); i++){
//        list.append("'");
//        list.append(slist.at(i));
//        list.append("'");
//        if (i != slist.size() - 1){
//            list.append(",");
//        }
//    }

//    //qInfo() << "current list: " + list;

//    for(int a=0; a < slist.count(); a++){
//        if (from == slist.at(a)){
//            //qInfo() << true;

//            qrs.exec("SELECT `email` FROM `users` WHERE `id` = '" + from + "' AND `id` IN (" + list + ");");
//            qrs.next();


//            if(qrs.size()>0){
//            //qInfo() << "peer name: " + qrs.value(0).toString();

//            QString peerEmail = qrs.value(0).toString();

//            QString qr;
//            qr = "im:";
//            qr.append(peerEmail);
//            qr.append(":");
//            qr.append(message);
//            qr.append(":");
//            qr.append(query.value(4).toString());


//            pClient->sendTextMessage(qr.toUtf8());
//            pClient->flush();

//            emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + message + " ->" + "\n" + "  Delivery: " + qr);

//            //qInfo() << query.value(4).toString();
//            query.exec("UPDATE `messages` SET `server_sent` = '1' WHERE `msg_from` = '" + from + "' AND `msg_to` = '" + userid + "' AND `time` = '" + query.value(4).toString() + "' AND `server_sent` = '0';");

//            a=slist.count();

//        }

//    }




//    }   }  }

//    //QTimer::singleShot(1000, this, [=]() { getNewMessages(); });


//    }



//}

//void client::get_list(){

    //qInfo() << "getList";
    //qInfo() << userid + " debug";

    //qInfo() << "Breakpoint 24.0";
//    QString glist;
//    glist.prepend("friends_list");


//    if (userid != "unsigned"){


//        if (!list_type){

//        QSqlQuery query;
//        query.exec("SELECT `list`, `group_name` FROM `friends_list` WHERE `owner_id` = '" + userid + "';");

//        QString list;
//        QString group_name;

//        peersListCompare.clear();

//        while(query.next()){

//        group_name = query.value(1).toString();
//        list = query.value(0).toString();

//        QStringList slist = list.split(",");
//        list = "";
//        for (int i =0; i< slist.size(); i++){
//            list.append("'");
//            list.append(slist.at(i));
//            list.append("'");
//            if (i != slist.size() -1){
//                list.append(",");
//            }
//        }

//        QSqlQuery qs;
//        qs.exec("SELECT `nickname`, `availability`, `status_message`, `full_name`,`email`,`picture` FROM `users` WHERE `id` IN (" + list + ") ORDER BY `nickname`;");
//        // Info() << "c";
//        list = "";
//        QString availability;


//        while (qs.next()) {

//            availability = qs.value(1).toString();
//            if (availability == "3") { availability = "2";}
//            list.append(":" + qs.value(0).toString() + "/" +  availability + "/" +  qs.value(2).toString() + "/picture/" + qs.value(4).toString());

//            peersListCompare.append(qs.value(0).toString() + "/" +  availability + "/" +  qs.value(2).toString() + "/picture/" + qs.value(4).toString());


//        }


//        glist.append(":|" + group_name + "/3//picture/");
//        glist.append(list);

//        }

//        //qInfo() << glist;

//        peersListBuffer = peersListCompare;


//        if(peersListCompare.size() > peersList.count()){
//        for (int i = 0; i < peersListCompare.count(); i++){
//            for (int a = 0; a < peersList.count(); a++){

//                if (peersListCompare.at(i) == peersList.at(a)){
//                    peersListCompare.removeAt(i);
//                }

//            }
//        }

//        if (peersListCompare.size() != peersList.count()){
//            for (int i=0; i< peersListCompare.size(); i++){

//                //qInfo() << peersListCompare;                     /// update_user_data -> //

//                QSqlQuery query;
//                query.exec("SELECT `id` FROM `users` WHERE `email` = '" + peersListCompare.at(i).split("/").at(4) + "';");
//                query.next();

//                QString peerId = query.value(0).toString();

//                QStringList friendsListA;
//                QString groupNameA;

//               // qInfo() << peerId;

//                query.exec("SELECT `list`, `group_name` FROM `friends_list` WHERE `owner_id` = '" + userid + "';");
//                while(query.next()){

//                groupNameA = query.value(1).toString();
//                friendsListA = query.value(0).toString().split(",");

//                for(int b = 0; b<friendsListA.count(); b++ ){

//                    if(friendsListA.at(b) == peerId){

//                        QString updateString = "addUserToGroup:" + peersListCompare.at(i) + ":" + groupNameA;
//                        pClient->sendTextMessage(updateString.toUtf8());
//                        pClient->flush();

//                        emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + " ( none ) " + " ->" + "\n" + "  Delivery: " + updateString);

//                        break;
//                    }

//                }


//                }

//            }
//        }

//        } else if (peersListCompare.size() == peersList.count()) {

//            for (int i = 0; i < peersListCompare.count(); i++){
//                       for (int a = 0; a < peersList.count(); a++){
//                           if (peersListCompare.at(i) == peersList.at(a)){
//                               peersListCompare.removeAt(i);
//                           }
//                       }
//                   }



//                   peersList = peersListBuffer;

//            if (peersListCompare.size()>0){
//                       for (int i=0; i< peersListCompare.size(); i++){

//                           //qInfo() << peersListCompare;                     /// update_user_data -> //

//                           QString updateString = "updateUser:" + peersListCompare.at(i);
//                           pClient->sendTextMessage(updateString.toUtf8());
//                           pClient->flush();

//                           emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + " ( none ) " + " ->" + "\n" + "  Delivery: " + updateString);

//                       }
//                   }

//        }


//        peersList = peersListBuffer;



//        if (previous_list == ""){
//            previous_list = glist;
//        }


//        if (previous_list != glist){

//        QString update_list = glist;

//        previous_list = glist;


//        }

//        }

//                //qInfo() << "get_friend_requests...";

//                QSqlQuery query;
//                query.exec("SELECT * FROM `friendship_requests` WHERE `fto` = '" + userid + "' AND `fstatus` = '0';");

//                //qInfo() << query.size();
//                if (query.size() > 0) {
//                    query.next();

//                    QString msg = query.value(3).toString();

//                    query.exec("SELECT `email` FROM `users` WHERE `id` = '" + query.value(1).toString() + "';");

//                    query.next();
//                    response="newfriendshiprequest:";
//                    response.append(query.value(0).toString());

//                    pClient->sendTextMessage(response);
//                    //qInfo() << response;
//                    pClient->flush();

//                    emit emit_logData("\n" + IPaddress.toString() + ":" + RemotePortString + "  " + QString::number(QDateTime::currentMSecsSinceEpoch()) + "\n" + "  Request: " + " ( none ) " + " ->" + "\n" + "  Delivery: " + response);

//                    }

//    ss->singleShot(1000, this, SLOT(get_list()));


//    } else if (userid == "unsigned") { //qInfo() << "user not signed in...";
//    }


//}
