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

#include "Headers/RecoverPasswordObject.h"
#include "ui_RecoverPasswordObject.h"

#include <QCryptographicHash>
#include <QRegularExpression>
#include <QDesktopWidget>


    //#include <QDebug>

RecoverPasswordObject::RecoverPasswordObject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecoverPasswordObject)
{
    ui->setupUi(this);

   this->setWindowIcon(QIcon("./Resources/icons/registration.png"));

    ui->stackedWidget->setCurrentIndex(0);
    ui->feedbackLabel->setText("...");

    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), 198);
    this->setMinimumHeight(84);
    this->setMaximumHeight(84);

    QDesktopWidget dWidget;
    int screenWidth = dWidget.screen()->width();
    int screenHeight = dWidget.screen()->height();

    this->setGeometry((screenWidth/2)-(this->width()/2),(screenHeight/2)-(this->height()/2),this->width(),this->height());

    this->setWindowTitle("New Password");


    ui->pageButton->setIcon(QIcon("./Resources/icons/triangle_right.png"));
    ui->pageButton2->setIcon(QIcon("./Resources/icons/triangle_left.png"));



    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendResetCode()));
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetPassword()));
    connect(ui->pageButton, SIGNAL(clicked()), this, SLOT(nextPage()));
    connect(ui->pageButton2, SIGNAL(clicked()), this, SLOT(previousPage()));

     ui->sendButton->setIcon(QIcon("./Resources/icons/sendEmail.png"));
     ui->resetButton->setIcon(QIcon("./Resources/icons/2221968.png"));

}

RecoverPasswordObject::~RecoverPasswordObject()
{
    delete ui;

}

void RecoverPasswordObject::nextPage(){

    ui->stackedWidget->setCurrentIndex(1);

    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), 198);
    this->setMinimumHeight(170);
    this->setMaximumHeight(170);

    this->setWindowTitle("Reset Password");

    ui->emailPrompt->clear();
    ui->securityCodePrompt->clear();
    ui->passwordConfirmPrompt->clear();
    ui->passwordPrompt->clear();
    ui->feedbackLabel->clear();
    ui->feedbackLabel->setText("...");

}

void RecoverPasswordObject::previousPage(){

    ui->stackedWidget->setCurrentIndex(0);

    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), 198);
    this->setMinimumHeight(84);
    this->setMaximumHeight(84);

    this->setWindowTitle("New Password");

    ui->emailPrompt->clear();
    ui->securityCodePrompt->clear();
    ui->passwordConfirmPrompt->clear();
    ui->passwordPrompt->clear();
    ui->feedbackLabel->clear();
    ui->feedbackLabel->setText("...");

}

void RecoverPasswordObject::sendResetCode()
{
    QString sp = "*@*.*";
    //match.setPatternSyntax(QRegExp::Wildcard);

    QString w =  QRegularExpression::wildcardToRegularExpression("*@*.*");
    QRegularExpression re(w);
    QRegularExpressionMatch match = re.match(ui->emailPrompt->text());
    bool hasMatch = match.hasMatch();

    if (hasMatch){

        ui->feedbackLabel->setText("Processing...");

        QString request = "recoverPassword:";
        emit server_request(request + ui->emailPrompt->text());

    } else {
        ui->feedbackLabel->setText("Email format not validated...");
        ui->feedbackLabel->setStyleSheet("color: rgb(60, 150, 0);"); // green: rgb(60, 150, 0); red: rgb(224, 27, 36); yellow: rgb(246, 211, 45); blue: rgb(28, 113, 216);
    }

}

void RecoverPasswordObject::resetPassword(){

    ui->feedbackLabel->clear();
    QString scode = ui->securityCodePrompt->text();
    QString password = ui->passwordPrompt->text();

    QByteArray hash = password.toUtf8();
    password = QCryptographicHash::hash(hash, QCryptographicHash::Sha256).toHex();

    if (scode.size() == 20){

    if (ui->passwordPrompt->text() == ui->passwordConfirmPrompt->text()){
        if(ui->passwordPrompt->text().size() > 7){


            QString request="resetPassword:";
            request.append(scode);
            request.append(":");
            request.append(password);

            ui->feedbackLabel->setText("Processing...");

            emit server_request(request);



        } else {ui->feedbackLabel->setText("Password must be at least 8 characters long...");}
        } else {ui->feedbackLabel->setText("Passwords don't match..."); }

     } else {ui->feedbackLabel->setText("Security code is not validated...");}

}

void RecoverPasswordObject::server_feedback(QString message){

    ui->feedbackLabel->setText(message);

    if(message == "Reset code sent..."){
       nextPage();
       ui->feedbackLabel->setText("Please check your email for the security code...");
    }

    if(message == "Password changed..."){
        ui->securityCodePrompt->clear();
        ui->passwordPrompt->clear();
        ui->passwordConfirmPrompt->clear();
    }
}

void RecoverPasswordObject::closeEvent (QCloseEvent *event)
{
    ui->emailPrompt->clear();
    ui->securityCodePrompt->clear();
    ui->passwordConfirmPrompt->clear();
    ui->passwordPrompt->clear();
    ui->feedbackLabel->clear();
}
