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

#include <QWidget>
#include <QTimer>

namespace Ui {
class FriendRequestObject;
}

class FriendRequestObject : public QWidget
{
    Q_OBJECT

public:
    explicit FriendRequestObject(QWidget *parent = nullptr);
    ~FriendRequestObject();

    QString email;
    QString groupName;

private slots:
    void add();
    void close_window();


public slots:
    void feedback(QString message);
    void closeEvent(QCloseEvent *event);


signals:
    void addNewUser();


private:
    Ui::FriendRequestObject *ui;

    QTimer *st = new QTimer();
};

