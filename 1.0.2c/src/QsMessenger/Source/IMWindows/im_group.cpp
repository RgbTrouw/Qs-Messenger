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


#include "im_group.h"
#include "ui_im_group.h"

IM_Group::IM_Group(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IM_Group)
{
    ui->setupUi(this);
    ui->avatar->setPixmap(QPixmap("./Resources/icons/groupAvatar.png"));

    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
}

IM_Group::~IM_Group()
{
    delete ui;
}

void IM_Group::sendMessage(){

    if(ui->message->toPlainText().size() > 4){
    emit sendGroupMessageSignal(ui->message->toPlainText(), groupName);
    ui->message->clear();
    groupName = "";
    this->close();
    }

}
