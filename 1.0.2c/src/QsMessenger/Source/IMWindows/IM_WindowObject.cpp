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

#include "Headers/IM_WindowObject.h"
#include "ui_IM_WindowObject.h"
 
#include <QRegularExpression>
#include <QRandomGenerator>
#include <QTextBrowser>
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QUuid>
#include <QCloseEvent>
#include <QSizePolicy>
#include <QScrollBar>
#include <QDateTime>
#include <QMenuBar>
#include <QTimer>
#include <QFile>
#include <QTime>

    //#include <QDebug>


IM_WindowObject::IM_WindowObject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IM_WindowObject)
{
    ui->setupUi(this);

    this->setFocusPolicy(Qt::ClickFocus);
    vLayout->setContentsMargins(0,0,0,0);
    vLayout->setSpacing(0);


    ui->webcamButton->setIcon(QIcon("./Resources/icons/webcam.png"));
    ui->offlineIcon->setPixmap(QPixmap("./Resources/icons/smiley_offline.png"));


    QMenuBar* menuBar = new QMenuBar();
    QMenu *fileMenu = new QMenu("Conversation");
    menuBar->addMenu(fileMenu);

    fileMenu->addAction(ui->actionLoadPrevious);
    fileMenu->addAction(ui->actionClearArchive);

    connect(ui->actionLoadPrevious, SIGNAL(triggered()), this, SLOT(loadPreviousMessages()));
    connect(ui->actionClearArchive, SIGNAL(triggered()), this, SLOT(clearArchive()));


    this->layout()->setMenuBar(menuBar);

    this->setWindowIcon(QIcon("./Resources/icons/AppIcon.png"));

    setMyAvatar();
    setPeerAvatar();

    ui->smileysButton->setIcon(QIcon("./Resources/icons/smiley.png"));
    ui->buzzButton->setIcon(QIcon("./Resources/icons/buzz.png"));
    ui->sendFileButton->setIcon(QIcon("./Resources/icons/paperclip.png"));
    ui->imagesButton->setIcon(QIcon("./Resources/icons/images.png"));

    ui->acceptButton->setIcon(QIcon("./Resources/icons/check.png"));
    ui->declineButton->setIcon(QIcon("./Resources/icons/decline.png"));

    ui->receiveFileWidget->setVisible(false);
    ui->acceptButton->setVisible(false);
    ui->declineButton->setVisible(false);
    ui->horizontalLayout_4->addItem(horizontalSpacerExpanding);


    connect(ui->buzzButton, SIGNAL(clicked()), this, SLOT(sendBuzz()));
    connect(ui->sendFileButton, SIGNAL(clicked()), this, SLOT(sendFile()));

    ui->myAvatar->setPixmap(QPixmap("./Resources/icons/avatarIcon.png"));
    //ui->myAvatar->hide();

    connect(ui->sendMsgButton, SIGNAL(clicked()), this, SLOT(sendMsg()));
    connect(ui->acceptButton, SIGNAL(clicked()), this, SLOT(acceptFile()));
    connect(ui->declineButton, SIGNAL(clicked()), this, SLOT(declineFile()));

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


       //QString conversationBuffer = ui->conversationTextBox->toHtml();

       QString conversationBuffer = "<html><body>";



       conversationBuffer.replace(QRegularExpression::wildcardToRegularExpression("<!DOCTYPE*</body></html>") ,"<html><body>");

       conversationBuffer.replace("\n", "");
       conversationBuffer.replace("<br>", "");
       conversationBuffer.replace("<br />", "");
       conversationBuffer.replace("<p>", "");
       conversationBuffer.replace("<p style", "<div style");
       conversationBuffer.replace("-qt-paragraph-type:empty; ", "");
       conversationBuffer.replace("</br>", "");
       conversationBuffer.replace("</p>", "");

       for (int i=0; i< conversationList.size(); i++){
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
    //QTimer::singleShot(2000, this, [=](){ emit have_read(email);});
//    haveRead = false;

    if (this->isActiveWindow()){
        //qInfo() << "has focus...";

        emit have_read(email);
       // haveRead == true;
    } else {
        //qInfo() << "doesn't have focus...";
        playAudio("./Resources/imNotification.wav");
    }

    if (message == "<ding>"){


//        this->setWindowState(Qt::WindowState::WindowActive);
//        this->show();
//        this->raise();
//        this->activateWindow();

        conversationBuffer = "<html><body>";

        conversationList.append("<span style='color: rgb(204, 0, 0);'>BUZZ</span><br></br>");

        for(int i=0; i<conversationList.size(); i++){
            conversationBuffer.append(conversationList.at(i));
        }

        conversationBuffer.append("</body></html>");

       // QSound::play("./Resources/ding-dong.wav");
        audioEffect->setSource(QUrl::fromLocalFile("./Resources/ding-dong.wav"));
        audioEffect->setLoopCount(1);
        audioEffect->setVolume(0.75f);
        audioEffect->play();

         ui->conversationTextBox->setHtml(conversationBuffer);

         for (int i = 0; i < 4; i++){

             int xa;
             int ya;

             xa = this->geometry().x() + QRandomGenerator::global()->bounded(-16,16);
             ya = this->geometry().y() + QRandomGenerator::global()->bounded(-16,16);

             this->setGeometry(xa,ya, this->geometry().width(), this->geometry().height());
             deelay();
        }
    } else {




    if (conversationList.size()>0){
        conversationList.last().append(peer_name + ": " + message +  "<br></br>");
    } else {
        conversationList.append(peer_name + ": "  + message + "<br></br>");
    }



    //QString conversationBuffer = ui->conversationTextBox->toHtml();

     QString conversationBuffer = "<html><body>";

    for (int i =0; i < conversationList.size(); i++){
        conversationBuffer.append(conversationList.at(i));
    }

    conversationBuffer.replace(QRegularExpression::wildcardToRegularExpression("<!DOCTYPE*</body></html>") ,"<html><body>");

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

     // Potential leak of memory pointed to by 'dt';

    }
}

void IM_WindowObject::prepend_message(QString msgFrom, QString msgTo, QString message,  QString time){

    Q_UNUSED(msgTo);
    Q_UNUSED(time);

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

    //QString conversationBuffer = ui->conversationTextBox->toHtml();

    QString conversationBuffer = "<html><body>";


    for (int i =0; i < conversationList.size(); i++){
        conversationBuffer.append(conversationList.at(i));
    }

    conversationBuffer.replace(QRegularExpression::wildcardToRegularExpression("<!DOCTYPE*</body></html>") ,"<html><body>");
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
    Q_UNUSED(event);
//        ui->conversationTextBox->setText("");
//        ui->sendMessageBox->setText("");
//        event->accept();
//        previousMsgIndex = 0;
//        ui->conversationTextBox->setText("");
//        conversationList.clear();
//        conversationBuffer.clear();

    this->hide();

}

//void IM_WindowObject::mousePressEvent(QMouseEvent *event){
//    Q_UNUSED(event)
//    qInfo() << 1;

//    //return IM_WindowObject::event(event);
//}

bool IM_WindowObject::event(QEvent *event){

    //qInfo() << event->type();

    if(event->type() == QEvent::WindowActivate){
        emit have_read(email);
    }
    return QWidget::event(event);
}

void IM_WindowObject::sendBuzz()
{
    //qInfo() << this->geometry();


    conversationBuffer = "<html><body>";

    conversationList.append("<span style='color: rgb(204, 0, 0);'>BUZZ</span><br></br>");

    for(int i=0; i<conversationList.size(); i++){
        conversationBuffer.append(conversationList.at(i));
    }

    conversationBuffer.append("</body></html>");

    emit send_message(email, "<ding>");
   // QSound::play("./Resources/ding-dong.wav");

    audioEffect->setSource(QUrl::fromLocalFile("./Resources/ding-dong.wav"));
    audioEffect->setLoopCount(1);
    audioEffect->setVolume(0.75f);
    audioEffect->play();

     ui->conversationTextBox->setHtml(conversationBuffer);

     for (int i = 0; i < 4; i++){

         int xa;
         int ya;

         xa = this->geometry().x() + QRandomGenerator::global()->bounded(-16,16);
         ya = this->geometry().y() + QRandomGenerator::global()->bounded(-16,16);

         this->setGeometry(xa,ya, this->geometry().width(), this->geometry().height());
         deelay();

     }
}


void IM_WindowObject::loadPreviousMessages()
{
    conversationBuffer = ui->conversationTextBox->toHtml();
    //ui->conversationTextBox->clear();

    int substract = 0;

    for (int i=0; i<conversationList.size(); i++){
        if (conversationList.at(i) == "<span style='color: rgb(204, 0, 0);'>BUZZ</span><br></br>" ){
            substract += 1;
        }
    }

    previousMsgIndex = conversationList.size();

    emit get_prev_messages(email, QString::number(previousMsgIndex - substract));

    //previousMsgIndex = previousMsgIndex + 10;
    //qInfo() << "index: " + QString::number(previousMsgIndex);
}

void IM_WindowObject::showSmileys()
{

//    SmileysObject *sm = new SmileysObject();

//    sm->setWindowFlags(Qt::Window | Qt::FramelessWindowHint| Qt::Popup);
//    sm->setGeometry(this->geometry().x() + 10, this->geometry().y() + this->geometry().height() - 116 - 56, 132, 56);

//    connect(sm, SIGNAL(smiley(QString)), SLOT(appendSmiley(QString)));

//    sm->show();

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
    Q_UNUSED(event);

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

        index = text.indexOf(QRegularExpression("[0-9]{1,1}.png"), index);
       if (index != -1){
           bool insert = true;
           for (int a=0; a< smileysList.size(); a++){
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

   for (int i=0; i<smileysList.size(); i++){
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

void IM_WindowObject::clearArchive(){

    QMessageBox msgBox;
    msgBox.setWindowTitle("Clear Archive");
    msgBox.setText("Are you sure you want to delete all archived messages?");
    //msgBox.setFont(textFont);
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    if(msgBox.exec() == QMessageBox::Yes){

      ui->sendMessageBox->clear();
      ui->conversationTextBox->clear();

      emit clearArchiveSignal(email);

    }else {
     // qInfo() << "no";
    }
}

void IM_WindowObject::sendFile(){

    QFileDialog dialog(nullptr,  "File (*.*)");

    dialog.setNameFilter("*.*");
    dialog.exec();

    QStringList path = dialog.selectedFiles();

    if (!path.isEmpty()){
        QFileInfo fileInfo(path.at(0));
        if (fileInfo.exists() && fileInfo.isFile()){
            FileTransferData fileTransferData;
            fileTransferData.transferId = QUuid::createUuid().toString(QUuid::WithoutBraces);
            fileTransferData.filePath = path.at(0);
            fileTransferData.fileName = fileInfo.fileName();
            fileTransferData.fileSize = QString::number(fileInfo.size());
            fileTransferData.savePath = "";
            fileTransferData.bytesReceived = 0;
            fileTransferData.writeInitialized = false;
            outgoingFileRequests.append(fileTransferData);

            emit send_file_request(email, fileTransferData.transferId, fileTransferData.fileName, fileTransferData.fileSize);
            ui->notification_label->setText(" File transfer request sent: \"" + fileTransferData.fileName + "\"");
        }
    }
}

void IM_WindowObject::receiveFileRequest(QString transferId, QString fileName, QString fileSize){

    bool validFileSize = false;
    qint64 expectedFileSize = fileSize.toLongLong(&validFileSize);
    if (!validFileSize || expectedFileSize < 0){
        ui->notification_label->setText(" Invalid file transfer request: \"" + fileName + "\"");
        return;
    }

    FileTransferData fileTransferData;
    fileTransferData.transferId = transferId;
    fileTransferData.filePath = "";
    fileTransferData.fileName = fileName;
    fileTransferData.fileSize = fileSize;
    fileTransferData.savePath = "";
    fileTransferData.bytesReceived = 0;
    fileTransferData.writeInitialized = false;

    if (pendingFileRequest.transferId.size() > 0){
        incomingFileRequests.append(fileTransferData);
        ui->notification_label->setText(" New file transfer request queued: \"" + fileName + "\"");
    } else {
        pendingFileRequest = fileTransferData;
    }

    updatePendingFileRequest();
}

void IM_WindowObject::receiveFileResponse(QString transferId, bool accepted){

    this->show();

    for (int i = 0; i < outgoingFileRequests.size(); i++){
        if (outgoingFileRequests.at(i).transferId == transferId){
            if (accepted){
                FileTransferData fileTransferData = outgoingFileRequests.takeAt(i);
                activeOutgoingFileRequests.append(fileTransferData);
                ui->notification_label->setText(" " + peer_name + " accepted file transfer: \"" + fileTransferData.fileName + "\"");
                emit send_file_payload(email, transferId, fileTransferData.filePath);
            } else {
                ui->notification_label->setText(" " + peer_name + " declined file transfer: \"" + outgoingFileRequests.at(i).fileName + "\"");
                outgoingFileRequests.removeAt(i);
            }
            break;
        }
    }
}

void IM_WindowObject::acceptFile(){
    if (pendingFileRequest.transferId.size() > 0){
        QString savePath = QFileDialog::getSaveFileName(this, "Save File", pendingFileRequest.fileName);
        if (savePath.isEmpty()){
            ui->notification_label->setText(" File transfer accept canceled: \"" + pendingFileRequest.fileName + "\"");
            return;
        }

        QFileInfo saveFileInfo(savePath);
        if (saveFileInfo.exists()){
            QMessageBox msgBox;
            msgBox.setWindowTitle("Overwrite File");
            msgBox.setText("File already exists. Overwrite \"" + saveFileInfo.fileName() + "\"?");
            msgBox.setStandardButtons(QMessageBox::Yes);
            msgBox.addButton(QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::No);

            if(msgBox.exec() != QMessageBox::Yes){
                ui->notification_label->setText(" File transfer accept canceled: \"" + pendingFileRequest.fileName + "\"");
                return;
            }
        }

        pendingFileRequest.savePath = savePath;
        pendingFileRequest.bytesReceived = 0;
        pendingFileRequest.writeInitialized = false;
        acceptedIncomingFileRequests.append(pendingFileRequest);
        emit respond_file_request(email, pendingFileRequest.transferId, true);
        ui->notification_label->setText(" Waiting for file: \"" + pendingFileRequest.fileName + "\"");
    }
    pendingFileRequest = FileTransferData();
    updatePendingFileRequest();
}

void IM_WindowObject::declineFile(){
    if (pendingFileRequest.transferId.size() > 0){
        emit respond_file_request(email, pendingFileRequest.transferId, false);
        ui->notification_label->setText(" You declined file transfer: \"" + pendingFileRequest.fileName + "\"");
    }
    pendingFileRequest = FileTransferData();
    updatePendingFileRequest();
}

void IM_WindowObject::updatePendingFileRequest(){

    if (pendingFileRequest.transferId.size() == 0 && incomingFileRequests.size() > 0){
        pendingFileRequest = incomingFileRequests.takeFirst();
    }

    if (pendingFileRequest.transferId.size() > 0){
        ui->receiveFileWidget->setVisible(true);
        ui->acceptButton->setVisible(true);
        ui->declineButton->setVisible(true);

        ui->sendFileLabel->setText(peer_name + " wants to send a file: ");
        ui->fileNameLabel->setText('"' + pendingFileRequest.fileName + '"' + " (" + pendingFileRequest.fileSize + " bytes)");
    } else {
        ui->receiveFileWidget->setVisible(false);
        ui->acceptButton->setVisible(false);
        ui->declineButton->setVisible(false);
    }
}

void IM_WindowObject::receiveFilePayload(QString transferId, QByteArray data, bool isLastFrame){

    this->show();

    for (int i = 0; i < acceptedIncomingFileRequests.size(); i++){
        if (acceptedIncomingFileRequests.at(i).transferId == transferId){
            FileTransferData &fileTransferData = acceptedIncomingFileRequests[i];
            QString progressText = " Receiving file: \"" + fileTransferData.fileName + "\"";
            if (fileTransferData.fileSize.size() > 0){
                progressText.append(" (" + QString::number(fileTransferData.bytesReceived) + "/" + fileTransferData.fileSize + " bytes)");
            }
            ui->notification_label->setText(progressText);

            QIODevice::OpenMode openMode = QIODevice::WriteOnly;
            if (fileTransferData.writeInitialized){
                openMode |= QIODevice::Append;
            } else {
                openMode |= QIODevice::Truncate;
            }

            QFile file(fileTransferData.savePath);
            if (file.open(openMode)){
                qint64 bytesWritten = file.write(data);
                file.close();

                if (bytesWritten != data.size()){
                    ui->notification_label->setText(" Failed to save file: \"" + fileTransferData.fileName + "\"");
                    QFile::remove(fileTransferData.savePath);
                    acceptedIncomingFileRequests.removeAt(i);
                } else {
                    fileTransferData.bytesReceived += bytesWritten;
                    fileTransferData.writeInitialized = true;

                    bool validFileSize = false;
                    qint64 expectedFileSize = fileTransferData.fileSize.toLongLong(&validFileSize);
                    QString currentProgress = " Receiving file: \"" + fileTransferData.fileName + "\"";
                    if (fileTransferData.fileSize.size() > 0){
                        currentProgress.append(" (" + QString::number(fileTransferData.bytesReceived) + "/" + fileTransferData.fileSize + " bytes)");
                    }
                    ui->notification_label->setText(currentProgress);

                    if (isLastFrame){
                        if (!validFileSize || expectedFileSize != fileTransferData.bytesReceived){
                            QFile::remove(fileTransferData.savePath);
                            ui->notification_label->setText(" Failed to save file: \"" + fileTransferData.fileName + "\"");
                        } else {
                            ui->notification_label->setText(" File saved: \"" + fileTransferData.fileName + "\"");
                        }
                        acceptedIncomingFileRequests.removeAt(i);
                    }
                }
            } else {
                ui->notification_label->setText(" Failed to save file: \"" + fileTransferData.fileName + "\"");
                acceptedIncomingFileRequests.removeAt(i);
            }
            break;
        }
    }
}

void IM_WindowObject::completeOutgoingFileTransfer(QString transferId, bool success, QString message){

    for (int i = 0; i < activeOutgoingFileRequests.size(); i++){
        if (activeOutgoingFileRequests.at(i).transferId == transferId){
            if (success){
                if (message.size() > 0){
                    ui->notification_label->setText(message);
                } else {
                    ui->notification_label->setText(" File sent: \"" + activeOutgoingFileRequests.at(i).fileName + "\"");
                }
                activeOutgoingFileRequests.removeAt(i);
            } else {
                ui->notification_label->setText(message);
                activeOutgoingFileRequests.removeAt(i);
            }
            break;
        }
    }
}
