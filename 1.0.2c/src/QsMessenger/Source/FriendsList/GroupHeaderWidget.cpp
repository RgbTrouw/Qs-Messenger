/*   Qs Messenger Client v 1.0.2c Instant Messaging Application
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

#include "Headers/GroupHeaderWidget.h"
#include "ui_GroupHeaderWidget.h"

#include <QTimer>
 
    // #include <QDebug>

GroupHeaderWidget::GroupHeaderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupHeaderWidget)
{
    ui->setupUi(this);
    ui->expandIcon->setPixmap(QPixmap("./Resources/icons/triangle_down.png"));
    this->installEventFilter(this);
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setAttribute(Qt::WA_Hover, true);

    this->setContextMenuPolicy(Qt::CustomContextMenu);

    contextMenuFont.setPointSize(10);
    contextMenu->setFont(contextMenuFont);

    addNewGroupAction->setText("Add New Group");
    addNewUserAction->setText("Add New User");
    removeGroupAction->setText("Remove Group");
    imGroupAction->setText("IM to Group");

    addNewGroupAction->setFont(contextMenuFont);
    addNewGroupAction->setFont(contextMenuFont);
    removeGroupAction->setFont(contextMenuFont);
    imGroupAction->setFont(contextMenuFont);

    addNewUserAction->setIcon(QIcon("./Resources/icons/addUser.png"));
    addNewGroupAction->setIcon(QIcon("./Resources/icons/addGroup.png"));
    removeGroupAction->setIcon(QIcon("./Resources/icons/trashBinGroups.png"));
    imGroupAction->setIcon(QIcon("./Resources/icons/groupMessage.png"));

    contextMenu->addAction(imGroupAction);
    contextMenu->addAction(addNewUserAction);
    contextMenu->addAction(addNewGroupAction);
//    contextMenu->addAction(imGroupAction);
//    contextMenu->addAction(removeGroupAction);



    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customContextMenu(QPoint)));

}

GroupHeaderWidget::~GroupHeaderWidget()
{
    this->disconnect();
    delete ui;

}

void GroupHeaderWidget::setName(QString name){

    GroupName = name;

    ui->groupNameLabel->setText(GroupName);

}

void GroupHeaderWidget::setCounterLabel(QString data){

    ui->counterLabel->setText(data);
}

void GroupHeaderWidget::hover(bool value){

    if(value){
        this->setStyleSheet("background-color: rgb(238, 238, 236);");
    } else {
         this->setStyleSheet("background-color:rgb(255, 255, 255);");
    }

}


bool GroupHeaderWidget::eventFilter(QObject *object, QEvent *event)
{
    Q_UNUSED(object);

    bool returnValue;

    if (event->type() == QEvent::HoverEnter)
    {

        returnValue = true;
        hover(true);

    }

    if (event->type() == QEvent::HoverLeave)
    {
        returnValue = false;

        hover(false);

    }
    return returnValue;
}

void GroupHeaderWidget::customContextMenu(QPoint positionPoint){

//    qInfo() << positionPoint;

    QTimer::singleShot(1000, this , [=](){hover(false);});
    contextMenu->show();
    contextMenu->move(this->mapToGlobal(positionPoint).x(),this->mapToGlobal(positionPoint).y());

}

void GroupHeaderWidget::mousePressEvent(QMouseEvent *event){

    if(event->type() == QMouseEvent::MouseButtonPress){
        if (event->button() == Qt::LeftButton){
        emit changePeersDisplay(currentType);
        }
    };
}

void GroupHeaderWidget::setIconMode(QString mode){

    if (mode == "up"){ui->expandIcon->setPixmap(QPixmap("./Resources/icons/triangle_up.png")); }
    else if (mode == "middle"){ui->expandIcon->setPixmap(QPixmap("./Resources/icons/triangle_right.png")); }
    else if (mode == "down"){ui->expandIcon->setPixmap(QPixmap("./Resources/icons/triangle_down.png")); }

}
