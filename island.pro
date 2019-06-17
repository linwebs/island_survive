#-------------------------------------------------
#
# Project created by QtCreator 2019-03-31T02:02:52
# Version: 0.28
# Last edit time 2019-06-18 02:16
#
#-------------------------------------------------

QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = island
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
          resources_big

SOURCES += \
    bag.cpp \
    blood.cpp \
    main.cpp \
    mainwindow.cpp \
    gamewindow.cpp \
    map.cpp \
    struct.cpp \
    system.cpp \
    oldmemorywindow.cpp \
    ruleintrowindow.cpp \
    action.cpp \
    energy.cpp \
    player.cpp \
    gamewindowscene.cpp \
    teamintro.cpp

HEADERS += \
    bag.h \
    blood.h \
    mainwindow.h \
    gamewindow.h \
    map.h \
    system.h \
    oldmemorywindow.h \
    ruleintrowindow.h \
    action.h \
    energy.h \
    player.h \
    gamewindowscene.h \
    teamintro.h

FORMS += \
    mainwindow.ui \
    oldmemorywindow.ui \
    ruleintrowindow.ui \
    teamintro.ui
#    gamewindow.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    .gitignore \
    README.md
