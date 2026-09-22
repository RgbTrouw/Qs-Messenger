QT = websockets sql

TARGET = 'QsMessengerServer'
CONFIG   += console
CONFIG   += c++17
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    QsMessengerServer.cpp \
    client.cpp \
    main.cpp

HEADERS += \
    QsMessengerServer.h \
    client.h


QMAKE_CXXFLAGS += -std=c++17
