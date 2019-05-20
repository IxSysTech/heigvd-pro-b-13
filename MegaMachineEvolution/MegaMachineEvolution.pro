#-------------------------------------------------
#
# Project created by QtCreator 2019-04-26T11:11:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MegaMachineEvolution
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

CONFIG += c++14

SOURCES += \
    StateMachines/emitteracgt.cpp \
    StateMachines/megamachine.cpp \
    StateMachines/megamachinemanager.cpp \
    dispatcher.cpp \
    GUI/main.cpp \
    GUI/mainwindow.cpp \
    GUI/parameterwindow.cpp

HEADERS += \
    GALGO/Chromosome.hpp \
    GALGO/Converter.hpp \
    GALGO/Evolution.hpp \
    GALGO/Galgo.hpp \
    GALGO/GeneticAlgorithm.hpp \
    GALGO/Parameter.hpp \
    GALGO/Population.hpp \
    GALGO/Randomize.hpp \
    GUI/mainwindow.h \
    GUI/parameterwindow.h \
    StateMachines/emitteracgt.h \
    StateMachines/megamachine.h \
    StateMachines/megamachinemanager.h \
    dispatcher.h \
    StateMachines/utils.h

FORMS += \
    GUI/mainwindow.ui \
    GUI/parameterwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/GUI/libssh/build/lib/release/ -lssh
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/GUI/libssh/build/lib/debug/ -lssh
else:unix: LIBS += -L$$PWD/GUI/libssh/build/lib/ -lssh

INCLUDEPATH += $$PWD/GUI/libssh/include
DEPENDPATH += $$PWD/GUI/libssh/include

macx: LIBS += -L$$PWD/../../../../../../../../usr/local/Cellar/libssh/0.8.7/lib/ -lssh.4.7.4
