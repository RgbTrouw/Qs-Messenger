/*   QsMessenger Client v 1.0.2 Instant Messaging Application
     Copyright (C) 2025  Radu G. Balaban G.

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

#include "Headers/FriendsListWidget.h"
#include "ui_FriendsListWidget.h"

#include <QSpacerItem>

    // #include <QDebug>


FriendsListWidget::FriendsListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendsListWidget)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setAttribute(Qt::WA_Hover, true);
    ui->scrollArea->setWidget(scrollAreaContent);
    vLayout->setContentsMargins(0,0,0,0);
    vLayout->setSpacing(0);


}

FriendsListWidget::~FriendsListWidget()
{
    this->disconnect();
    delete ui;
}


void FriendsListWidget::set_data(QString plain_data){

    for (int i = 0; i< groups.count(); i++){ui->verticalLayout->removeWidget(groups.at(i));

    }
    groups.clear();

    data = plain_data;
    QStringList plain_groups = data.split("|");

    plain_groups.removeFirst();
    nr_of_groups = plain_groups.count();

    QStringList buffer;

    for (int i=0; i < nr_of_groups; i++){

        buffer.append(plain_groups.at(i).split("/").at(0));
    }

    for (int i=0; i < nr_of_groups; i++){

        GroupWidget *buffer_group = new GroupWidget();
        buffer_group->set_group_name(buffer.at(i));
        groups.append(buffer_group);

        vLayout->addWidget(groups.last());


        }


    vLayout->addItem(verticalSpacer);

    for (int i=0; i < groups.count(); i++){
        groups.at(i)->set_plain_data(plain_groups.at(i));

        //qInfo() << "Group " + groups.at(i)->get_group_name() + " - Group Data: " + groups.at(i)->plain_group_data;
    }



}


void FriendsListWidget::clearWidget(){

    for (int i=0; i<groups.count(); i++){

        ui->verticalLayout->removeWidget(groups.at(i));

    }
    groups.clear();

}

void FriendsListWidget::removeGroup(QString groupName){

    for(int i=0; i<groups.count(); i++){
    if(groups.at(i)->group_name == groupName){
        vLayout->removeWidget(groups.at(i));

        delete groups.at(i);
        groups.removeAt(i);

    }
    }
}

void FriendsListWidget::addNewGroup(QString groupName){
    //qInfo() << vLayout->count();

  //  qInfo() << "add new group...";

    vLayout->removeItem(verticalSpacer);
    groups.append(new GroupWidget());
    groups.last()->set_group_name(groupName);
    groups.last()->set_plain_data(groupName + "|");
    vLayout->addWidget(groups.last());
    groups.last()->setVisible(true);
    vLayout->addItem(verticalSpacer);

}
