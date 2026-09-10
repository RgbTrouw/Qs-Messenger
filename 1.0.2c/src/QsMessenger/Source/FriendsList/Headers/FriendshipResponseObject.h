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

#include <QWidget>
#include <QTimer>
 
namespace Ui {
class FriendshipResponseObject;
}

class FriendshipResponseObject : public QWidget
{
    Q_OBJECT


public:
    explicit FriendshipResponseObject(QWidget *parent = nullptr);
    ~FriendshipResponseObject();

public slots:
    void from(QString email);
    void closeEvent(QCloseEvent *event);


private slots:

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void feedback();

signals:
    void respond_fr(QString email, QString response);

private:
    Ui::FriendshipResponseObject *ui;
    QTimer *st = new QTimer();
};


