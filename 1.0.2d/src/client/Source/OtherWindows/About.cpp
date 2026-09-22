/*   Qs-Messenger Client v 1.0.2d Instant Messaging Application
     Copyright (C) 2026  Radu G. Balaban G.
*/

#include "Headers/About.h"
#include "ui_About.h"
#include <QGuiApplication>
#include <QScreen>

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
