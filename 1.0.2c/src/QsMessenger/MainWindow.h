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

 
#include "Source/FriendsList/Headers/FriendshipResponseObject.h"
#include "Source/OtherWindows/Headers/RecoverPasswordObject.h"
#include "Source/OtherWindows/Headers/RegisterNewUserObject.h"
#include "Source/FriendsList/Headers/CreateNewGroupObject.h"
#include "Source/FriendsList/Headers/FriendRequestObject.h"
#include "Source/FriendsList/Headers/FriendsListWidget.h"
#include "Source/OtherWindows/Headers/SettingsObject.h"
#include "Source/IMWindows/Headers/IM_WindowObject.h"
#include "Source/OtherWindows/Headers/About.h"
#include "Source/IMWindows/im_group.h"

#include "ui_MainWindow.h"

#include <QtMultimedia/QMediaPlayer>
#include <QtWebSockets/QWebSocket>
#include <QtNetwork/QSslError>
#include <QStandardItemModel>
#include <QSystemTrayIcon>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QStandardItem>
#include <QtCore/QList>
#include <QApplication>
#include <QMainWindow>
#include <QtCore/QUrl>
#include <QSettings>
#include <QObject>
#include <QWidget>
#include <QMovie>
#include <QTimer>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    ////////////////////////////////////////////////////////////////////////////////////////////// Main Window

    void onWindowsStartup();
    void closeEvent (QCloseEvent *event);

    /////////////////////////////////////////////////////////////////////////////////////////////// Main Window Menus

    void closeApplication();
    void showHideMainWindow();

    /////////////////////////////////////////////////////////////////////////////////////////////// Socket

    void onConnected();
    void onDisconnected();

    void reconnect();

    void onTextMessageReceived(QString message);
    void processBinaryMessage(QByteArray data);
    void processBinaryFrame(QByteArray data, bool isLastFrame);
    void onSslErrors(QList<QSslError> errors);
    void onSocketError(QAbstractSocket::SocketError error);

    void connectionManager();

    void updateHostAddress(QString address);

    /////////////////////////////////////////////////////////////////////////////////////////////// Network

    void signIn();
    void signOut();
    void autologin();

    void keepAlive();


    ////////////////////////// Pre Login //////////////////////////////////////

    void registerNewUserMenu();
    void registrationRequest(QString request);

    void recoverPasswordMenu();
    void recoverPasswordRequest(QString request);


    ////////////////////////// Post Login //////////////////////////////////////


    /// ** Status

    void changeAvatar();
    void changeAvailability(int index);
    void updateStatusMessage();

    void lastLoginCounter(QString time, int counter);

    /// ** Friends List

    //void onFriendsListItemDoubleClicked(const QModelIndex &index);
    //void friendsListContextMenu(const QPoint &point);

    void addToGroup(QString groupName);
    void addNewGroup();
    void addNewGroupConfirmation(QString groupName);

    void removeGroup(QString groupName);

    void removeUser(QString email);
    //void addNewGroup();

    void moveToGroupDown(QString email);
    void moveToGroupUp(QString email);

    void imGroupWindow(QString groupName);


    /// ** Friend Request

    void respondFriendRequest(QString email, QString response);
    //void sendFriendRequest(QString email);

    /// ** Instant Messages

    void retrieve_avatar();
    void refreshPeerAvatar(QString email);
    void send_im(QString peerEmail, QString message);
    void send_file_request(QString peerEmail, QString transferId, QString fileName, QString fileSize);
    void respond_file_request(QString peerEmail, QString transferId, bool accepted);
    void send_file_payload(QString peerEmail, QString transferId, QString filePath);
    void have_read(QString peerEmail);
    void get_prev_messages(QString peerEmail, QString index);
    void clearArchive(QString peerEmail);

    void playAudio(QString path);

    void imGroup(QString message, QString groupName);


    ////////////////////////////////////////////////////////////////////////////////////////////////// Other

    void delay(int seconds);


signals:
    void server_response(QString);

private:
    IM_WindowObject *prepareImWindow(QString peerEmail);

    Ui::MainWindow *ui;
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(QIcon("/usr/local/share/QsMessenger/Resources/icons/smiley_offline.png"));

    QMenu *trayMenu = new QMenu();
    QMovie *movie = new QMovie("loading.gif");

    QSoundEffect *audioEffect = new QSoundEffect();

    QSettings *savedSettings = new QSettings();
    QTimer *autoLoginTimer = new QTimer();

    QString hostAddress = "";
    bool connected;

    QAction *hostnameAction = new QAction();

    QAction *showHideAction = new QAction();
    QAction *signInAction = new QAction();
    QAction *closeAppAction = new QAction();

    FriendsListWidget *friendsWidget = new FriendsListWidget();
    CreateNewGroupObject *addNewGroupWindow = new CreateNewGroupObject();
    FriendRequestObject *addNewUserWindow = new FriendRequestObject();
    //IM_Group *imGroupWindow = new IM_Group();

    FriendshipResponseObject *friendshipResponseWindow = new FriendshipResponseObject();

    RegisterNewUserObject *registerNewUserWindow = new RegisterNewUserObject();
    RecoverPasswordObject *recoverPasswordWindow = new RecoverPasswordObject();

    SettingsObject *settingsWindow = new SettingsObject();

    About *aboutWindow = new About();

    QWebSocket *m_webSocket = new QWebSocket();

    QString hostAddressAndPort;
    QString searchPattern;

    QString myUsername;
    QString myEmail;

    QString session_id;
    QString previousMsgBuffer;

    QStandardItemModel *itemsModel = new QStandardItemModel();
    //FriendsListObject *peerList = new FriendsListObject();
    QList<QStandardItem *> friendsListItemsModel;
    QList<IM_WindowObject *> imList;
    QFont contextMenuFont;
    QFont notificationFont;


    bool ticker = true;


};
