QT = websockets gui core widgets multimedia

TARGET = "qsmessenger"
CONFIG   -= app_bundle

RC_ICONS = Resources/AppIcon.ico

TEMPLATE = app

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    Source/Windows/FriendsList/NotificationsWidget.cpp \
    Source/Windows/FriendsList/NoticeLabelObject.cpp \
    Source/Windows/OtherWindows/About.cpp \    
    Source/Windows/IMWindows/IM_WindowObject.cpp \
    Source/Windows/IMWindows/SmileysObject.cpp \
    Source/Windows/OtherWindows/RecoverPasswordObject.cpp \
    Source/Windows/OtherWindows/RegisterNewUserObject.cpp \
    Source/Windows/FriendsList/CreateNewGroupObject.cpp \
    Source/Windows/FriendsList/FriendsListWidget.cpp \
    Source/Windows/FriendsList/GroupHeaderWidget.cpp \
    Source/Windows/FriendsList/GroupWidget.cpp \
    Source/Windows/FriendsList/PeerWidget.cpp \
    Source/Windows/FriendsList/FriendRequestObject.cpp \
    Source/Windows/FriendsList/FriendshipResponseObject.cpp \
    Source/Objects/FriendsList.cpp \
    Source/Objects/FriendsGroup.cpp \
    Source/Objects/Peer.cpp \

HEADERS += \
    MainWindow.h \
    Source/Windows/FriendsList/Headers/NotificationsWidget.h \
    Source/Windows/OtherWindows/Headers/About.h \
    Source/Windows/IMWindows/Headers/IM_WindowObject.h \
    Source/Windows/FriendsList/Headers/NoticeLabelObject.h \
    Source/Windows/IMWindows/Headers/SmileysObject.h \
    Source/Windows/OtherWindows/Headers/RecoverPasswordObject.h \
    Source/Windows/OtherWindows/Headers/RegisterNewUserObject.h \
    Source/Windows/FriendsList/Headers/FriendsListWidget.h \
    Source/Windows/FriendsList/Headers/GroupHeaderWidget.h \
    Source/Windows/FriendsList/Headers/GroupWidget.h \
    Source/Windows/FriendsList/Headers/PeerWidget.h \
    Source/Windows/FriendsList/Headers/FriendRequestObject.h \
    Source/Windows/FriendsList/Headers/FriendshipResponseObject.h \
    Source/Windows/FriendsList/Headers/CreateNewGroupObject.h \
    Source/Objects/Headers/Peer.h \
    Source/Objects/Headers/FriendsList.h \
    Source/Objects/Headers/FriendsGroup.h


INSTALLS += target

FORMS += \
    MainWindow.ui \
    Source/Windows/FriendsList/Headers/NotificationsWidget.ui \
    Source/Windows/OtherWindows/Headers/About.ui \
    Source/Windows/IMWindows/Headers/IM_WindowObject.ui \
    Source/Windows/FriendsList/Headers/NoticeLabelObject.ui \
    Source/Windows/IMWindows/Headers/SmileysObject.ui \
    Source/Windows/OtherWindows/Headers/RecoverPasswordObject.ui \
    Source/Windows/OtherWindows/Headers/RegisterNewUserObject.ui \
    Source/Windows/FriendsList/Headers/FriendsListWidget.ui \
    Source/Windows/FriendsList/Headers/GroupHeaderWidget.ui \
    Source/Windows/FriendsList/Headers/GroupWidget.ui \
    Source/Windows/FriendsList/Headers/PeerWidget.ui \
    Source/Windows/FriendsList/Headers/FriendRequestObject.ui \
    Source/Windows/FriendsList/Headers/FriendshipResponseObject.ui \
    Source/Windows/FriendsList/Headers/CreateNewGroupObject.ui

