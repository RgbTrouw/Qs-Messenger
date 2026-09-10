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

#ifndef IM_GROUP_H
#define IM_GROUP_H

#include <QWidget>

namespace Ui {
class IM_Group;
}

class IM_Group : public QWidget
{
    Q_OBJECT

public:
    explicit IM_Group(QWidget *parent = nullptr);
    ~IM_Group();

    QString groupName;

private:
    Ui::IM_Group *ui;

private slots:
    void sendMessage();

signals:

    void sendGroupMessageSignal(QString message, QString groupName);
};

#endif // IM_GROUP_H
