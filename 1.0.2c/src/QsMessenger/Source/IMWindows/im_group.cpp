#include "im_group.h"
#include "ui_im_group.h"

IM_Group::IM_Group(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IM_Group)
{
    ui->setupUi(this);
    ui->avatar->setPixmap(QPixmap("./Resources/icons/groupAvatar.png"));

    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
}

IM_Group::~IM_Group()
{
    delete ui;
}

void IM_Group::sendMessage(){

    if(ui->message->toPlainText().size() > 4){
    emit sendGroupMessageSignal(ui->message->toPlainText(), groupName);
    ui->message->clear();
    groupName = "";
    this->close();
    }

}
