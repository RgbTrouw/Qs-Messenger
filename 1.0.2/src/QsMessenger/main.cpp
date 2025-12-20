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



#include "ui_MainWindow.h"
#include "MainWindow.h"

#include <QtCore/QCoreApplication>
#include <QSharedMemory>
#include <QObject>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setOrganizationDomain("qsmessenger.net");
    app.setOrganizationName(QLatin1String("Rgb Trust"));
    app.setApplicationName(QLatin1String("Qs Messenger"));



    MainWindow mw;
    int x=1642; int y=42; mw.setGeometry(x,y,274,980);
    mw.show();


    return app.exec();
}

