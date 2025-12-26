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

#include "Headers/NoticeLabelObject.h"
#include "ui_NoticeLabelObject.h"
#include "../../../MainWindow.h"

#include <QTimer>

NoticeLabelObject::NoticeLabelObject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NoticeLabelObject)
{
    ui->setupUi(this);

    emit createNotice();

    QTimer::singleShot(3000, this, [=](){

     emit closeNotice();
     this->close();

    });

}

NoticeLabelObject::~NoticeLabelObject()
{
    delete ui;
}


void NoticeLabelObject::setLabel(QString label){

    ui->label->setText(label);

}

void NoticeLabelObject::setIcon(int value){

    if(value == 0){
        ui->img->setPixmap(QPixmap("./Resources/icons/smiley_offline.png"));
    } else {
        ui->img->setPixmap(QPixmap("./Resources/icons/smiley.png"));

    }

}
