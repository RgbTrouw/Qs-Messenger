/*   Qs Messenger Client v 1.0.2c Instant Messaging Application
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

 
#include "ui_MainWindow.h"
#include "MainWindow.h"

#include <QRegularExpressionMatch>
#include <QCryptographicHash>
#include <QRegularExpression>
#include <QSystemTrayIcon>
#include <QApplication>
#include <QFileDialog>
#include <QCloseEvent>
#include <QByteArray>
#include <QSettings>
#include <QProcess>
#include <QWidget>
#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QFont>


    #include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(),this->height());

    friendsWidget->setAttribute(Qt::WA_StyledBackground, true);
    friendsWidget->setAttribute(Qt::WA_Hover, true);


    this->setWindowTitle("Qs Messenger");
    this->setWindowIcon(QIcon("./Resources/icons/AppIcon.png"));


    QDir dir("./Resources/users/");
    if (!dir.exists()){
        QDir().mkdir("./Resources/users/");
    }

    showHideAction->setText("Hide");
    signInAction->setText("Sign In");
    closeAppAction->setText("Close");

    contextMenuFont.setPointSize(10);

    ui->availabilityDropDownMenu->setItemIcon(0,QIcon("./Resources/icons/smiley.png"));
    ui->availabilityDropDownMenu->setItemIcon(1,QIcon("./Resources/icons/smiley_busy.png"));
    ui->availabilityDropDownMenu->setItemIcon(2,QIcon("./Resources/icons/smiley_offline.png"));

    //friendsWidget->setSizePolicy(Qt:)
    ui->listLayout->addWidget(friendsWidget);
    ui->listLayout->setSpacing(0);
    //ui->listLayout->setMargin(0);

    notificationFont.setPointSize(8);
    ui->statusbar->setFont(notificationFont);

    ui->bannerLabel->setPixmap(QPixmap("./Resources/banner2.png"));
    ui->bannerLabel->hide();
    ui->MainAvatar->setIcon(QPixmap("./Resources/icons/avatarIcon.png"));

    // QDesktopWidget dWidget;
    // int screenWidth = dWidget.screen()->width();
    // int screenHeight = dWidget.screen()->height();


    this->statusBar()->showMessage("Disconnected");
    this->statusBar()->setStyleSheet("color: rgb(28, 110, 216);"); // green: rgb(60, 150, 0); red: rgb(224, 27, 36); yellow: rgb(246, 211, 45); blue: rgb(28, 110, 216);

    // *** CONNECT

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  socket


    connect(m_webSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(m_webSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

    connect(m_webSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));

    connect(m_webSocket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(onSslErrors(QList<QSslError>)));


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  user interface

    connect(closeAppAction, SIGNAL(triggered()), this, SLOT(closeApplication()));

    connect(signInAction, SIGNAL(triggered()), this, SLOT(signIn()));
    connect(ui->actionSign, SIGNAL(triggered()), this, SLOT(signIn()));

    connect(showHideAction, SIGNAL(triggered()), this, SLOT(showHideMainWindow()));

    connect(ui->actionAbout, &QAction::triggered, this, [=](){aboutWindow->show();});
    connect(ui->actionSettings, &QAction::triggered, this, [=](){settingsWindow->show();});


    connect(ui->signInButton, SIGNAL(clicked()), this, SLOT(signIn()));


    connect(ui->MainAvatar, SIGNAL(clicked()), this, SLOT(changeAvatar()));
    connect(ui->availabilityDropDownMenu, SIGNAL(currentIndexChanged(int)), this, SLOT(changeAvailability(int)));
    connect(ui->statusMessageLineEdit, SIGNAL(editingFinished()), this, SLOT(updateStatusMessage()));


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// pre login

    connect(ui->registerNewUserButton, SIGNAL(clicked()), this, SLOT(registerNewUserMenu()));
    connect(registerNewUserWindow, SIGNAL(server_request(QString)), this, SLOT(registrationRequest(QString)));

    connect(ui->resetPasswordButton, SIGNAL(clicked()), this, SLOT(recoverPasswordMenu()));
    connect(recoverPasswordWindow, SIGNAL(server_request(QString)), this, SLOT(recoverPasswordRequest(QString))); //?

    connect(settingsWindow, SIGNAL(updateHostAddress(QString)), this, SLOT(updateHostAddress(QString)));



    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// other windows

//    QFile inputFile("hostname");
//    if (inputFile.open(QIODevice::ReadOnly))
//    {
//       QTextStream in(&inputFile);
//       while (!in.atEnd())
//       {
//          QString line = in.readLine();
//          hostAddress = line.split(" ").at(0);
//       }
//       inputFile.close();
//    }

    hostAddress = savedSettings->value("hostAddress").toString();

    if(hostAddress != ""){
        settingsWindow->setSettings(hostAddress.split(":").at(0), hostAddress.split(":").at(1));
    } else {
        hostAddress = "qsmessenger.net:7080";
    }

    //qInfo() << hostAddress;
    //hostAddress = "";

    connectionManager();
    //reconnect();



    trayIcon->setContextMenu(trayMenu);
    trayIcon->setVisible(true);

    trayMenu->addAction(showHideAction);
    trayMenu->addAction(signInAction);
    trayMenu->addAction(closeAppAction);

    ui->actionSign->setText("Sign In");

    //hostnameAction->setText("Hostname");
    //ui->menuMessenger->addAction(hostnameAction);



    if (savedSettings->value("remember_credentials").toBool() ) {

        ui->usernamePrompt->setText(savedSettings->value("username").toString());
        ui->passwordPrompt->setText(savedSettings->value("password").toString());
        ui->autologinPrompt->setChecked(savedSettings->value("autologin").toBool());
        ui->invisible_Prompt->setChecked(savedSettings->value("invisible").toBool());

        ui->rememberPrompt->setChecked(savedSettings->value("remember_credentials").toBool());

    }

    if (savedSettings->value("autologin").toBool()){


        autoLoginTimer->singleShot(700, this, SLOT(autologin()));
    }

    onWindowsStartup();
    ui->stackedWidget->setCurrentIndex(0);

    ui->smiley_label->setMovie(movie);
    movie->jumpToNextFrame();


}

void MainWindow::onWindowsStartup() {

    QSettings registeryKey("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);   // Windows Startup Registery Key

    QString value = QCoreApplication::applicationFilePath(); //get absolute path of running exe
    QString apostroph = "\"";

    value.replace("/","\\");
    value = apostroph + value + apostroph ;

    registeryKey.setValue("Qs Messenger", value);

}

MainWindow::~MainWindow() { delete ui; }


void MainWindow::updateHostAddress(QString hostAddressValue){

    savedSettings->setValue("hostAddress", hostAddressValue);

    hostAddress = hostAddressValue;


    settingsWindow->setSettings(hostAddress.split(":").at(0), hostAddress.split(":").at(1));

    m_webSocket->disconnect();
    reconnect();

    //qInfo() << savedSettings->value("hostAddress").toString();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////  *** SOCKET ***  ///////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::onConnected()
{
     connected = true;

    this->statusBar()->showMessage("Connected");
    this->statusBar()->setStyleSheet("color: rgb(60, 150, 0);"); // green: rgb(60, 150, 0); red: rgb(224, 27, 36);

    //qDebug() << "Socket Connected";
    connect(m_webSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(onTextMessageReceived(QString)));

    connect(m_webSocket, SIGNAL(binaryMessageReceived(QByteArray)), this, SLOT(processBinaryMessage(QByteArray)));
    connect(m_webSocket, SIGNAL(binaryFrameReceived(QByteArray,bool)), this, SLOT(processBinaryFrame(QByteArray,bool)));
    //hostnameAction->disconnect();

    m_webSocket->sendTextMessage(QStringLiteral("session_id"));

}

void MainWindow::onDisconnected(){

    connected = false;

    trayIcon->setIcon(QIcon("./Resources/icons/smiley_offline.png"));
    signOut();

    this->statusBar()->showMessage("Disconnected");
    this->statusBar()->setStyleSheet("color: rgb(224, 27, 36);"); // green: rgb(60, 150, 0); red: rgb(224, 27, 36);

    this->statusBar()->showMessage("Connecting");
    this->statusBar()->setStyleSheet("color: rgb(28, 110, 216);"); // green: rgb(60, 150, 0); red: rgb(224, 27, 36); yellow: rgb(246, 211, 45); blue: rgb(28, 110, 216);

   reconnect();

}

void MainWindow::reconnect(){


    //qInfo() << hostAddress;

    m_webSocket->open(QUrl("wss://" + hostAddress));



}

void MainWindow::onSslErrors(QList<QSslError> errors) {

    qInfo() << errors;

    //m_webSocket.ignoreSslErrors();
}

void MainWindow::onSocketError(QAbstractSocket::SocketError error){

    qInfo() << error;

}

void MainWindow::connectionManager(){

    //qInfo() << "connection manager...";
    //qInfo() << m_webSocket->state();
    //qInfo() << connected;

    if (m_webSocket->state() == QAbstractSocket::ConnectedState && !connected){
        this->statusBar()->showMessage("Connected...");
        this->statusBar()->setStyleSheet("color: rgb(60, 150, 0);");

        onConnected();
    } else if (m_webSocket->state() == QAbstractSocket::UnconnectedState && connected){
        this->statusBar()->showMessage("Disconnected...");
        this->statusBar()->setStyleSheet("color: rgb(28, 110, 216);");

        onDisconnected();
    } else if (m_webSocket->state() == QAbstractSocket::ConnectingState && !connected){
        this->statusBar()->showMessage("Connecting...");
        this->statusBar()->setStyleSheet("color: rgb(28, 110, 216);");
    } else if (m_webSocket->state() == QAbstractSocket::UnconnectedState && !connected){
        this->statusBar()->showMessage("Connecting...");
        this->statusBar()->setStyleSheet("color: rgb(28, 110, 216);");

        reconnect();
    }

    QTimer::singleShot(2000, this, SLOT(connectionManager()));

}

void MainWindow::keepAlive(){

    if(m_webSocket->state() == QAbstractSocket::ConnectedState){
        m_webSocket->sendTextMessage("ping");
    }
    QTimer::singleShot(60000 * 60,this, SLOT(keepAlive()));
}

void MainWindow::onTextMessageReceived(QString message)
{

    if (message != previousMsgBuffer ){

    if (message.left(12) != "friends_list"){
       // qInfo() << message;
    }

    if ( message.indexOf("session_id:") == 0){
        session_id = message.split(":").at(1);
        //qInfo() << session_id;

        if(ui->autologinPrompt->isChecked()){
            signIn();
        }
    }

    if(message=="Could not login..."){
        this->statusBar()->showMessage(message);
        this->statusBar()->setStyleSheet("color: rgb(28, 110, 216);"); // green: rgb(60, 150, 0); red: rgb(224, 27, 36);
    }

    if(message.indexOf("User already signed in... :") == 0){

        QString loginToken = message.split(":").at(1);

        this->statusBar()->showMessage("Already signed in...");
        this->statusBar()->setStyleSheet("color: rgb(28, 112, 216);");

        QMessageBox msgBox;
        msgBox.setWindowTitle("Already Signed In");
        msgBox.setText("There is another session with the same username. Do you wish to disconnect the other client?");
        msgBox.setFont(contextMenuFont);
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);

        if(msgBox.exec() == QMessageBox::Yes){

            m_webSocket->sendTextMessage("disconnectOtherSession:" + loginToken );

          this->statusBar()->showMessage("Disconnecting other client...");
          this->statusBar()->setStyleSheet("color: rgb(28, 110, 216);");



        }else {
         // qInfo() << "no";
        }


    }

    if(message.indexOf("disconnected from other...") == 0){

        ui->autologinPrompt->setChecked(false);
        QMessageBox msgBox;
        msgBox.setWindowTitle("Disconnected");
        msgBox.setText("You have signed in from another client.");
        msgBox.setFont(contextMenuFont);
        //msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.addButton(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);

        if(msgBox.exec() == QMessageBox::Ok){
          //
        }else {
         // qInfo() << "no";
        }

    }


    if (message.indexOf("Login was successful... :") == 0){

        signInAction->setText("Sign Out");


        disconnect(signInAction, SIGNAL(triggered()), this, SLOT(signIn()));
        connect(signInAction, SIGNAL(triggered()), this, SLOT(signOut()));

        ui->actionSign->setText("Sign Out");
        disconnect(ui->actionSign, SIGNAL(triggered()), this, SLOT(signIn()));
        connect(ui->actionSign, SIGNAL(triggered()), this, SLOT(signOut()));

       // ui->menuMessenger->removeAction(hostnameAction);

        ui->stackedWidget->setCurrentIndex(1);
        ui->MainAvatar->setIcon(QPixmap("./Resources/icons/avatarIcon.png"));

        m_webSocket->sendTextMessage("getMyInfo");
        m_webSocket->sendTextMessage("getlist" );



        ui->actionReset_Password->setVisible(false);
        ui->actionActivate_New_User->setVisible(false);
        ui->actionToggle_List_View->setVisible(true);


        ui->actionFriend_Request->setVisible(true);

        retrieve_avatar();

        //ui->statusEdit->close();

        movie->jumpToFrame(0);
        movie->stop();

        QTimer::singleShot(1000, this, [=](){
            if(ui->availabilityDropDownMenu->currentIndex() != 2){
                trayIcon->setIcon(QIcon("./Resources/icons/smiley.png"));
            } else {
                trayIcon->setIcon(QIcon("./Resources/icons/smiley_offline.png"));
            }

        });


        if (message.split(":").at(1) != "0"){
        QDateTime *dt = new QDateTime();
        // Potential leak of memory pointed to by 'dt';


        this->statusBar()->showMessage("Last Login: " + dt->fromMSecsSinceEpoch(message.split(":").at(1).toLongLong()).toString("h:m ap dd.MMMM.yy"));
        // Potential leak of memory pointed to by 'dt';

       // this->statusBar()->setFont(contextMenuFont);
        this->statusBar()->setStyleSheet("color: rgb(60, 150, 0);");

        lastLoginCounter(message.split(":").at(1), 30);

        } else {this->statusBar()->showMessage("Welcome to QsMessenger...");
        this->statusBar()->setStyleSheet("color: rgb(28, 110, 216);");

            QTimer::singleShot(10000, this, [=](){this->statusBar()->clearMessage();});
        }
    }


    if ( message.indexOf("friends_list:|") == 0){



        for(int i=0; i< friendsWidget->groups.size(); i++){
            disconnect(friendsWidget->groups.at(i));
            for (int a=0; a< friendsWidget->groups.at(i)->peers.size(); a++){
                disconnect(friendsWidget->groups.at(i)->peers.at(a));
                disconnect(friendsWidget->groups.at(i)->peers.at(a)->imWidget);
                 delete friendsWidget->groups.at(i)->peers.at(a)->imWidget;
                 delete friendsWidget->groups.at(i)->peers.at(a);
                 friendsWidget->groups.at(i)->peers.clear();
                //friendsWidget->groups.at(i)->peers.at(a)->imWidget->close();
                //friendsWidget->groups.at(i)->peers.removeAt(a);

            }
            delete friendsWidget->groups.at(i);
            friendsWidget->groups.clear();

        }

        friendsWidget->groups.clear();
        friendsWidget->clearWidget();

        ui->listLayout->removeWidget(friendsWidget);


        friendsWidget = new FriendsListWidget();
        friendsWidget->set_data(message);
        ui->listLayout->addWidget(friendsWidget);
\

        for (int i =0; i < friendsWidget->groups.size(); i++){

            connect(friendsWidget->groups.at(i), SIGNAL(addToGroupSignal(QString)), this, SLOT(addToGroup(QString)));
            connect(friendsWidget->groups.at(i), SIGNAL(addNewGroupSignal()), this, SLOT(addNewGroup()));
            connect(friendsWidget->groups.at(i), SIGNAL(removeGroupSignal(QString)), this, SLOT(removeGroup(QString)));
            connect(friendsWidget->groups.at(i), SIGNAL(imGroupSignal(QString)), this, SLOT(imGroupWindow(QString)));


            for (int a =0; a < friendsWidget->groups.at(i)->peers.size(); a++){
                connect(friendsWidget->groups.at(i)->peers.at(a)->imWidget, SIGNAL(send_message(QString, QString)), this, SLOT(send_im(QString, QString)));
                connect(friendsWidget->groups.at(i)->peers.at(a)->imWidget, SIGNAL(send_file_request(QString, QString, QString, QString)), this, SLOT(send_file_request(QString, QString, QString, QString)));
                connect(friendsWidget->groups.at(i)->peers.at(a)->imWidget, SIGNAL(respond_file_request(QString, QString, bool)), this, SLOT(respond_file_request(QString, QString, bool)));
                connect(friendsWidget->groups.at(i)->peers.at(a)->imWidget, SIGNAL(send_file_payload(QString, QString, QString)), this, SLOT(send_file_payload(QString, QString, QString)));
                connect(friendsWidget->groups.at(i)->peers.at(a)->imWidget, SIGNAL(get_prev_messages(QString, QString)), this, SLOT(get_prev_messages(QString, QString)));
                connect(friendsWidget->groups.at(i)->peers.at(a)->imWidget, SIGNAL(have_read(QString)), this, SLOT(have_read(QString)));
                connect(friendsWidget->groups.at(i)->peers.at(a)->imWidget, SIGNAL(playAudio(QString)), this, SLOT(playAudio(QString)));
                connect(friendsWidget->groups.at(i)->peers.at(a)->imWidget, SIGNAL(clearArchiveSignal(QString)), this, SLOT(clearArchive(QString)));

                connect(friendsWidget->groups.at(i)->peers.at(a), SIGNAL(refreshPeerAvatar(QString)), this, SLOT(refreshPeerAvatar(QString)));
                connect(friendsWidget->groups.at(i)->peers.at(a), SIGNAL(removeUserSignal(QString)), this, SLOT(removeUser(QString)) );

                connect(friendsWidget->groups.at(i)->peers.at(a), SIGNAL(moveToGroupDownSignal(QString)), this, SLOT(moveToGroupDown(QString)) );
                connect(friendsWidget->groups.at(i)->peers.at(a), SIGNAL(moveToGroupUpSignal(QString)), this, SLOT(moveToGroupUp(QString)) );



                friendsWidget->groups.at(i)->peers.at(a)->imWidget->setWindowTitle(friendsWidget->groups.at(i)->peers.at(a)->name);
                if (ui->availabilityDropDownMenu->currentIndex() == 2) {
                    friendsWidget->groups.at(i)->peers.at(a)->imWidget->showHideNotice(false);
                } else {
                    friendsWidget->groups.at(i)->peers.at(a)->imWidget->showHideNotice(true);

                }



                friendsWidget->groups.at(i)->peers.at(a)->imWidget->myUsername = myUsername;
                friendsWidget->groups.at(i)->peers.at(a)->imWidget->myEmail = myEmail;

                QString server_request="peer_avatar:" + friendsWidget->groups.at(i)->peers.at(a)->email;
                m_webSocket->sendTextMessage(server_request.toUtf8());

            }
        }


    }

    searchPattern = "updateUser:*/*/*/*/*";

    if (QRegularExpression(QRegularExpression::wildcardToRegularExpression(searchPattern)).match(message).hasMatch()){

        QString parameters;
        parameters = message.split(":").at(1);

        //qInfo() << parameters;
        QString newAvailability = parameters.split("/").at(1);
        QString previousAvailability;

        for (int i=0; i<friendsWidget->groups.size(); i++){
            for (int a=0; a<friendsWidget->groups.at(i)->peers.size(); a++){
                if (friendsWidget->groups.at(i)->peers.at(a)->email == parameters.split("/").at(4)){

                    previousAvailability = friendsWidget->groups.at(i)->peers.at(a)->availability;

                    friendsWidget->groups.at(i)->peers.at(a)->set_plain_data(parameters);
                    friendsWidget->groups.at(i)->updateUsersOnline();

                    newAvailability = friendsWidget->groups.at(i)->peers.at(a)->availability;

                }

            }

        }


        if( (previousAvailability == "available" || previousAvailability == "busy") && newAvailability == "offline"){
            playAudio("./Resources/offlineNotification.wav");


        }
        else if( (newAvailability == "available" || newAvailability == "busy") && previousAvailability == "offline"){
            playAudio("./Resources/onlineNotification.wav");

        }


    }

    searchPattern = "addUserToGroup:*/*/*/*/*:*";

    if (QRegularExpression(QRegularExpression::wildcardToRegularExpression(searchPattern)).match(message).hasMatch()){

        QStringList parameters;
        parameters = message.split(":");
        //qInfo() << "add User: " + parameters.at(1) + " to Group: " + parameters.at(2);

        m_webSocket->sendTextMessage("getlist" );




    }

    searchPattern = "userInfo:*:*:*:*";

    if (QRegularExpression(QRegularExpression::wildcardToRegularExpression(searchPattern)).match(message).hasMatch()){


        QStringList parameters;
        parameters = message.split(":");

        //qInfo() << parameters;

        ui->usernameLabel->setText( " " + parameters.at(1));
        myUsername = parameters.at(1);
        myEmail = parameters.at(4);

        QDir dir("./Resources/users/" + myEmail);
        if (!dir.exists()){
            QDir().mkdir("./Resources/users/" + myEmail);
            QDir().mkdir("./Resources/users/" + myEmail + "/avatars/");
        }

        QByteArray byteArray = QByteArray::fromHex(parameters.at(2).toUtf8());
        QString statusMessage = byteArray.data();
        ui->statusMessageLineEdit->setText(statusMessage);

        if(parameters.at(3).toInt() != 3){
        ui->availabilityDropDownMenu->setCurrentIndex(parameters.at(3).toInt());
        } else {ui->availabilityDropDownMenu->setCurrentIndex(2);}

        for (int i = 0 ; i < friendsWidget->groups.size(); i++){
            for (int a = 0; a< friendsWidget->groups.at(i)->peers.size(); a++){
                friendsWidget->groups.at(i)->peers.at(a)->imWidget->myUsername = myUsername;
                friendsWidget->groups.at(i)->peers.at(a)->imWidget->myEmail = myEmail;
            }
        }
        //qInfo() << parameters.at(4); // last login;
    }

    searchPattern = "friendRequestAccepted:*";

    if (QRegularExpression(QRegularExpression::wildcardToRegularExpression(searchPattern)).match(message).hasMatch()){

         m_webSocket->sendTextMessage("getlist");

    }

    searchPattern = "unfriend:*";

    if (QRegularExpression(QRegularExpression::wildcardToRegularExpression(searchPattern)).match(message).hasMatch()){

         m_webSocket->sendTextMessage("getlist");

    }

    searchPattern = "im:*:*:*";

    if (QRegularExpression(QRegularExpression::wildcardToRegularExpression(searchPattern)).match(message).hasMatch()){

        //qInfo() << "new message received...";
        //qInfo() << message;
        QStringList parameters = message.split(":", Qt::KeepEmptyParts);

        if (parameters.size() == 4){
            QString messageHex = parameters.at(2);
            if (messageHex.size() > 0 && messageHex.size() % 2 == 0 && QRegularExpression("^[0-9A-Fa-f]+$").match(messageHex).hasMatch()){
                IM_WindowObject *imWindow = prepareImWindow(parameters.at(1));
                if (imWindow){
                    QByteArray byteArray = QByteArray::fromHex(messageHex.toUtf8());
                    QString message = QString::fromUtf8(byteArray);
                    imWindow->append_message(message,  parameters.at(3));
                }
            }
        }

    }

    searchPattern = "file:request:*:*:*:*";

    if (QRegularExpression(QRegularExpression::wildcardToRegularExpression(searchPattern)).match(message).hasMatch()){

        QStringList parameters = message.split(":", Qt::KeepEmptyParts);
        if (parameters.size() == 6){
            QString transferId = parameters.at(3);
            QString fileNameHex = parameters.at(4);
            if (fileNameHex.size() > 0 && fileNameHex.size() % 2 == 0 && QRegularExpression("^[0-9A-Fa-f]+$").match(fileNameHex).hasMatch()){
                QByteArray byteArray = QByteArray::fromHex(fileNameHex.toUtf8());
                QString fileName = QString::fromUtf8(byteArray);
                QString fileSize = parameters.at(5);
                IM_WindowObject *imWindow = prepareImWindow(parameters.at(2));

                if (imWindow){
                    imWindow->receiveFileRequest(transferId, fileName, fileSize);
                }
            }
        }

    }

    searchPattern = "file:response:*:*:*";

    if (QRegularExpression(QRegularExpression::wildcardToRegularExpression(searchPattern)).match(message).hasMatch()){

        QStringList parameters = message.split(":", Qt::KeepEmptyParts);
        if (parameters.size() == 5){
            QString transferId = parameters.at(3);
            QString response = parameters.at(4);

            if (response == "accepted" || response == "declined"){
                bool accepted = response == "accepted";
                IM_WindowObject *imWindow = prepareImWindow(parameters.at(2));
                if (imWindow){
                    imWindow->receiveFileResponse(transferId, accepted);
                }
            }
        }

    }


    searchPattern = "pm:*:*:*:*";

    if (QRegularExpression(QRegularExpression::wildcardToRegularExpression(searchPattern)).match(message).hasMatch()){

        //qInfo() << "archived message received...";
        QStringList parameters = message.split(":");

        //qInfo() << parameters;
        QString msgFrom = parameters.at(1);
        QString msgTo = parameters.at(2);
        QString msg = parameters.at(3);
        QString time = parameters.at(4);
        for(int i =0; i< friendsWidget->groups.size(); i++){

            for (int a = 0; a< friendsWidget->groups.at(i)->peers.size(); a++){
            if( (friendsWidget->groups.at(i)->peers.at(a)->imWidget->email == msgFrom && msgTo == myEmail) || (friendsWidget->groups.at(i)->peers.at(a)->imWidget->email == msgTo && msgFrom == myEmail)){

                friendsWidget->groups.at(i)->peers.at(a)->imWidget->show();
                friendsWidget->groups.at(i)->peers.at(a)->imWidget->setMyAvatar();
                friendsWidget->groups.at(i)->peers.at(a)->imWidget->setPeerAvatar();
                friendsWidget->groups.at(i)->peers.at(a)->imWidget->setWindowTitle(friendsWidget->groups.at(i)->peers.at(a)->name);
                QByteArray byteArray = QByteArray::fromHex(msg.toUtf8());
                QString message = byteArray.data();
                friendsWidget->groups.at(i)->peers.at(a)->imWidget->prepend_message(msgFrom, msgTo, message, time);
                friendsWidget->groups.at(i)->peers.at(a)->imWidget->myUsername = myUsername;

            }
        }
        }

    }

    searchPattern = "newfriendshiprequest:*";

    if (QRegularExpression(QRegularExpression::wildcardToRegularExpression(searchPattern)).match(message).hasMatch()){

        QStringList parameters = message.split(":");
        friendshipResponseWindow->from(parameters.at(1));

        connect(friendshipResponseWindow, SIGNAL(respond_fr(QString, QString)), this, SLOT(respondFriendRequest(QString, QString)));
        friendshipResponseWindow->show();

    }

    searchPattern = "userRemovedFromList:*";

    if (QRegularExpression(QRegularExpression::wildcardToRegularExpression(searchPattern)).match(message).hasMatch()){

        QStringList parameters = message.split(":");
        QString email = parameters.at(1);

        for (int i=0; i< friendsWidget->groups.size(); i++){
            for (int a=0; a< friendsWidget->groups.at(i)->peers.size(); a++ ){
                if (friendsWidget->groups.at(i)->peers.at(a)->email == email){
                    friendsWidget->groups.at(i)->peers.at(a)->imWidget->close();
                    friendsWidget->groups.at(i)->peers.at(a)->imWidget->disconnect();
                    friendsWidget->groups.at(i)->peers.at(a)->imWidget->deleteLater();
                    friendsWidget->groups.at(i)->peers.at(a)->disconnect();
                    friendsWidget->groups.at(i)->peers.at(a)->deleteLater();
                    delete friendsWidget->groups.at(i)->peers.at(a);
                    friendsWidget->groups.at(i)->peers.removeAt(a);
                }
            }
        }

        m_webSocket->sendTextMessage("getlist");

    }

    searchPattern = "Group already exists:*";

    if (QRegularExpression(QRegularExpression::wildcardToRegularExpression(searchPattern)).match(message).hasMatch()){
        QString groupName = message.split(":").at(1);

        addNewGroupWindow->feedback("Group already exists...");

    }

    searchPattern = "New Group Created:*";

    if (QRegularExpression(QRegularExpression::wildcardToRegularExpression(searchPattern)).match(message).hasMatch()){

        m_webSocket->sendTextMessage("getlist");

        QString groupName = message.split(":").at(1);

        addNewGroupWindow->feedback("New group created...");

    }

    searchPattern = "Group Deleted:*";

    if (QRegularExpression(QRegularExpression::wildcardToRegularExpression(searchPattern)).match(message).hasMatch()){

        QString groupName = message.split(":").at(1);
        friendsWidget->removeGroup(groupName);

        m_webSocket->sendTextMessage("getlist");


    }

    searchPattern = "userMovedToGroup:*:*";

    if (QRegularExpression(QRegularExpression::wildcardToRegularExpression(searchPattern)).match(message).hasMatch()){

        m_webSocket->sendTextMessage("getlist");

    }

    if (message == "Friendship request accepted..."){
        m_webSocket->sendTextMessage("getlist");
    }


    if (message == "Friendship request has been sent..." || message == "Request allready sent..." || message == "Email is not registered..." || message == "You are allready friends..."){

        addNewUserWindow->feedback(message);
        //qInfo() << message;
    }

    if (message == "Email already in use or not activated..." || message == "Registration success... Please activate your account..." || "Activation success..." || message == "Activation failed..."  || message == "Activation code resent..." || message == "Email not registered or already activated..." ){

        registerNewUserWindow->server_feedback(message);

    }


    if (message == "Reset code sent..." || message == "Email is not registered or activated..." || message == "Password changed..." || message == "Reset code not validated..." || message == "Password must not be null..." ) {

        recoverPasswordWindow->server_feedback(message);
    }

    previousMsgBuffer = message;

   }

    searchPattern = "ServerMessage:*";

    if (QRegularExpression(QRegularExpression::wildcardToRegularExpression(searchPattern)).match(message).hasMatch()){

        QMessageBox msgBox;
        msgBox.setWindowTitle("Qs Messenger Server");
        msgBox.setText(message.split(":").at(1));
        msgBox.setFont(contextMenuFont);

        msgBox.exec();

    }


}

void MainWindow::processBinaryMessage(QByteArray data){

    if (data.left(5) == "file:"){
        return;
    }

    if (data.left(12) == "your_avatar:"){

        QString path = "./Resources/users/" + myEmail + "/" + myUsername;
        QFile avatar(path);
        if(avatar.open(QIODevice::ReadWrite)){
        avatar.write(data.right(data.size() - 12));

        ui->MainAvatar->setIcon(QPixmap(path));

        }
    }


    QStringList header = QString(data.left(50)).split(":");


    if(header.at(0) == "peer_avatar"){

        QString peerEmail = header.at(1);

        QByteArray buffer = data.right(data.size() - 11 - peerEmail.size() - 2);

        QString path = "./Resources/users/" + myEmail + "/avatars/" + peerEmail;
        QFile avatar(path);
        if(avatar.open(QIODevice::WriteOnly)){
        avatar.write(buffer);
        }

    }

}

void MainWindow::processBinaryFrame(QByteArray data, bool isLastFrame){

    if (data.left(5) == "file:"){

        int firstColon = data.indexOf(':');
        int secondColon = data.indexOf(':', firstColon + 1);
        int thirdColon = data.indexOf(':', secondColon + 1);

        if (firstColon != -1 && secondColon != -1 && thirdColon != -1){
            incomingFileTransferPeer = QString::fromUtf8(data.mid(firstColon + 1, secondColon - firstColon - 1));
            incomingFileTransferId = QString::fromUtf8(data.mid(secondColon + 1, thirdColon - secondColon - 1));

            QByteArray payload = data.mid(thirdColon + 1);
            IM_WindowObject *imWindow = prepareImWindow(incomingFileTransferPeer);
            if (imWindow){
                imWindow->receiveFilePayload(incomingFileTransferId, payload, isLastFrame);
            }
        }

        if (isLastFrame){
            incomingFileTransferPeer = "";
            incomingFileTransferId = "";
        }

        return;
    }

    if (incomingFileTransferPeer.size() > 0 && incomingFileTransferId.size() > 0){
        IM_WindowObject *imWindow = prepareImWindow(incomingFileTransferPeer);
        if (imWindow){
            imWindow->receiveFilePayload(incomingFileTransferId, data, isLastFrame);
        }

        if (isLastFrame){
            incomingFileTransferPeer = "";
            incomingFileTransferId = "";
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////  *** MAIN WINDOW ***  //////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::lastLoginCounter(QString time, int counter){


    if(ticker){
    if (counter > 0){

        QDateTime *dt = new QDateTime();
        // Potential leak of memory pointed to by 'dt';


        this->statusBar()->showMessage("Last Login: " + dt->fromMSecsSinceEpoch(time.toLongLong()).toString("dd.MMMM.yy hh:mm") + " (" + QString::number(counter) + "s)");
        // Potential leak of memory pointed to by 'dt';

        this->statusBar()->setStyleSheet("color: rgb(12, 12, 12);");

        counter = counter - 1;

        QTimer::singleShot(1000, this, [=](){lastLoginCounter(time, counter);});
    } else {this->statusBar()->clearMessage();

    }
    }
}

void MainWindow::retrieve_avatar(){ m_webSocket->sendTextMessage("retrieve_avatar" ); }

void MainWindow::refreshPeerAvatar(QString email){  m_webSocket->sendTextMessage("peer_avatar:" + email ); }

void MainWindow::addToGroup(QString groupName){


    addNewUserWindow = new FriendRequestObject();
    addNewUserWindow->setWindowTitle("Add To Group: " + groupName);
    addNewUserWindow->show();

    connect(addNewUserWindow, &FriendRequestObject::addNewUser, this, [=](){ m_webSocket->sendTextMessage("addNewUser:" + addNewUserWindow->email + ":" + groupName) ;});

}



void MainWindow::addNewGroup(){

    addNewGroupWindow->resetInput();
    addNewGroupWindow->show();
    connect(addNewGroupWindow, SIGNAL(addNewGroupSignal(QString)), this, SLOT(addNewGroupConfirmation(QString)));
}

void MainWindow::addNewGroupConfirmation(QString groupName){

    m_webSocket->sendTextMessage("addNewGroup:" + groupName);
}

void MainWindow::removeGroup(QString groupName){

    //qInfo() << "remove group " + groupName + "...";
    QMessageBox msgBox;
    msgBox.setWindowTitle("Remove Group");
    msgBox.setText("Are you sure you want to remove the '" + groupName + "' group with all underlaying users?");
    msgBox.setFont(contextMenuFont);
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes){
      m_webSocket->sendTextMessage("removeGroup:" + groupName );
    }else {
     // qInfo() << "no";
    }

}

void MainWindow::removeUser(QString email){

    QString username;

    for (int i =0; i < friendsWidget->groups.size(); i++){
        for (int a=0; a< friendsWidget->groups.at(i)->peers.size(); a++){
            if (friendsWidget->groups.at(i)->peers.at(a)->email == email){

                username = friendsWidget->groups.at(i)->peers.at(a)->name;
            }
        }
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("Remove User");
    msgBox.setText("Are you sure you want to remove the user '" + username + "' from group?");
    msgBox.setFont(contextMenuFont);
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::Yes){

       m_webSocket->sendTextMessage("removeUser:" + email );

    }else {

    }

}

void MainWindow::moveToGroupDown(QString email){

    QString targetGroupName;

    for(int i=0; i< friendsWidget->groups.size(); i++){

        for (int a=0; a< friendsWidget->groups.at(i)->peers.size(); a++){

            if (friendsWidget->groups.at(i)->peers.at(a)->email == email){


                if(i != friendsWidget->groups.size() - 1){
                    targetGroupName = friendsWidget->groups.at(i + 1)->group_name;
                } else {targetGroupName = friendsWidget->groups.at(0)->group_name;}


                a=friendsWidget->groups.at(i)->peers.size();
                i=friendsWidget->groups.size();

                break;
            }
        }

    }

     m_webSocket->sendTextMessage("moveToGroup:" + email + ":" + targetGroupName);

}

void MainWindow::moveToGroupUp(QString email){

    QString targetGroupName;

    for(int i=0; i< friendsWidget->groups.size(); i++){

        for (int a=0; a< friendsWidget->groups.at(i)->peers.size(); a++){

            if (friendsWidget->groups.at(i)->peers.at(a)->email == email){

                if(i != 0 ){
                    targetGroupName = friendsWidget->groups.at(i - 1)->group_name;
                } else {targetGroupName = friendsWidget->groups.last()->group_name;}


                a=friendsWidget->groups.at(i)->peers.size();
                i=friendsWidget->groups.size();

                break;
            }
        }

    }

    //qInfo() << "move up " + email + " to group " + targetGroupName;
    m_webSocket->sendTextMessage("moveToGroup:" + email + ":" + targetGroupName);

}

void MainWindow::imGroupWindow(QString groupName){

    qInfo() << "im group " + groupName;

    IM_Group *imGroupWindow = new IM_Group();
    imGroupWindow->groupName = groupName;
    connect(imGroupWindow, SIGNAL(sendGroupMessageSignal(QString, QString)), this, SLOT(imGroup(QString, QString)));

    imGroupWindow->show();
    imGroupWindow->setWindowTitle("IM to Group: " + groupName);


}

void MainWindow::imGroup(QString message, QString groupName){

        for(int i=0; i< friendsWidget->groups.size(); i++){
            if(friendsWidget->groups.at(i)->group_name == groupName){
                for(int a=0; a< friendsWidget->groups.at(i)->peers.size(); a++){
                    send_im(friendsWidget->groups.at(i)->peers.at(a)->email, message);
                }
            }
        }

}

void MainWindow::respondFriendRequest(QString email, QString response ){

    m_webSocket->sendTextMessage("respondAddNewUserRequest:" + email + ":" + response  );

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// tray menus


void MainWindow::changeAvatar()
{
    QFileDialog dialog(nullptr,  "Images (*.png)");

    dialog.setNameFilter("*.png");
    dialog.exec();

    QByteArray picByteArray;
    QStringList path = dialog.selectedFiles();

    if(path.at(0).left(path.at(0).size()).right(4) == ".png" || path.at(0).left(path.at(0).size()).right(4) == ".PNG" ){

    QFile pic(path.at(0));
    if (pic.open(QIODevice::ReadOnly)){;
        picByteArray = pic.readAll();


        picByteArray.prepend("myAvatar:");

        ui->MainAvatar->setIcon(QPixmap(path.at(0)));
        //m_webSocket.sendTextMessage("upload_avatar:" );
        m_webSocket->sendBinaryMessage(picByteArray);
        QString path2 = "./Resources/users/" + myEmail + "/";

        path2.append(myUsername);
        QFile::remove(path2);
        QFile::copy(path.at(0), path2);

    }
    }
}

void MainWindow::autologin(){ this->signIn();}

void MainWindow::signIn() {

    //movie->start();

    QString username = ui->usernamePrompt->text();
    QString password = ui->passwordPrompt->text();

    QByteArray hash = password.toUtf8();
    password = QCryptographicHash::hash(hash, QCryptographicHash::Sha256).toHex();


    if (ui->rememberPrompt){


        savedSettings->setValue("username", ui->usernamePrompt->text());
        savedSettings->setValue("password", password);
        savedSettings->setValue("autologin", ui->autologinPrompt->isChecked() );
        savedSettings->setValue("invisible", ui->invisible_Prompt->isChecked() );
        savedSettings->setValue("remember_credentials", ui->rememberPrompt->isChecked());

    }


    if (ui->rememberPrompt->checkState()){

        savedSettings->setValue("remember_credentials", true);
        savedSettings->setValue("username", ui->usernamePrompt->text());
        savedSettings->setValue("password", ui->passwordPrompt->text());
        savedSettings->setValue("autologin", ui->autologinPrompt->checkState());
        savedSettings->setValue("invisible", ui->invisible_Prompt->checkState());

    }

    QString request =  "login:" + username + ":" + password + ":" ;
    QString visibility;

    if (ui->invisible_Prompt->isChecked()){visibility = "2";}
    else if (!ui->invisible_Prompt->isChecked()) {visibility = "0";}

    request.append(visibility);
    m_webSocket->sendTextMessage(request);

    registerNewUserWindow->close();
    recoverPasswordWindow->close();

    ticker=true;
}

void MainWindow::signOut()
{
    //ui->menuMessenger->addAction(hostnameAction);
    signInAction->setText("Sign In");
    disconnect(signInAction, SIGNAL(triggered()), this, SLOT(signOut()));
    connect(signInAction, SIGNAL(triggered()), this, SLOT(signIn()));

    ui->actionSign->setText("Sign In");
    disconnect(ui->actionSign, SIGNAL(triggered()), this, SLOT(signOut()));
    connect(ui->actionSign, SIGNAL(triggered()), this, SLOT(signIn()));

    ui->statusMessageLineEdit->setText("");
    m_webSocket->sendTextMessage("sign_out");

    addNewUserWindow->close();
    addNewGroupWindow->close();
    friendshipResponseWindow->close();



    for(int i=0; i<friendsWidget->groups.size(); i++){
        for(int a=0; a<friendsWidget->groups.at(i)->peers.size(); a++){
            friendsWidget->groups.at(i)->peers.at(a)->imWidget->close();
        }
    }
     friendsWidget->groups.clear();

     friendsWidget->close();
    ui->stackedWidget->setCurrentIndex(0);

    ui->actionToggle_List_View->setVisible(false);
    ui->actionActivate_New_User->setVisible(true);
    ui->actionReset_Password->setVisible(true);
    ui->actionFriend_Request->setVisible(false);

    if (!ui->rememberPrompt->isChecked()){
        ui->usernamePrompt->setText("");
        ui->passwordPrompt->setText("");
        ui->rememberPrompt->setCheckState(Qt::Unchecked);
        ui->autologinPrompt->setCheckState(Qt::Unchecked);
        ui->invisible_Prompt->setCheckState(Qt::Unchecked);

    }

    QString username = "";

    movie->jumpToFrame(0);

    trayIcon->setIcon(QIcon("./Resources/icons/smiley_offline.png"));

    this->statusBar()->clearMessage();
    this->statusBar()->showMessage("Connected");
    this->statusBar()->setStyleSheet("color: rgb(60, 150, 0);"); // green: rgb(60, 150, 0); red: rgb(224, 27, 36);

    ticker=false;

}

void MainWindow::changeAvailability(int index)
{

    QString param="set_availability:";
    param.append(QString::number(index));
    m_webSocket->sendTextMessage(param);

    updateStatusMessage();

    if (ui->availabilityDropDownMenu->currentIndex() == 2){
        trayIcon->setIcon(QIcon("./Resources/icons/smiley_offline.png"));
    } else if (ui->availabilityDropDownMenu->currentIndex() == 0){
        trayIcon->setIcon(QIcon("./Resources/icons/smiley.png"));
    }  else if (ui->availabilityDropDownMenu->currentIndex() == 1){
        trayIcon->setIcon(QIcon("./Resources/icons/smiley_busy.png"));
    }

    for (int i=0; i < friendsWidget->groups.size(); i++){
        for (int a=0; a< friendsWidget->groups.at(i)->peers.size(); a++){
            if (ui->availabilityDropDownMenu->currentIndex() == 2){
                friendsWidget->groups.at(i)->peers.at(a)->imWidget->showHideNotice(false);
            } else {
                friendsWidget->groups.at(i)->peers.at(a)->imWidget->showHideNotice(true);

            }
        }
    }

}


void MainWindow::closeEvent (QCloseEvent *event) { event->ignore(); this->hide(); showHideAction->setText("Show"); }
void MainWindow::showHideMainWindow() { if (this->isVisible()){ this->hide(); showHideAction->setText("Show"); } else if (!this->isVisible()){ int x=1642; int y=42; this->setGeometry(x,y,280,900); this->show(); this->activateWindow(); showHideAction->setText("Hide"); } }
void MainWindow::closeApplication() {

    QMessageBox msgBox;
    msgBox.setWindowTitle("Close QsMessenger");
    msgBox.setText("Are you sure you want to exit?");
    msgBox.setFont(contextMenuFont);
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes){
       this->close(); QCoreApplication::exit(0);
    }else {
     // qInfo() << "no";
    }


}

void MainWindow::updateStatusMessage() { QString qr="set_status:";
                                         QString statusMessage = ui->statusMessageLineEdit->text();
                                         QByteArray byteArray = statusMessage.toUtf8();
                                         qr.append(byteArray.toHex()); m_webSocket->sendTextMessage(qr); }


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////  *** AFTER LOGIN ***  //////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// messages

void MainWindow::send_im(QString peerEmail, QString message){

    QString request = "im:";
    request.append(peerEmail);
    request.append(":");
    QByteArray byteArray = message.toUtf8();
    request.append(byteArray.toHex());
    m_webSocket->sendTextMessage(request);

}

void MainWindow::send_file_request(QString peerEmail, QString transferId, QString fileName, QString fileSize){

    QString request = "file:request:";
    request.append(peerEmail);
    request.append(":");
    request.append(transferId);
    request.append(":");
    request.append(fileName.toUtf8().toHex());
    request.append(":");
    request.append(fileSize);
    m_webSocket->sendTextMessage(request);

}

void MainWindow::respond_file_request(QString peerEmail, QString transferId, bool accepted){

    QString request = "file:response:";
    request.append(peerEmail);
    request.append(":");
    request.append(transferId);
    request.append(":");
    if (accepted){
        request.append("accepted");
    } else {
        request.append("declined");
    }
    m_webSocket->sendTextMessage(request);

}

void MainWindow::get_prev_messages(QString peerEmail, QString index){

    QString request = "previous:";
    request.append(peerEmail);
    request.append(":");
    request.append(index);
    m_webSocket->sendTextMessage(request);

}

void MainWindow::send_file_payload(QString peerEmail, QString transferId, QString filePath){

    IM_WindowObject *imWindow = prepareImWindow(peerEmail);
    if (!imWindow){
        return;
    }

    QFile file(filePath);
    if (!file.exists() || !file.open(QIODevice::ReadOnly)){
        imWindow->completeOutgoingFileTransfer(transferId, false, " Failed to open file for sending");
        return;
    }

    if (m_webSocket->state() != QAbstractSocket::ConnectedState){
        file.close();
        imWindow->completeOutgoingFileTransfer(transferId, false, " Connection lost while sending file");
        return;
    }

    QByteArray header = "file:";
    header.append(peerEmail.toUtf8());
    header.append(":");
    header.append(transferId.toUtf8());
    header.append(":");

    if (m_webSocket->sendBinaryFrame(header, file.size() == 0) == -1){
        file.close();
        imWindow->completeOutgoingFileTransfer(transferId, false, " Failed to queue file transfer");
        return;
    }

    const qint64 chunkSize = 65536;
    bool failed = false;
    while (!file.atEnd()){
        QByteArray chunk = file.read(chunkSize);
        bool lastFrame = file.atEnd();
        if (m_webSocket->sendBinaryFrame(chunk, lastFrame) == -1){
            failed = true;
            break;
        }
    }
    file.close();

    if (failed){
        imWindow->completeOutgoingFileTransfer(transferId, false, " Failed to queue file transfer");
        return;
    }

    imWindow->completeOutgoingFileTransfer(transferId, true, " File transfer queued: \"" + QFileInfo(filePath).fileName() + "\"");

}

void MainWindow::have_read(QString peerEmail){
    //qInfo() << "have_read:" + peerEmail;
    m_webSocket->sendTextMessage("have_read:" + peerEmail);
}

void MainWindow::playAudio(QString path){

   // audioPlayer->setMedia(QUrl::fromLocalFile(path));  // or // audioPlayer->setSource(QUrl::fromLocalFile(path));

    audioEffect->setSource(QUrl::fromLocalFile(path));
    audioEffect->setLoopCount(1);
    audioEffect->setVolume(0.75f);
    audioEffect->play();
}

IM_WindowObject *MainWindow::prepareImWindow(QString peerEmail){

    for(int i =0; i< friendsWidget->groups.size(); i++){

        for (int a = 0; a< friendsWidget->groups.at(i)->peers.size(); a++){
        if( friendsWidget->groups.at(i)->peers.at(a)->email == peerEmail){

            friendsWidget->groups.at(i)->peers.at(a)->imWidget->show();
            friendsWidget->groups.at(i)->peers.at(a)->imWidget->setMyAvatar();
            friendsWidget->groups.at(i)->peers.at(a)->imWidget->setPeerAvatar();
            friendsWidget->groups.at(i)->peers.at(a)->imWidget->setWindowTitle(friendsWidget->groups.at(i)->peers.at(a)->name);
            friendsWidget->groups.at(i)->peers.at(a)->imWidget->myUsername = myUsername;
            return friendsWidget->groups.at(i)->peers.at(a)->imWidget;
            }
        }
    }

    return nullptr;
}

void MainWindow::clearArchive(QString peerEmail){

    m_webSocket->sendTextMessage("clearArchive:" + peerEmail);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////  *** PRE LOGIN ***  //////////////////////////////////////////////////////////////////////////////////////////////////


void MainWindow::recoverPasswordMenu() { recoverPasswordWindow->close(); recoverPasswordWindow = new RecoverPasswordObject(); recoverPasswordWindow->show();
                                         connect(recoverPasswordWindow, SIGNAL(server_request(QString)), this, SLOT(recoverPasswordRequest(QString))); }

void MainWindow::recoverPasswordRequest(QString request){  m_webSocket->sendTextMessage(request.toUtf8()); }


void MainWindow::registerNewUserMenu() { registerNewUserWindow->close(); registerNewUserWindow = new RegisterNewUserObject(); registerNewUserWindow->show();
                                         connect(registerNewUserWindow, SIGNAL(server_request(QString)), this, SLOT(registrationRequest(QString))); }

void MainWindow::registrationRequest(QString request) {  m_webSocket->sendTextMessage(request); }




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////  *** OTHER *** /////////////////////////////////////////////////////////////////////////////////////////////////////


void MainWindow::delay(int seconds) { QTime theTime= QTime::currentTime().addSecs(seconds); while (QTime::currentTime() < theTime){ QCoreApplication::processEvents(QEventLoop::AllEvents, 100); } }



////////////////////////////////////////////////////////////////////////////////////  THE END  ///////////////////////////////////////////////////////////////////////////////////////////////////////
