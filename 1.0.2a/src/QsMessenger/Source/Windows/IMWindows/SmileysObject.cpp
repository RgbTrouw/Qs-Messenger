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

#include "Headers/SmileysObject.h"
#include "ui_SmileysObject.h"


SmileysObject::SmileysObject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SmileysObject)
{
    ui->setupUi(this);
}

SmileysObject::~SmileysObject()
{
    delete ui;
}

void SmileysObject::on_pushButton_clicked()
{
    emit smiley(":)");
}

void SmileysObject::on_pushButton_5_clicked()
{
    emit smiley(":))");
}

void SmileysObject::on_pushButton_3_clicked()
{
    emit smiley(":shy:");
}

void SmileysObject::on_pushButton_6_clicked()
{
    emit smiley(":X");
}

void SmileysObject::on_pushButton_10_clicked()
{
    emit smiley(":|");
}

void SmileysObject::on_pushButton_4_clicked()
{
    emit smiley(":D");
}

void SmileysObject::on_pushButton_2_clicked()
{
    emit smiley(":D");
}

void SmileysObject::on_pushButton_8_clicked()
{
    emit smiley("X|");
}

void SmileysObject::on_pushButton_9_clicked()
{
    emit smiley(":((");
}

void SmileysObject::on_pushButton_7_clicked()
{
    emit smiley(":O");
}
