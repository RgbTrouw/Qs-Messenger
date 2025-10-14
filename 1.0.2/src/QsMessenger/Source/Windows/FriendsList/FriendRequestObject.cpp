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

#include "Headers/FriendRequestObject.h"
#include "ui_FriendRequestObject.h"

#include <QRegularExpression>
#include <QDesktopWidget>


FriendRequestObject::FriendRequestObject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendRequestObject)
{
    ui->setupUi(this);
    ui->addButton->setIcon(QIcon("./Resources/icons/addUser.png"));

    //ui->serverMessageLabel->hide();

    QDesktopWidget dWidget;
    int screenWidth = dWidget.screen()->width();
    int screenHeight = dWidget.screen()->height();

    this->setGeometry((screenWidth/2)-(this->width()/2),(screenHeight/2)-(this->height()/2),this->width(),this->height());

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(add()));
}

FriendRequestObject::~FriendRequestObject()
{
    delete ui;
}

void FriendRequestObject::add()
{
    QString sp = "*@*.*";
    //match.setPatternSyntax(QRegExp::Wildcard);

    QString w =  QRegularExpression::wildcardToRegularExpression("*@*.*");
    QRegularExpression re(w);
    QRegularExpressionMatch match = re.match(ui->lineEdit->text());
    bool hasMatch = match.hasMatch();

    if (hasMatch){

    email = ui->lineEdit->text();

    ui->serverMessageLabel->setText("  Processing...");
    emit addNewUser();

    } else {
        ui->serverMessageLabel->setText("  Email is not validated...");
    }
    //st->singleShot(1000, this, SLOT(close_window()));
}

void FriendRequestObject::feedback(QString message){


    //this->setGeometry(this->geometry().x(),this->geometry().y(), this->geometry().width(), this->geometry().height() + 20);
    ui->serverMessageLabel->show();
    this->activateWindow();

    ui->serverMessageLabel->setText(message);
    if(ui->serverMessageLabel->text() == "  Friendship request has been sent..."){
        st->singleShot(3200, this, SLOT(close_window()));
    }
}

void FriendRequestObject::close_window(){

    if (ui->serverMessageLabel->text() == "  Friendship request has been sent..."){

        ui->lineEdit->setText("");
        ui->serverMessageLabel->setText("");
        this->close();
    } else {st->singleShot(3200, this, SLOT(close_window()));}

}

void FriendRequestObject::closeEvent (QCloseEvent *event)
{
    ui->lineEdit->setText("");
    ui->serverMessageLabel->setText("...");
}
