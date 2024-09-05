QT       += core gui network xml sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14
TEMPLATE = app
TARGET = remind_test

QMAKE_CFLAGS_RELEASE += -g
QMAKE_CXXFLAGS_RELEASE += -g
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO -= -O2
QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
CONFIG += force_debug_info

DEFINES += QT_DEPRECATED_WARNINGS
project = $$PWD/../..

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/mainwindow.cpp \

HEADERS += \
    $$PWD/mainwindow.h \
    $$PWD/msg.h \

DEFINES += _BUILDING_QX_HANGLOK

INCLUDEPATH += $${project}
INCLUDEPATH += $${project}/include
INCLUDEPATH += $${project}/include/interface
INCLUDEPATH += $${project}/include/define
INCLUDEPATH += $${project}/include/CommunicationUtils

#unix {
#    INCLUDEPATH += $${midleware}/include/linux/third_party/include \
#                   $${midleware}/include/linux/third_party/include/boost \
#                   $${midleware}/third_party/amqpcpp \
#                   $${midleware}/third_party/amqpcpp/rabbitmq-c \
#                   $${midleware}/third_party/amqpcpp/rabbitmq-c/include \
#}

win32 {
    LIBS += $${project}/deploy_64/windows_64/RemindConfig.lib
    LIBS += $${project}/deploy_64/windows_64/RemindCommunicationStack.lib
}

unix {
    LIBS += -L$${project}/deploy_64/linux_64 -lRemindConfig
    LIBS += -L$${project}/deploy_64/linux_64 -lRemindCommunicationStack
    LIBS += -L$${project}/deploy_64/linux_64 -lrabbitmq
    LIBS += -L$${project}/deploy_64/linux_64 -lboost_chrono
    LIBS += -L$${project}/deploy_64/linux_64 -lamqpcpp
}

win32:DESTDIR = $${project}/deploy_64/windows_64
unix:DESTDIR = $${project}/deploy_64/linux_64


