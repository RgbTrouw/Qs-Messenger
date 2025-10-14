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

#ifndef GROUP_H
#define GROUP_H

#include "Peer.h"

#include <QStandardItem>
#include <QString>
#include <QList>
#include <QFont>
#include <QIcon>

class GroupObject : public QObject
{
    Q_OBJECT

public:
    explicit GroupObject(QObject *parent = nullptr);

    QString plain_group_data;
    QList < PeerObject *> peers;
    QString group_name;

    int group_list_position_index;

    int peers_online;
    int peers_total;

    QIcon item_icon;

    QStandardItem *item_model;
    QFont item_font;
    QColor item_color;

public slots:

    void set_group_name(QString name);
    void set_plain_data(QString data);


    QString get_group_name();
    int group_peers_count();
    int group_peers_online_count();

    QStandardItem* get_item_model_item();
    PeerObject* get_user_at(int index);

};

#endif // GROUP_H
