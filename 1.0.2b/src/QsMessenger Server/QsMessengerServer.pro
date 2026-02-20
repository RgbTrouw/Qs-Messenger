QT = websockets sql

TARGET = 'QsMessengerServer'
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    QsMessengerServer.cpp \
    client.cpp \
    main.cpp

HEADERS += \
    QsMessengerServer.h \
    client.h

