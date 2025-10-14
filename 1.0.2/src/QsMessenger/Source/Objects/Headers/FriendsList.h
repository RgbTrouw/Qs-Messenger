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

#ifndef FRIENDS_LIST_H
#define FRIENDS_LIST_H

#include "../../Windows/IMWindows/Headers/IM_WindowObject.h"
#include "FriendsGroup.h"
#include "Peer.h"

#include <QObject>

class FriendsListObject : public QObject
{
    Q_OBJECT
public:
    explicit FriendsListObject(QObject *parent = nullptr);

    QString data;
    QList< GroupObject *> groups;

    int nr_of_groups;

public slots:
    void set_data(QString data);

    GroupObject* group_at(int index);
    GroupObject* newGroup();
    IM_WindowObject* get_im_at(int index);

    void clear();

signals:

};

#endif // FRIENDS_LIST_H
