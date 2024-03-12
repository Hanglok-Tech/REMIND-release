QT       += core gui network xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
TEMPLATE = app
TARGET = remind_test

#解决界面中文显示乱码
msvc {
      QMAKE_CFLAGS += /utf-8
      QMAKE_CXXFLAGS += /utf-8
}

QMAKE_CFLAGS_RELEASE += -g
QMAKE_CXXFLAGS_RELEASE += -g
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO -= -O2
QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
CONFIG += force_debug_info
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += include
INCLUDEPATH += include/CommunicationUtils
INCLUDEPATH += include/define
INCLUDEPATH += include/interface

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/mainwindow.cpp \

HEADERS += \
    $$PWD/mainwindow.h \

LIBS += -l$${PWD}/deploy_64/RemindCommunicationStack
LIBS += -l$${PWD}/deploy_64/RemindConfig

DESTDIR = $${PWD}/deploy_64

