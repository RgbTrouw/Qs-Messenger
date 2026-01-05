QT += websockets gui core widgets multimedia

TARGET = "QsMessenger"
CONFIG   -= app_bundle

RC_ICONS = Resources/AppIcon.ico

TEMPLATE = app

SOURCES += \
    main.cpp \
    MainWindow.cpp \     
    Source/FriendsList/CreateNewGroupObject.cpp \
    Source/FriendsList/FriendsListWidget.cpp \
    Source/FriendsList/GroupHeaderWidget.cpp \
    Source/FriendsList/GroupWidget.cpp \
    Source/FriendsList/PeerWidget.cpp \
    Source/FriendsList/FriendRequestObject.cpp \
    Source/FriendsList/FriendshipResponseObject.cpp \
    Source/IMWindows/IM_WindowObject.cpp \
    Source/OtherWindows/RecoverPasswordObject.cpp \
    Source/OtherWindows/RegisterNewUserObject.cpp \
    Source/OtherWindows/SettingsObject.cpp \
    Source/OtherWindows/About.cpp \

HEADERS += \
    MainWindow.h \
    Source/FriendsList/Headers/FriendsListWidget.h \
    Source/FriendsList/Headers/GroupHeaderWidget.h \
    Source/FriendsList/Headers/GroupWidget.h \
    Source/FriendsList/Headers/PeerWidget.h \
    Source/FriendsList/Headers/FriendRequestObject.h \
    Source/FriendsList/Headers/FriendshipResponseObject.h \
    Source/FriendsList/Headers/CreateNewGroupObject.h \
    Source/IMWindows/Headers/IM_WindowObject.h \
    Source/OtherWindows/Headers/About.h \
    Source/OtherWindows/Headers/RecoverPasswordObject.h \
    Source/OtherWindows/Headers/RegisterNewUserObject.h \
    Source/OtherWindows/Headers/SettingsObject.h \

FORMS += \
    MainWindow.ui \
    Source/FriendsList/Headers/FriendsListWidget.ui \
    Source/FriendsList/Headers/GroupHeaderWidget.ui \
    Source/FriendsList/Headers/GroupWidget.ui \
    Source/FriendsList/Headers/PeerWidget.ui \
    Source/FriendsList/Headers/FriendRequestObject.ui \
    Source/FriendsList/Headers/FriendshipResponseObject.ui \
    Source/FriendsList/Headers/CreateNewGroupObject.ui \
    Source/IMWindows/Headers/IM_WindowObject.ui \
    Source/OtherWindows/Headers/About.ui \
    Source/OtherWindows/Headers/RecoverPasswordObject.ui \
    Source/OtherWindows/Headers/RegisterNewUserObject.ui \
    Source/OtherWindows/Headers/SettingsObject.ui \

