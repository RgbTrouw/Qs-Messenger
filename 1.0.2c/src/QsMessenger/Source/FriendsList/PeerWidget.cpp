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

#include "Headers/PeerWidget.h"
#include "ui_PeerWidget.h"

#include <QMouseEvent>
#include <QEvent>
#include <QTimer>
 
    // #include <QDebug>

PeerWidget::PeerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PeerWidget)
{
    this->installEventFilter(this);
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setAttribute(Qt::WA_Hover, true);


    ui->setupUi(this);

    ui->Icon->setPixmap(QPixmap("./Resources/icons/smiley.png"));
    ui->Icon->setAttribute(Qt::WA_StyledBackground, true);
    ui->Icon->setAttribute(Qt::WA_Hover, true);

    this->setMouseTracking(true);
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    moveToGroupUpAction->setText("Move Up");
    moveToGroupDownAction->setText("Move Down");
    removeUserAction->setText("Remove User");

    contextMenuFont.setPointSize(10);
    contextMenu->setFont(contextMenuFont);

    moveToGroupUpAction->setFont(contextMenuFont);
    moveToGroupDownAction->setFont(contextMenuFont);
    removeUserAction->setFont(contextMenuFont);


    moveToGroupUpAction->setIcon(QIcon("./Resources/icons/moveUp.png"));
    moveToGroupDownAction->setIcon(QIcon("./Resources/icons/moveDown.png"));
    removeUserAction->setIcon(QIcon("./Resources/icons/trashBin.png"));

    contextMenu->addAction(moveToGroupUpAction);
    contextMenu->addAction(moveToGroupDownAction);
    contextMenu->addAction(removeUserAction);


    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customContextMenu(QPoint)));
    connect(removeUserAction, SIGNAL(triggered()), this, SLOT(removeUser()));
    connect(moveToGroupDownAction, SIGNAL(triggered()), this, SLOT(moveToGroupDown()));
    connect(moveToGroupUpAction, SIGNAL(triggered()), this, SLOT(moveToGroupUp()));


}

PeerWidget::~PeerWidget()
{
    this->disconnect();
    delete ui;
}

void PeerWidget::set_plain_data(QString plain_peer_data){

    //    qInfo() << plain_peer_data;

    plain_data = plain_peer_data;

    peer_data = plain_data.split("/");
    //qInfo() << peer_data.size();

    name = peer_data.at(0);
    availability = peer_data.at(1);
    availability_int = peer_data.at(1).toInt();
    QByteArray byteArray = QByteArray::fromHex(peer_data.at(2).toUtf8());
    status_message = byteArray.data();

    email = peer_data.at(4);

    if (availability == "0"){
        availability = "available";
        ui->Icon->setPixmap(QPixmap("./Resources/icons/smiley.png"));
        if (status_message.size() > 0){
            ui->statusLabel->setText("- " + status_message);
        }
    } else if (availability == "1"){
        availability = "busy";
        ui->Icon->setPixmap(QPixmap("./Resources/icons/smiley_busy.png"));
        if (status_message.size() > 0){
            ui->statusLabel->setText("- " + status_message);
        }
    } else if (availability == "3"){
        availability = "offline";
        ui->Icon->setPixmap(QPixmap("./Resources/icons/smiley_offline.png"));
        ui->statusLabel->setText("");
    }


    ui->label->setText(name);

    //qInfo() << imWidget;


    this->setToolTip(email);

    imWidget->peer_name = name;
    imWidget->setWindowTitle(name);
    imWidget->email = email;


}

void PeerWidget::hover(bool value){


    if(value){
        this->setStyleSheet("background-color:rgb(243, 243, 243);");
    } else {
         this->setStyleSheet("background-color:rgb(255, 255, 255);");
    }

}


bool PeerWidget::eventFilter(QObject *object, QEvent *event)
{
    Q_UNUSED(object);

    bool returnValue;

    //qInfo() << event;

    if (event->type() == QEvent::HoverEnter)
    {

        returnValue = true;
        hover(true);

    }

    if (event->type() == QEvent::HoverLeave)
    {
        returnValue = false;

        hover(false);

    }

    if(event->type() == QEvent::MouseButtonDblClick){

        emit refreshPeerAvatar(email);

       // qInfo() << imWidget;

        imWidget->setWindowTitle(name);
        imWidget->email = email;
        imWidget->peer_name = name;

        //qInfo() << imWidget;
        imWidget->show();
        imWidget->setPeerAvatar();
        QTimer::singleShot(600, this, [=](){imWidget->setPeerAvatar();});
        imWidget->setMyAvatar();
        returnValue = true;
    }
    return returnValue;
}

void PeerWidget::customContextMenu(QPoint positionPoint){

//    qInfo() << positionPoint;

//    hover(false);
    QTimer::singleShot(1000, this , [=](){hover(false);});

    contextMenu->show();
    contextMenu->move(this->mapToGlobal(positionPoint).x(), this->mapToGlobal(positionPoint).y());

}

void PeerWidget::removeUser(){

    emit removeUserSignal(email);

}

void PeerWidget::moveToGroupDown(){

    emit moveToGroupDownSignal(this->email);

}


void PeerWidget::moveToGroupUp(){

    emit moveToGroupUpSignal(this->email);

}

