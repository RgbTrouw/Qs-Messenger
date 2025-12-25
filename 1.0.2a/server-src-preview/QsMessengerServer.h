
/*   QsMessenger Server v 1.0.2a Instant Messaging Application
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

#include <client.h>

#include <QtNetwork/QSslError>
#include <QFileSystemWatcher>
#include <QtCore/QByteArray>
#include <QWebSocketServer>
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QSqlQuery>
#include <QTimer>
#include <QFile>
#include <QList>
#include <QMap>


class QsMessengerServer : public QObject
{
    Q_OBJECT
public:
    explicit QsMessengerServer(quint16 port, QObject *parent = nullptr);
    ~QsMessengerServer() override;

private Q_SLOTS:
    void onNewConnection();
    void onSslErrors(QList<QSslError> errors);
    void dateTime();

    void close_client(QString session_id);

    void logData(QString data);

    void clearDatabase();

    void fwMessage(QString senderEmail, QString recipientEmail, QString message, QString timeMseconds);
    void updateStatus(QString email, QStringList peersList);
    void fwFriendRequest(QString myEmail, QString peerEmail);

    void openDataBase();

private:


    int clients_id = 0;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    QWebSocketServer *m_pWebSocketServer;

    QList<client *> clients;

    QList<QWebSocket *> m_clients;

    QString response;
    QMap<QString, QString> response_hash;

    QTimer *tmr= new QTimer();
    QMap<QString, QTimer *> tmr_hash;
    QTimer *ss = new QTimer();
    QMap<QString, QTimer *> ss_hash;

    bool list_type=false;
    QMap<QString, bool> list_type_hash;
    QString previous_list;

    QString session_id_request="session_id";


    bool compact_list;
    bool reset = true;


    QString logPath;

    QString mysqlUsername;
    QString mysqlPassword;


};

