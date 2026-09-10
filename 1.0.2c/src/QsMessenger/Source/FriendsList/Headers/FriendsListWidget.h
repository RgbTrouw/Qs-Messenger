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

#ifndef FRIENDSLISTWIDGET_H
#define FRIENDSLISTWIDGET_H

#include "GroupWidget.h"

#include <QVBoxLayout>
#include <QMessageBox>
#include <QWidget>
#include <QList>

 

namespace Ui {
class FriendsListWidget;
}

class FriendsListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FriendsListWidget(QWidget *parent = nullptr);
    ~FriendsListWidget();

    QWidget *scrollAreaContent = new QWidget();
    QVBoxLayout *vLayout = new QVBoxLayout(scrollAreaContent);

    QString data;
    QList< GroupWidget *> groups;

     QSpacerItem *verticalSpacer = new QSpacerItem(0,1000, QSizePolicy::Expanding, QSizePolicy::Expanding);

    int nr_of_groups;

public slots:

    void set_data(QString data);
    void clearWidget();

    void removeGroup(QString groupName);
    void addNewGroup(QString groupName);


    //GroupWidget* newGroup();

private:
    Ui::FriendsListWidget *ui;



};

#endif // FRIENDSLISTWIDGET_H
