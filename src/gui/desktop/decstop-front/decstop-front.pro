QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../../brick_game/snake/classes.cpp \
    ../../../brick_game/snake/controller.cpp \
    ../../../brick_game/snake/game.cpp \
    helpfield.cpp \
    main.cpp \
    mainwindow.cpp \
    ../../../brick_game/tetris/back.c \
    ../../../brick_game/tetris/fsm.c

HEADERS += \
    ../../../brick_game/snake/classes.h \
    ../../../consts.h \
    ../../../brick_game/snake/controller.h \
    ../../../brick_game/snake/game.h \
    helpfield.h \
    mainwindow.h \
    ../../../brick_game/tetris/back.h
    ../../../brick_game/tetris/fsm.h
    ../../../brick_game/tetris/structs.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
