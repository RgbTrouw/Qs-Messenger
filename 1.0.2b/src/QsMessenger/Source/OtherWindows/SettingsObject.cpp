/*   QsMessenger Client v 1.0.2b Rev 4 Instant Messaging Application
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

 
#include "Headers/SettingsObject.h"
#include "ui_SettingsObject.h"

SettingsObject::SettingsObject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsObject)
{
    ui->setupUi(this);
    connect(ui->updateButton, SIGNAL(clicked()), this, SLOT(updateHostAddressValue()));

    connect(ui->generalButton, SIGNAL(clicked()), this, SLOT(generalStack()));
    connect(ui->connectionButton, SIGNAL(clicked()), this, SLOT(connectionStack()));
    connect(ui->privacyButton, SIGNAL(clicked()), this, SLOT(privacyStack()));

    ui->updateButton->setIcon(QIcon("./Resources/icons/refresh.png"));
    ui->connectionButton->setIcon(QIcon("./Resources/icons/network.png"));
    ui->generalButton->setIcon(QIcon("./Resources/icons/2221968.png"));
    ui->privacyButton->setIcon(QIcon("./Resources/icons/registration.png"));
    ui->stackedWidget->setCurrentIndex(0);
}

SettingsObject::~SettingsObject()
{
    delete ui;
}

void SettingsObject::updateHostAddressValue(){

    if(ui->hostAddressLineEdit->text() != "" && ui->portSpinBox->value() != 0 ){
    emit updateHostAddress(ui->hostAddressLineEdit->text() + ":" + QString::number(ui->portSpinBox->value()));
    }
}

void SettingsObject::setSettings(QString host, QString port){

    ui->currentAddressLabel->setText(host);
    ui->currentPortLabel->setText(port);
}


void SettingsObject::generalStack(){

    ui->stackedWidget->setCurrentIndex(0);
}

void SettingsObject::connectionStack(){

    ui->stackedWidget->setCurrentIndex(1);
}


void SettingsObject::privacyStack(){

    ui->stackedWidget->setCurrentIndex(2);
}
