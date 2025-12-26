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

#ifndef GROUPHEADERWIDGET_H
#define GROUPHEADERWIDGET_H

#include <QMouseEvent>
#include <QWidget>
#include <QEvent>
#include <QMenu>


namespace Ui {
class GroupHeaderWidget;
}

class GroupHeaderWidget : public QWidget
{
    Q_OBJECT



public:
    explicit GroupHeaderWidget(QWidget *parent = nullptr);
    ~GroupHeaderWidget();

    QString GroupName;

    QString counter;
    QString iconLabel;
    QString currentType = "all";

    QMenu *contextMenu = new QMenu();
    QAction *addNewUserAction = new QAction();
    QAction *addNewGroupAction = new QAction();
    QAction *removeGroupAction = new QAction();

    QFont contextMenuFont;

public slots:

    void setName(QString name);
    void setCounterLabel(QString data);


    void hover(bool value);
    bool eventFilter(QObject *object, QEvent *event);
    void customContextMenu(QPoint positionPoint);
    void setIconMode(QString mode);

signals:

    void changePeersDisplay(QString type);

private:
    Ui::GroupHeaderWidget *ui;

    void mousePressEvent(QMouseEvent * event);

};

#endif // GROUPHEADERWIDGET_H
