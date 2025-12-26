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

#include "Headers/NotificationsWidget.h"
#include "ui_NotificationsWidget.h"

    // #include <QDebug>

NotificationsWidget::NotificationsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NotificationsWidget)
{

    ui->setupUi(this);


    this->setGeometry(this->geometry().x(), 800, 200,0);


}

NotificationsWidget::~NotificationsWidget()
{
    delete ui;
}

void NotificationsWidget::newNotification(QString availability, QString username){

    noticesList.prepend(new NoticeLabelObject());

    connect(noticesList.last(), SIGNAL(createNotice()), this, SLOT(createNotice()));
    connect(noticesList.last(), SIGNAL(closeNotice()), this, SLOT(closeNotice()));

    if (availability == "0"){
        noticesList.first()->setLabel(username + " went offline...");
        noticesList.first()->setIcon(0);
    }
    else if (availability == "1") {
        noticesList.first()->setLabel(username + " went online...");
        noticesList.first()->setIcon(1);
    }



    for(int i =0; i< noticesList.count(); i++){
        ui->verticalLayout->removeItem(ui->verticalLayout->takeAt(i));
    }

    ui->verticalLayout->removeItem(verticalSpacer);

    for(int i =0; i< noticesList.count(); i++){
        ui->verticalLayout->addWidget(noticesList.at(i));
    }

    ui->verticalLayout->addItem(verticalSpacer);


}



void NotificationsWidget::createNotice(){

    this->setGeometry(this->geometry().x(), (this->geometry().y() - 20), 200, (this->geometry().height() + 20));

}

void NotificationsWidget::closeNotice(){

    this->setGeometry(this->geometry().x(), (this->geometry().y() + 20), 200, (this->geometry().height() - 20));

    if (noticesList.count() == 0) {this->close();}

}
