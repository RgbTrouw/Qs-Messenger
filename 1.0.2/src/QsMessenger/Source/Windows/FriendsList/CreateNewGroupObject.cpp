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

#include "Headers/CreateNewGroupObject.h"
#include "ui_CreateNewGroupObject.h"

#include <QDesktopWidget>
#include <QTimer>

CreateNewGroupObject::CreateNewGroupObject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateNewGroupObject)
{
    ui->setupUi(this);

    QDesktopWidget dWidget;
    int screenWidth = dWidget.screen()->width();
    int screenHeight = dWidget.screen()->height();

    this->setGeometry((screenWidth/2)-(this->width()/2),(screenHeight/2)-(this->height()/2),this->width(),this->height());
    ui->addButton->setIcon(QIcon("./Resources/icons/addGroup.png"));
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addNewGroup()) );
}

CreateNewGroupObject::~CreateNewGroupObject()
{
    delete ui;
}

void CreateNewGroupObject::resetInput(){

    ui->groupNameText->setText("");
    ui->serverMessage->setText("  ...");
}

void CreateNewGroupObject::addNewGroup(){

    if(ui->groupNameText->text().indexOf(" ") == -1 && ui->groupNameText->text().size() > 2){
    emit addNewGroupSignal(ui->groupNameText->text());

    } else {
        ui->serverMessage->setText("  Group name is not validated...");
    }
}

void CreateNewGroupObject::feedback(QString message){

    ui->serverMessage->setText("  " + message);

    if (message == "New group created...") {
        QTimer::singleShot(3200, this, [=] () {

        ui->groupNameText->clear();
        ui->serverMessage->clear();
        this->close();

        });
    }

}
