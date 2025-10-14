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

#include "Headers/FriendshipResponseObject.h"
#include "ui_FriendshipResponseObject.h"

#include <QTimer>

FriendshipResponseObject::FriendshipResponseObject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendshipResponseObject)
{
    ui->setupUi(this);
    ui->pushButton->setIcon(QIcon("./Resources/icons/addUser.png"));

}

FriendshipResponseObject::~FriendshipResponseObject()
{
    delete ui;
}

void FriendshipResponseObject::on_pushButton_clicked()
{

    QString rsp = "yes";

    ui->label->setText("  Friendship accepted...");

    st->singleShot(2000, this, SLOT(feedback()));

    emit respond_fr( ui->emailLabel->text(), rsp );
}

void FriendshipResponseObject::on_pushButton_2_clicked()
{
    QString rsp = "no";

    st->singleShot(2000, this, SLOT(feedback()));

    ui->label->setText("  Friendship declined...");
    emit respond_fr(ui->emailLabel->text(), rsp);
}

void FriendshipResponseObject::from(QString email){

    ui->emailLabel->setText(email);
}

void FriendshipResponseObject::feedback(){

    ui->emailLabel->setText("");
    ui->label->setText("");
    this->close();
}

void FriendshipResponseObject::closeEvent (QCloseEvent *event)
{

}
