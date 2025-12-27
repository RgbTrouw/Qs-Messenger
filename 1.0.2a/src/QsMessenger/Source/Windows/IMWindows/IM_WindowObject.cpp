/*   QsMessenger Client v 1.0.2a Instant Messaging Application
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

#include "Headers/IM_WindowObject.h"
#include "Headers/SmileysObject.h"
#include "ui_IM_WindowObject.h"

#include <QTextBrowser>
#include <QCloseEvent>
#include <QSizePolicy>
#include <QScrollBar>
#include <QDateTime>
#include <QMenuBar>
#include <QSound>
#include <QTimer>
#include <QFile>
#include <QTime>

    #include <QDebug>


IM_WindowObject::IM_WindowObject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IM_WindowObject)
{
    ui->setupUi(this);

    vLayout->setContentsMargins(0,0,0,0);
    vLayout->setSpacing(0);


    ui->webcamButton->setIcon(QIcon("./Resources/icons/webcam.png"));
    ui->offlineIcon->setPixmap(QPixmap("./Resources/icons/smiley_offline.png"));


    QMenuBar* menuBar = new QMenuBar();
    QMenu *fileMenu = new QMenu("Conversation");
    menuBar->addMenu(fileMenu);
    fileMenu->addAction(ui->actionLoad_Previous_Messages);
    //fileMenu->addAction(ui->actionUnfriend_Contact);

    connect(ui->actionLoad_Previous_Messages, SIGNAL(triggered()), this, SLOT(loadPreviousMessages()));


    this->layout()->setMenuBar(menuBar);

    this->setWindowIcon(QIcon("./Resources/icons/AppIcon.png"));

    setMyAvatar();
    setPeerAvatar();

    ui->smileysButton->setIcon(QIcon("./Resources/icons/smiley.png"));
    ui->buzzButton->setIcon(QIcon("./Resources/icons/buzz.png"));
    ui->sendFileButton->setIcon(QIcon("./Resources/icons/paperclip.png"));
    ui->imagesButton->setIcon(QIcon("./Resources/icons/images.png"));

    connect(ui->buzzButton, SIGNAL(clicked()), this, SLOT(sendBuzz()));

    ui->myAvatar->setPixmap(QPixmap("./Resources/icons/avatarIcon.png"));
    //ui->myAvatar->hide();

    connect(ui->sendMsgButton, SIGNAL(clicked()), this, SLOT(sendMsg()));

}

IM_WindowObject::~IM_WindowObject()
{
    this->disconnect();
    delete ui;
}

void IM_WindowObject::deelay()
{
    QTime theTime= QTime::currentTime().addMSecs(100);
    while (QTime::currentTime() < theTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void IM_WindowObject::setMyAvatar(){

    //qInfo() << "Set Avatar..";

    //qInfo() << myEmail;
    //qInfo() << myUsername;

    QString path = "./Resources/users/" + myEmail + "/" + myUsername;
    //path.append(myUsername);
    if (QFile::exists(path)){
        QFile file(path);
    if(file.size() > 0){
        ui->myAvatar->setPixmap(QPixmap(path));
        //qInfo() << QPixmap(path);
    }} else {
        //qInfo() << "1";
        ui->myAvatar->setPixmap(QPixmap("./Resources/icons/avatarIcon.png"));
    }
}

void IM_WindowObject::setPeerAvatar(){


    QString path = "./Resources/users/" + myEmail + "/avatars/" + email;
    //path.append(peer_name);



    if (QFile::exists(path)){

        QFile file(path);

         if (QFile::exists(path)){
        if(file.size() > 0){

        ui->peerAvatar->setPixmap(QPixmap(path));
        //qInfo() << path;

        }}
    } else {
        ui->peerAvatar->setPixmap(QPixmap("./Resources/icons/avatarIcon.png"));
    }
}

void IM_WindowObject::sendMsg()
{
    //qInfo() << myUsername;

    if (ui->sendMessageBox->toPlainText().size() > 0){

        if (ui->sendMessageBox->toPlainText() == "<ding>"){

            sendBuzz();

        } else {



       conversationList.append(ui->sendMessageBox->toPlainText() + "<br></br>");

       conversationList.last().prepend("<span style='color: rgb(52, 101, 164);'>" + myUsername + ": " + "</span>");


       QString conversationBuffer = ui->conversationTextBox->toHtml();

       conversationBuffer.replace(QRegExp("<!DOCTYPE*</body></html>", Qt::CaseInsensitive ,QRegExp::Wildcard) ,"<html><body>");

       conversationBuffer.replace("\n", "");
       conversationBuffer.replace("<br>", "");
       conversationBuffer.replace("<br />", "");
       conversationBuffer.replace("<p>", "");
       conversationBuffer.replace("<p style", "<div style");
       conversationBuffer.replace("-qt-paragraph-type:empty; ", "");
       conversationBuffer.replace("</br>", "");
       conversationBuffer.replace("</p>", "");

       for (int i=0; i< conversationList.count(); i++){
       conversationBuffer.append(conversationList.at(i));
       }
       conversationBuffer.append("</body></html>");

       //qInfo() << conversationBuffer;
       //qInfo() << conversationList;

       ui->conversationTextBox->setHtml(conversationBuffer);

        }

        emit send_message(email, ui->sendMessageBox->toPlainText());
        ui->sendMessageBox->setText("");

    }


}

void IM_WindowObject::append_message(QString message, QString time){

    this->show();
    QTimer::singleShot(2000, this, [=](){ emit have_read(email);});
//    haveRead = false;

//    if (this->isActiveWindow()){
//        //qInfo() << "has focus...";


//        haveRead == true;
//    } else {
//        //qInfo() << "doesn't have focus...";
//    }

    if (message == "<ding>"){


//        this->setWindowState(Qt::WindowState::WindowActive);
//        this->show();
//        this->raise();
//        this->activateWindow();

        conversationBuffer = "<html><body>";

        conversationList.append("<span style='color: rgb(204, 0, 0);'>BUZZ</span><br></br>");

        for(int i=0; i<conversationList.count(); i++){
            conversationBuffer.append(conversationList.at(i));
        }

        conversationBuffer.append("</body></html>");

        QSound::play("./Resources/ding-dong.wav");

         ui->conversationTextBox->setHtml(conversationBuffer);

         for (int i = 0; i < 4; i++){

             int xa;
             int ya;

             xa = this->geometry().x() + qrand() % ((16 + 1) - - 16) + -  16;
             ya = this->geometry().y() + qrand() % ((16 + 1) - - 16) + -  16;

             this->setGeometry(xa,ya, this->geometry().width(), this->geometry().height());
             deelay();
}
    } else {



    if (conversationList.size()>0){
        conversationList.last().append(peer_name + ": " + message +  "<br></br>");
    } else {
        conversationList.append(peer_name + ": "  + message + "<br></br>");
    }


    QString conversationBuffer = ui->conversationTextBox->toHtml();

    for (int i =0; i < conversationList.count(); i++){
        conversationBuffer.append(conversationList.at(i));
    }

    conversationBuffer.replace(QRegExp("<!DOCTYPE*</body></html>", Qt::CaseInsensitive ,QRegExp::Wildcard) ,"<html><body>");

    conversationBuffer.replace("\n", "");
    //conversationBuffer.replace("<br>", "");
    conversationBuffer.replace("<br />", "");
    conversationBuffer.replace("<p>", "");
    conversationBuffer.replace("<p style", "<div style");
    conversationBuffer.replace("-qt-paragraph-type:empty; ", "");
    conversationBuffer.replace("</br>", "");
    conversationBuffer.replace("</p>", "");

    //conversationBuffer.prepend(conversationList.last());

    conversationBuffer.append("</body></html>");

     ui->conversationTextBox->setHtml(conversationBuffer);

     ui->conversationTextBox->verticalScrollBar()->setValue(ui->conversationTextBox->verticalScrollBar()->maximum());

     //qInfo() << conversationBuffer;

     qint64 tm = time.toULongLong();

     QDateTime *dt = new QDateTime();

     ui->notification_label->setText(" Last message received at: " + dt->fromMSecsSinceEpoch(tm).toString("dd.MMMM.yy hh:mm:ss"));

    }
}

void IM_WindowObject::prepend_message(QString msgFrom, QString msgTo, QString message,  QString time){

    if (msgFrom == myEmail){
            if (email == myEmail){
                conversationList.prepend(myUsername + ":   " + message + "<br></br>" );
                conversationList.prepend("<span style='color: rgb(52, 101, 164);'>" + myUsername + ":   " + "</span>" + message + "<br></br>");
            } else {
                conversationList.prepend("<span style='color: rgb(52, 101, 164);'>" + myUsername + ":   " + "</span>" + message + "<br></br>");
            }
        } else {
                conversationList.prepend(peer_name + ":   " + message + "<br></br>" );
        }

    QString conversationBuffer = ui->conversationTextBox->toHtml();

    for (int i =0; i < conversationList.count(); i++){
        conversationBuffer.append(conversationList.at(i));
    }

    conversationBuffer.replace(QRegExp("<!DOCTYPE*</body></html>", Qt::CaseInsensitive ,QRegExp::Wildcard) ,"<html><body>");
    conversationBuffer.replace("\n", "");
    //conversationBuffer.replace("<br>", "");
    conversationBuffer.replace("<br />", "");
    conversationBuffer.replace("<p>", "");
    conversationBuffer.replace("<p style", "<div style");
    conversationBuffer.replace("-qt-paragraph-type:empty; ", "");
    conversationBuffer.replace("</br>", "");
    conversationBuffer.replace("</p>", "");

    conversationBuffer.append("</body></html>");
    ui->conversationTextBox->setHtml(conversationBuffer);

    ui->conversationTextBox->verticalScrollBar()->setValue(ui->conversationTextBox->verticalScrollBar()->minimum());
    //qInfo() << conversationBuffer;

}

void IM_WindowObject::closeEvent (QCloseEvent *event)
{
        ui->conversationTextBox->setText("");
        ui->sendMessageBox->setText("");
        event->accept();
        previousMsgIndex = 0;
        ui->conversationTextBox->setText("");
        conversationList.clear();
        conversationBuffer.clear();

}

void IM_WindowObject::sendBuzz()
{
    //qInfo() << this->geometry();


    conversationBuffer = "<html><body>";

    conversationList.append("<span style='color: rgb(204, 0, 0);'>BUZZ</span><br></br>");

    for(int i=0; i<conversationList.count(); i++){
        conversationBuffer.append(conversationList.at(i));
    }

    conversationBuffer.append("</body></html>");

    emit send_message(email, "<ding>");
    QSound::play("./Resources/ding-dong.wav");

     ui->conversationTextBox->setHtml(conversationBuffer);

     for (int i = 0; i < 4; i++){

         int xa;
         int ya;

         xa = this->geometry().x() + qrand() % ((16 + 1) - - 16) + -  16;
         ya = this->geometry().y() + qrand() % ((16 + 1) - - 16) + -  16;

         this->setGeometry(xa,ya, this->geometry().width(), this->geometry().height());
         deelay();

     }
}


void IM_WindowObject::loadPreviousMessages()
{
    conversationBuffer = ui->conversationTextBox->toHtml();
    //ui->conversationTextBox->clear();

    int substract = 0;

    for (int i=0; i<conversationList.count(); i++){
        if (conversationList.at(i) == "<span style='color: rgb(204, 0, 0);'>BUZZ</span><br></br>" ){
            substract += 1;
        }
    }

    previousMsgIndex = conversationList.count();

    emit get_prev_messages(email, QString::number(previousMsgIndex - substract));

    //previousMsgIndex = previousMsgIndex + 10;
    //qInfo() << "index: " + QString::number(previousMsgIndex);
}

void IM_WindowObject::showSmileys()
{

    SmileysObject *sm = new SmileysObject();

    sm->setWindowFlags(Qt::Window | Qt::FramelessWindowHint| Qt::Popup);
    sm->setGeometry(this->geometry().x() + 10, this->geometry().y() + this->geometry().height() - 116 - 56, 132, 56);

    connect(sm, SIGNAL(smiley(QString)), SLOT(appendSmiley(QString)));

    sm->show();

}

void IM_WindowObject::appendSmiley(QString characters){

    //ui->sendMessageBox->append(characters);
    ui->sendMessageBox->insertPlainText(characters);
}

void IM_WindowObject::showHideNotice(bool value){
    if (value){
        ui->offlineIcon->hide();
        ui->noticeLabel->hide();
    } else {
        ui->offlineIcon->show();
        ui->noticeLabel->show();
    }
}

void IM_WindowObject::resizeEvent(QResizeEvent* event)
{
  // qInfo() << event->size();
   // Your code here.
}

void IM_WindowObject::playSmileys(){

   QString text = ui->conversationTextBox->toHtml();


   QScrollBar *scrollBar = ui->conversationTextBox->verticalScrollBar();

   int scrollValue = scrollBar->value();;

   int index;

   index = 0;


   while (text.indexOf("1.png", index) > -1){

        index = text.indexOf(QRegExp("[0-9]{1,1}.png"), index);
       if (index != -1){
           bool insert = true;
           for (int a=0; a< smileysList.count(); a++){
               if(smileysList.at(a)==index){
                   insert = false;
               }
           }
           if(insert){
               smileysList.append(index);
           }
           index += 1;}


   }

   //qInfo() << smileysList;

   for (int i=0; i<smileysList.count(); i++){
       //qInfo() << text.left(smileysList.at(i) + 5).right(5);

       if (text.left(smileysList.at(i) + 5).right(5) == "1.png"){
           text.replace(smileysList.at(i), 1, "2");
       }
       else if (text.left(smileysList.at(i) + 5).right(5) == "2.png"){
           text.replace(smileysList.at(i), 1, "3");
       }
       else if (text.left(smileysList.at(i) + 5).right(5) == "3.png"){
           text.replace(smileysList.at(i), 1, "4");
       }
       else if (text.left(smileysList.at(i) + 5).right(5) == "4.png"){
           text.replace(smileysList.at(i), 1, "5");
       }
       else if (text.left(smileysList.at(i) + 5).right(5) == "5.png"){
           text.replace(smileysList.at(i), 1, "6");
       }
       else if (text.left(smileysList.at(i) + 5).right(5) == "6.png"){
           text.replace(smileysList.at(i), 1, "7");
       }
       else if (text.left(smileysList.at(i) + 5).right(5) == "7.png"){
           text.replace(smileysList.at(i), 1, "8");
       }
       else if (text.left(smileysList.at(i) + 5).right(5) == "8.png"){
           text.replace(smileysList.at(i), 1, "9");
       }
       else if (text.left(smileysList.at(i) + 5).right(5) == "9.png"){
           text.replace(smileysList.at(i), 1, "1");
       }
   }





   ui->conversationTextBox->setHtml(text);

//   ui->conversationTextBox->moveCursor(QTextCursor::End);
//   QScrollBar *scrollBar = ui->conversationTextBox->verticalScrollBar();
//   scrollBar->setValue(scrollBar->maximum());
//   ui->conversationTextBox->ensureCursorVisible();

   scrollBar->setValue(scrollValue);
   QTimer::singleShot(200, this, SLOT(playSmileys()));

}


