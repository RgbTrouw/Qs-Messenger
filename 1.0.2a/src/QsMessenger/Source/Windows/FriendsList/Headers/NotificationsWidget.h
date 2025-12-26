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

#ifndef NOTIFICATIONSWIDGET_H
#define NOTIFICATIONSWIDGET_H

#include "NoticeLabelObject.h"

#include <QSpacerItem>
#include <QWidget>
#include <QTimer>
#include <QList>


namespace Ui {
class NotificationsWidget;
}

class NotificationsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NotificationsWidget(QWidget *parent = nullptr);
    ~NotificationsWidget();

    QList<NoticeLabelObject *> noticesList;

public slots:
    void newNotification(QString availability, QString username);
    void closeNotice();
    void createNotice();

private:
    Ui::NotificationsWidget *ui;

     QSpacerItem *verticalSpacer = new QSpacerItem(0,1000, QSizePolicy::Expanding, QSizePolicy::Expanding);
};

#endif // NOTIFICATIONSWIDGET_H
