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

#ifndef IM_H
#define IM_H

#include <QtMultimedia/QMediaPlayer>
#include <QSoundEffect>
#include <QResizeEvent>
#include <QFocusEvent>
#include <QMouseEvent>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QFocusEvent>
#include <QWidget>
#include <QFont>

 

namespace Ui {
class IM_WindowObject;
}

class IM_WindowObject : public QWidget
{
    Q_OBJECT

public:
    struct FileTransferData {
        QString transferId;
        QString filePath;
        QString fileName;
        QString fileSize;
        QString savePath;
        qint64 bytesReceived = 0;
        bool writeInitialized = false;
    };

    explicit IM_WindowObject(QWidget *parent = nullptr);
    ~IM_WindowObject();
    QString myUsername;
    QString myEmail;
    QString peer_name;
    QString email;
    QString conversationBuffer;

    QWidget *scrollAreaContent = new QWidget();
    QVBoxLayout *vLayout = new QVBoxLayout(scrollAreaContent);

    QSpacerItem *verticalSpacer = new QSpacerItem(0,1000, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSpacerItem *horizontalSpacer = new QSpacerItem(1000,0, QSizePolicy::Expanding, QSizePolicy::Expanding);

    int list_index;

    QString LoremIpsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam vel nibh lacus. Nulla sit amet consectetur augue. Duis pharetra tempus urna. Vestibulum eleifend mauris et auctor volutpat. Integer id lorem risus. Nunc massa mauris, vehicula sit amet congue eget, ornare nec eros. Nullam viverra, lectus in mollis elementum, dolor sapien suscipit sapien, eget cursus turpis nisl quis ligula.";

    QList<QString> conversationList;
    QList<int> smileysList;


public slots:

    void deelay();
    void setMyAvatar();
    void setPeerAvatar();
    void append_message(QString message, QString time);
    void prepend_message(QString msgFrom, QString msgTo, QString message, QString time);
    void receiveFileRequest(QString transferId, QString fileName, QString fileSize);
    void receiveFileResponse(QString transferId, QString response);
    void receiveFilePayload(QString transferId, QByteArray data, bool isLastFrame);
    void completeOutgoingFileTransfer(QString transferId, bool success, QString message);
    void closeEvent(QCloseEvent *event);
    void showHideNotice(bool value);



private slots:
    void sendMsg();
    void sendBuzz();
    void sendFile();
    void loadPreviousMessages();
    void showSmileys();
    void appendSmiley(QString characters);
    void resizeEvent(QResizeEvent* event);
    bool event(QEvent *event);
    void playSmileys();

    void clearArchive();

    void acceptFile();
    void declineFile();



signals:
    void send_message(QString peer, QString message);
    void send_file_request(QString peer, QString transferId, QString fileName, QString fileSize);
    void respond_file_request(QString peer, QString transferId, bool accepted);
    void send_file_payload(QString peer, QString transferId, QString filePath);
    void get_prev_messages(QString peer, QString index);
    void have_read(QString peer);
    void playAudio(QString path);
    void clearArchiveSignal(QString email);

    void receiveFile(QString peer, QString file, bool value);

private:
    void updatePendingFileRequest();

    Ui::IM_WindowObject *ui;
    int previousMsgIndex = 0;
    bool alternate = false;
    bool haveRead = true;
    //QList<MessageWidget *>

    QSpacerItem *horizontalSpacerExpanding = new QSpacerItem(1000,0, QSizePolicy::Expanding, QSizePolicy::Fixed);
    QSpacerItem *horizontalSpacerFixed = new QSpacerItem(12,0, QSizePolicy::Fixed, QSizePolicy::Fixed);

    QFont textFont;


    QSoundEffect *audioEffect = new QSoundEffect();
    QList<FileTransferData> outgoingFileRequests;
    QList<FileTransferData> activeOutgoingFileRequests;
    QList<FileTransferData> incomingFileRequests;
    QList<FileTransferData> acceptedIncomingFileRequests;
    FileTransferData pendingFileRequest;


};

#endif // IM_H
