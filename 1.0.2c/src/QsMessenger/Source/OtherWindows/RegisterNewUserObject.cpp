/*   QsMessenger Client v 1.0.2c Instant Messaging Application
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
 
#include "Headers/RegisterNewUserObject.h"
#include "ui_RegisterNewUserObject.h"

#include <QCryptographicHash>
//#include <QDesktopWidget>
#include <QTimer>

    //#include <QDebug>

RegisterNewUserObject::RegisterNewUserObject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterNewUserObject)
{
    ui->setupUi(this);
    ui->countriesBox->addItems(countries);
    ui->countriesBox->setCurrentIndex(0);
    ui->full_name_Prompt->setFocus();
    this->setWindowIcon(QIcon("./Resources/icons/2221968.png"));
    this->setWindowTitle("Registration");

    // QDesktopWidget dWidget;
    // int screenWidth = dWidget.screen()->width();
    // int screenHeight = dWidget.screen()->height();

    // this->setGeometry((screenWidth/2)-(this->width()/2),(screenHeight/2)-(this->height()/2),this->width(),this->height());

    //// ... //////

    ui->stackedWidget->setCurrentIndex(0);

    ui->pageButton->setIcon(QIcon("./Resources/icons/triangle_right.png"));
    ui->pageButton2->setIcon(QIcon("./Resources/icons/triangle_left.png"));

    ui->resendEmailButton->setEnabled(false);

    connect(ui->pageButton, SIGNAL(clicked()), this, SLOT(nextPage()));
    connect(ui->pageButton2, SIGNAL(clicked()), this, SLOT(previousPage()));

    connect(ui->activateButton, SIGNAL(clicked()), this, SLOT(activateNewAccount()));
    connect(ui->resendEmailButton, SIGNAL(clicked()), this, SLOT(resendActivationCode()));


    ui->registration_Button->setIcon(QIcon("./Resources/icons/registration.png"));
    ui->resendEmailButton->setIcon(QIcon("./Resources/icons/sendEmail.png"));
    ui->activateButton->setIcon(QIcon("./Resources/icons/2221968.png"));

    //ui->date_of_birthPrompt->setInputMask("00/00/0000");
}

RegisterNewUserObject::~RegisterNewUserObject()
{

    delete ui;
}

void RegisterNewUserObject::nextPage(){
    ui->stackedWidget->setCurrentIndex(1);
    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), 142);
    this->setMinimumHeight(124);
    this->setMaximumHeight(124);

    this->setWindowTitle("Activation");

    ui->activation_code_Prompt->clear();

    ui->message_Label->setText("...");
    ui->message_Label_2->setText("...");

}

void RegisterNewUserObject::previousPage(){
    ui->stackedWidget->setCurrentIndex(0);
    this->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), 503);
    this->setMinimumHeight(503);
    this->setMaximumHeight(503);

    this->setWindowTitle("Registration");

    ui->full_name_Prompt->clear();
    ui->nick_Prompt->clear();
    ui->countriesBox->setCurrentIndex(0);
    ui->agreement_checkBox->setChecked(false);
    ui->date_of_birthPrompt->clear();
    ui->email_Prompt->clear();
    ui->female_radioButton->setChecked(false);
    ui->password_2_Prompt->clear();
    ui->password_Prompt->clear();

    ui->resendEmailButton->setEnabled(false);

    ui->message_Label->setText("...");
    ui->message_Label_2->setText("...");

}


void RegisterNewUserObject::on_registration_Button_clicked()
{
    validate_input();

}



void RegisterNewUserObject::validate_input(){

    ui->message_Label->setText("");

    bool valid = false;

    full_name = ui->full_name_Prompt->text();
    nickname = ui->nick_Prompt->text();

    bool male = ui->male_radioButton->isChecked();
    bool female = ui->female_radioButton->isChecked();

    date_of_birth = ui->date_of_birthPrompt->text();

    email = ui->email_Prompt->text();

    password = ui->password_Prompt->text();
    password2 = ui->password_2_Prompt->text();

    agreement = ui->agreement_checkBox->isChecked();

    //////////////////////////////////////////////////////////////////


    QRegularExpression re("[A-Z]{1,1}[a-z]{1,16}( van){0,1}( of){0,1}( de la){0,1}( [A-Z]{1,1}[a-z]{1,16}){1,4}");
    QRegularExpressionMatch match = re.match(full_name);
    bool hasMatch = match.hasMatch();



    ////////////////////////////////////////////////////////////////////////

    if ( hasMatch  && full_name.length() < 40 && full_name.length() > 5) {

     QString sp = "[a-zA-Z0-9]{1,1}[a-zA-Z0-9]{0,5}[a-zA-Z0-9_]{1,1}[a-zA-Z0-9]{0,5}[a-zA-Z0-9]{1,5}";

     QRegularExpression re("[a-zA-Z0-9]{1,1}[a-zA-Z0-9]{0,5}[a-zA-Z0-9_]{1,1}[a-zA-Z0-9]{0,5}[a-zA-Z0-9]{1,5}");
     QRegularExpressionMatch match = re.match(nickname);
     bool hasMatch = match.hasMatch();

     if (hasMatch ) { //qInfo() << "nickname is valid";


     if (ui->male_radioButton->isChecked() || ui->female_radioButton->isChecked()) {

     if (male) {gender = "male";} else if (female) {gender = "female";}


      QRegularExpression re("(0[1-9]|[12][0-9]|3[01])/(0[1-9]|[1][0-2])/(19[0-9][0-9]|20[0-9][0-9])");
      QRegularExpressionMatch match = re.match(date_of_birth);

      bool hasMatch = match.hasMatch();

     if(hasMatch){ //qInfo() << "date of birth is valid";

     if (ui->countriesBox->currentIndex() != 0){

     sp = "*@*.*";

     QString w =  QRegularExpression::wildcardToRegularExpression("*@*.*");
     QRegularExpression re(w);
     QRegularExpressionMatch match = re.match(email);
     bool hasMatch = match.hasMatch();

     if (hasMatch){

     //qInfo() << "email is valid";

     if ( password == password2 ){


      //qInfo() << password.size();
      if (password.size() <= 24 && password.size()>=8){

      //qInfo() << "password is valid";

     if (agreement){

      //qInfo() << "agreement is checked";

         valid = true;


    } else { ui->message_Label->setText("Agreement is not checked..."); }

    } else { ui->message_Label->setText("Password is not validated..."); }

    } else { ui->message_Label->setText("Passwords do not match..."); }

    } else { ui->message_Label->setText("Email is not validated..."); }
         
    } else { ui->message_Label->setText("Country selection is not validated..."); }

    } else { ui->message_Label->setText("Date of birth is not validated..."); }

    } else { ui->message_Label->setText("Gender selection is not validated..."); }

    } else { ui->message_Label->setText("Nickname is not validated..."); }

    } else { ui->message_Label->setText("Full name is not validated..."); }


    //////////////////////////////////////////////////////////////////


    if (valid){

        country = ui->countriesBox->currentText();

        request = "register:";
        request.append(full_name + ":");
        request.append(nickname + ":");
        request.append(date_of_birth + ":");
        request.append(gender + ":");
        request.append(country + ":");
        request.append(email + ":");

        QByteArray hash = password.toUtf8();
        QString hashed_password = QCryptographicHash::hash(hash, QCryptographicHash::Sha256).toHex();

        request.append(hashed_password + ":");
        request.append("true");

        ui->message_Label->setText("Processing...");
        ui->message_Label_2->setText(ui->message_Label->text());

        emit server_request(request);

    }


}

void RegisterNewUserObject::server_feedback(QString message){
    if (message == "Registration success... Please activate your account..." ){
       ui->resendEmailButton->setEnabled(true);
       nextPage();
       ui->message_Label->setText(message);
       ui->message_Label_2->setText(ui->message_Label->text());
    }


    if (message == "Activation success..."){
        QTimer::singleShot(3200, this, [=](){

            nextPage();
            previousPage();
            this->close();
        });
    }
}

void RegisterNewUserObject::activateNewAccount(){

    if(ui->activation_code_Prompt->text().size() == 20){
    QString request;
    request = "activate_user_account:";
    request.append(ui->activation_code_Prompt->text());

    ui->message_Label->setText("Processing...");
    ui->message_Label_2->setText(ui->message_Label->text());

    emit server_request(request);
    } else {
        ui->message_Label_2->setText("Activation code is not validated...");
    }

}

void RegisterNewUserObject::resendActivationCode(){

    QString sp = "*@*.*";
    //match.setPatternSyntax(QRegExp::Wildcard);

    QString w =  QRegularExpression::wildcardToRegularExpression("*@*.*");
    QRegularExpression re(w);
    QRegularExpressionMatch match = re.match(ui->email_Prompt->text());
    bool hasMatch = match.hasMatch();

    if (hasMatch){

        ui->message_Label->setText("Processing...");
        ui->message_Label_2->setText(ui->message_Label->text());

        emit server_request("resendActivationCode:" + ui->email_Prompt->text());

    } else { ui->message_Label_2->setText("Email is not validated...");}


}

void RegisterNewUserObject::closeEvent (QCloseEvent *event)
{
    Q_UNUSED(event);

        ui->full_name_Prompt->clear();
        ui->nick_Prompt->clear();
        ui->date_of_birthPrompt->clear();
        ui->countriesBox->setCurrentIndex(0);
        ui->email_Prompt->clear();
        ui->password_Prompt->clear();
        ui->password_2_Prompt->clear();
        ui->male_radioButton->setChecked(true);
        ui->agreement_checkBox->setChecked(false);
        ui->agreement_textBox->home();
        ui->message_Label->setText("...");

        ui->activation_code_Prompt->clear();
}
