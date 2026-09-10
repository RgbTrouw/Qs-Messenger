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

#ifndef PEERWIDGET_H
#define PEERWIDGET_H

#include "../../IMWindows/Headers/IM_WindowObject.h"
#include <QWidget>
#include <QEvent>
#include <QIcon>
#include <QMenu>
 

namespace Ui {
class PeerWidget;
}

class PeerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PeerWidget(QWidget *parent = nullptr);
    ~PeerWidget();

    IM_WindowObject *imWidget = new IM_WindowObject();

    QString plain_data;
    QStringList peer_data;

    QString name;
    QString email;
    QString status_message;
    QString availability;
    int availability_int;

    QIcon list_icon;
    QPixmap avatar;

    QString spacer = "";
    QString separator = "  -  ";

    QMenu *contextMenu = new QMenu();
    QAction *moveToGroupUpAction = new QAction();
    QAction *moveToGroupDownAction = new QAction();
    QAction *removeUserAction = new QAction();

    QFont contextMenuFont;



public slots:
    void hover(bool value);
    bool eventFilter(QObject *object, QEvent *event);

    void set_plain_data(QString plain_peer_data);
    void customContextMenu(QPoint positionPoint);

    void removeUser();

    void moveToGroupUp();
    void moveToGroupDown();

signals:

    void removeUserSignal(QString thisEmail);
    void refreshPeerAvatar(QString email);

    void moveToGroupUpSignal(QString thisEmail);
    void moveToGroupDownSignal(QString thisEmail);


private:
    Ui::PeerWidget *ui;




};

#endif // PEERWIDGET_H
