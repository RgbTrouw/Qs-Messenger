/*   Qs-Messenger Client v 1.0.2d Instant Messaging Application
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

#include "Headers/About.h"
#include <QGuiApplication>
#include <QScreen>
#include "ui_About.h"
 
About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    auto const rec =  QGuiApplication::primaryScreen()->geometry();
    auto const sHeight = rec.height();
    auto const sWidth = rec.width();
    this->setGeometry(sWidth / 2 - this->geometry().width() / 2, sHeight / 2 - this->geometry().height() * 2, this->geometry().width(), this->geometry().height());
    this->raise();
}
About::~About()
{ delete ui;}
