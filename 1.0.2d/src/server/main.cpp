/*   Qs-Messenger Server v 1.0.2d Instant Messaging Application
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


#include <QtCore/QCoreApplication>
#include "QsMessengerServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    quint16 port = 7080;

    QString alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    QString ip2LocationApiKey = "";

    bool log = false;
    bool verbose = false;
    bool ipFilter = false;
    bool keyDetected = false;


    bool a0=false;
    bool b0=false;


    QString allowRegion;

    QStringList argg;

    for(int i=0; i< argc; i++){

        argg << argv[i];
    }

    for(int i=0; i< argg.size(); i++){

        if(argg.at(i) == "-l"){ log = true;}

        else if(argg.at(i) == "-v"){ verbose = true;}

        else if(argg.at(i) == "-f" && argg.at(i+1).size() == 2){

            allowRegion = argg.at(i+1);



            for(int a=0; a< alpha.size(); a++){
                //qInfo() << allowRegion.left(1) + " vs " + alpha.left(a+1).right(1);
                //qInfo() << allowRegion.right(1) + " vs " + alpha.left(a+1).right(1);
                if(allowRegion.left(1) == alpha.left(a+1).right(1)){
                    //qInfo() << "a true";
                    a0 = true;
                } else {
                    //qInfo() << "a false";
                }
                if(allowRegion.right(1) == alpha.left(a+1).right(1)){
                    //qInfo() << "b true";
                    b0 = true;
                } else {
                    //qInfo() << "b false";
                }
            }

            if(a0 && b0){

                ipFilter = true;
                i += 1;
            }

        }
        else if (argg.at(i).size() == 32){
            ip2LocationApiKey = argg.at(i);
            keyDetected = true;
        }
        else if(argg.at(i) == "-h"){

            qInfo().noquote() << "Qs-MessengerServer v1.0.2d - Copyright 2026 Rgb-Trust";
            qInfo().noquote() << "Usage: ./QsMessengerServer [-h] [-v] [-l] [-f <CountryCode>] [ipLookupApiKey]";
            qInfo().noquote() << " ";
            qInfo().noquote() << "Options: ";
            qInfo().noquote() << "  -h                 display usage information";
            qInfo().noquote() << "  -v                 display server-client messages";
            qInfo().noquote() << "  -l                 log server-client messages (recommended)";
            qInfo().noquote() << "  -f <NN> <apiKey>   allow only IPs from <NN> region - use https://ip2location.io <apiKey>";
            qInfo().noquote() << " ";
            qInfo().noquote() << "Service Port SSL: 7080";
            qInfo().noquote() << " ";
            qInfo().noquote() << "Configuration:";
            qInfo().noquote() << " ";
            qInfo().noquote() << "MYSQL Database Template               - assets/messenger.sql";
            qInfo().noquote() << "MYSQL Service Username and Password   - assets/mysql_credentials";
            qInfo().noquote() << " ";
            qInfo().noquote() << "(PHP) SMTP Username and Password      - assets/mailToRegister.php";
            qInfo().noquote() << "(PHP) SMTP Username and Password      - assets/mailToRecover.php";
            qInfo().noquote() << " ";
            qInfo().noquote() << "SSL CA Root Certificate               - crt/ca_certificate.crt";
            qInfo().noquote() << "SSL Certificate                       - crt/certificate.crt";
            qInfo().noquote() << "SSL Private Key                       - crt/private.key";


            return 1;
        }

    }

    if(!ipFilter){allowRegion = "";};

    if(ipFilter && keyDetected){
        ipFilter = true;
    } else if (ipFilter && !keyDetected) {

        ipFilter = false;
        qInfo().noquote() << "No ip2Location ApiKey provided !!";

    }



    QsMessengerServer server(port, log, verbose, ipFilter, allowRegion, ip2LocationApiKey);

    Q_UNUSED(server);

    return a.exec();
}
