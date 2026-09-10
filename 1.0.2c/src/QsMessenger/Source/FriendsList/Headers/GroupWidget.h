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

#ifndef GROUPWIDGET_H
#define GROUPWIDGET_H

#include "GroupHeaderWidget.h"
#include "PeerWidget.h"

#include <QWidget>
#include <QEvent>
#include <QIcon>
 
namespace Ui {
class GroupWidget;
}

class GroupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GroupWidget(QWidget *parent = nullptr);
    ~GroupWidget();


    QString plain_group_data;
    QList < PeerWidget *> peers;
    QString group_name;

    GroupHeaderWidget *groupHeader = new GroupHeaderWidget();

    int group_list_position_index;

    int peers_online;
    int peers_total;

    QString virtualDirection = "up";

    QIcon item_icon;

public slots:


    void set_group_name(QString name);
    void set_plain_data(QString data);

    void clearPeersDisplay();
    void changePeersDisplay(QString currentType);

    void updateUsersOnline();


    QString get_group_name();
    int usersOnlineCount();

    void addNewUser();
    void addNewGroup();
    void removeGroup();
    void imGroup();

    void appendLastPeer();


    void hover(bool value);
    bool eventFilter(QObject *object, QEvent *event);

signals:

    void addToGroupSignal(QString groupName);
    void addNewGroupSignal();
    void removeGroupSignal(QString groupName);
    void imGroupSignal(QString groupName);

private:
    Ui::GroupWidget *ui;
    PeerWidget *pw = new PeerWidget();



};

#endif // GROUPWIDGET_H
