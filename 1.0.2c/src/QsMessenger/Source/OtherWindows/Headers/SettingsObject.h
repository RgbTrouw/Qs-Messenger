/*   Qs Messenger v 1.0.2c Instant Messaging Application
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

#ifndef SETTINGSOBJECT_H
#define SETTINGSOBJECT_H
 
#include <QWidget>
#include <QSettings>

namespace Ui {
class SettingsObject;
}

class SettingsObject : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsObject(QWidget *parent = nullptr);
    ~SettingsObject();

public slots:
    void setSettings(QString host, QString port);

private slots:
    void updateHostAddressValue();

    void connectionStack();
    void generalStack();
    void privacyStack();

signals:
    void updateHostAddress(QString host);

private:
    Ui::SettingsObject *ui;

    QSettings savedSettings;
};

#endif // SETTINGSOBJECT_H
