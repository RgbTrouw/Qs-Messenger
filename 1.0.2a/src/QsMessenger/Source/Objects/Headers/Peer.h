/*   QsMessenger Client v 1.0.2a Instant Messaging Application
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

#ifndef PEER_H
#define PEER_H

#include "../../Windows/IMWindows/Headers/IM_WindowObject.h"
#include <QStandardItemModel>
#include <QStringList>
#include <QString>
#include <QColor>
#include <QMenu>
#include <QFont>


    // #include <QDebug>

class PeerObject : public QObject
{
    Q_OBJECT

public:
    explicit PeerObject(QObject *parent = nullptr);

    QString plain_data;
    QStringList peer_data;

    QString name;
    QString email;
    QString status_message;
    QString availability;
    int availability_int;

    IM_WindowObject *im_window = new IM_WindowObject();
    int peer_list_position_index;

    QIcon list_icon;
    QPixmap avatar;

    QString spacer = "";
    QString separator = "  -  ";

    QStandardItem *item_model;
    QFont item_font;
    QColor item_color;


public slots:
    void set_plain_data(QString plain_peer_data);
    QStandardItem* get_item_model_item();
    IM_WindowObject* get_im_window();
};

#endif // PEER_H
