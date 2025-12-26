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


#include "Headers/FriendRequestObject.h"
#include "Headers/GroupWidget.h"
#include "Headers/PeerWidget.h"
#include "ui_GroupWidget.h"

    //#include <QDebug>

GroupWidget::GroupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupWidget)
{
    ui->setupUi(this);
    ui->verticalLayout->setSpacing(0);
    ui->verticalLayout->setMargin(0);

    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setAttribute(Qt::WA_Hover, true);

    connect(groupHeader, SIGNAL(changePeersDisplay(QString)), this, SLOT(changePeersDisplay(QString)));
    connect(groupHeader->addNewUserAction, SIGNAL(triggered()), this, SLOT(addNewUser()));
    connect(groupHeader->addNewGroupAction, SIGNAL(triggered()), this, SLOT(addNewGroup()));
    connect(groupHeader->removeGroupAction, SIGNAL(triggered()), this, SLOT(removeGroup()));

}

GroupWidget::~GroupWidget()
{
    this->disconnect();
    delete ui;
}

void GroupWidget::set_group_name(QString name){
    group_name = name;
    groupHeader->setName(name);

    //ui->expandIcon->setPixmap(QPixmap("./Resources/icons/triangle_down.png"));

}

QString GroupWidget::get_group_name(){

    return group_name;
}



void GroupWidget::set_plain_data(QString plain_data){

    //qInfo() << "Group: " + group_name;

    peers.clear();

    if (plain_data.right(1) == ":"){
        plain_data = plain_data.left(plain_data.size() - 1);
    }

    QStringList buffer = plain_data.split(":");
    buffer.removeFirst();
    QString buffer_data;

    for (int i = 0; i < buffer.size(); i++){

        buffer_data.append(buffer.at(i));
            if (i != buffer.size() -1){
                buffer_data.append(":");
            }
    }

   plain_data = buffer_data;
   plain_group_data = plain_data;

   QStringList plain_group_data_sl;
   plain_group_data_sl = plain_group_data.split(":");


   ui->verticalLayout->addWidget(groupHeader);

   //qInfo() << plain_group_data_sl.count();
   if ( plain_group_data_sl.at(0) != "" ){
   for (int i = 0; i < plain_group_data_sl.count(); i++){
       PeerWidget *peer_obj = new PeerWidget();
       peer_obj->set_plain_data(plain_group_data_sl.at(i));
       peers.append(peer_obj);
       //peers.last()->peer_list_position_index = group_list_position_index + i;
       //qInfo() << group_list_position_index;
       //qInfo() << peers.last()->peer_list_position_index;
        ui->verticalLayout->addWidget(peers.last());


   }

   }

   groupHeader->setCounterLabel("(" + QString::number(usersOnlineCount()) + "/" + QString::number(peers.count()) + ")");

    //qInfo() << groupHeader->GroupName; // ?

   if (groupHeader->GroupName == "Friends"){
       groupHeader->contextMenu->removeAction(groupHeader->removeGroupAction);
   } else {groupHeader->contextMenu->addAction(groupHeader->removeGroupAction);}


}

void GroupWidget::appendLastPeer(){

    ui->verticalLayout->addWidget(peers.last());

}
int GroupWidget::usersOnlineCount(){

    int usersOnline = 0;

    for (int i=0; i<peers.count(); i++){
        if(peers.at(i)->availability_int == 0 || peers.at(i)->availability_int == 1 )
        usersOnline +=1;
    }

    return usersOnline;
}


void GroupWidget::hover(bool value){

    if(value){
        this->setStyleSheet("background-color:rgb(115, 210, 22);");
    } else {
         this->setStyleSheet("background-color:rgb(255, 255, 255);");
    }

}


bool GroupWidget::eventFilter(QObject *object, QEvent *event)
{
    bool returnValue;

    //qInfo() << object;
    if (event->type() == QEvent::HoverEnter)
    {

        returnValue = true;
        //qInfo() << "hover in..";

        hover(true);

    }

    if (event->type() == QEvent::HoverLeave)
    {
        returnValue = false;

       // qInfo() << "hover out..";
        hover(false);

    }
    return returnValue;
}

void GroupWidget::clearPeersDisplay(){

    for (int i = 0; i < peers.count(); i++){
        peers.at(i)->hide();
    }

//    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), 24);
 //   ui->verticalLayout->addWidget(groupHeader);
}

void GroupWidget::changePeersDisplay(QString currentType) {

    //qInfo() << currentType + " " + virtualDirection;


    if (currentType == "all" ){

        virtualDirection = "up";
    groupHeader->currentType = "online";


        for (int i = 0; i < peers.count(); i++){
           if(peers.at(i)->availability_int == 0 || peers.at(i)->availability_int == 1){
            peers.at(i)->show();
           } else {peers.at(i)->hide();}
        }

        groupHeader->setIconMode("middle");

    } else if (currentType == "online" ){

        if (virtualDirection == "up"){

        groupHeader->currentType = "none";

            for (int i =0; i<peers.count(); i ++){
                peers.at(i)->hide();
            }

        groupHeader->setIconMode("up");


        } else {

        groupHeader->currentType = "all";

            for(int i = 0; i < peers.count(); i++){
                peers.at(i)->show();
            }

        groupHeader->setIconMode("down");

        }

        //if (virtualDirection == "up"){virtualDirection = "down";} else {virtualDirection = "up";}

    }

    else if (currentType == "none" ){

        virtualDirection = "down";

        groupHeader->currentType = "online";
        clearPeersDisplay();


        for (int i = 0; i < peers.count(); i++){
           if(peers.at(i)->availability_int == 0 || peers.at(i)->availability_int == 1){
            peers.at(i)->show();
           } else {peers.at(i)->hide();}
        }

           groupHeader->setIconMode("middle");
    }

    //qInfo() << currentType + " " + virtualDirection;

}

void GroupWidget::updateUsersOnline(){

    groupHeader->setCounterLabel("(" + QString::number(usersOnlineCount()) + "/" + QString::number(peers.count()) + ")");
    if (groupHeader->currentType == "online"){
        for (int i = 0; i < peers.count(); i++){
           if(peers.at(i)->availability_int == 0 || peers.at(i)->availability_int == 1){
            peers.at(i)->show();
           } else {peers.at(i)->hide();}
        }
    }

}

void GroupWidget::addNewUser(){

    emit addToGroupSignal(this->group_name);

}

void GroupWidget::addNewGroup(){

    emit addNewGroupSignal();

}

void GroupWidget::removeGroup(){

    emit removeGroupSignal(this->group_name);
}


