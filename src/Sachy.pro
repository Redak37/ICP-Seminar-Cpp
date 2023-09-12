#-------------------------------------------------
#
# Project created by QtCreator 2019-05-04T09:17:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chess
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

#CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++17 -fpermissive -Wunused-parameter -Wreturn-type

SOURCES += \
    figures/Jezdec.cpp \
        main.cpp \
        mainwindow.cpp\
        Figure.cpp\
        Board.cpp\
        Game.cpp\
        Field.cpp\
        Tah.cpp\
        figures/Kral.cpp\
        figures/Strelec.cpp\
        figures/Vez.cpp\
        figures/Pesec.cpp\
        figures/Dama.cpp \
    Parser.cpp \
    games/ChessGame.cpp \
    games/CheckersGame.cpp \
    Message.cpp \
    Adapter.cpp \
    gamewindow.cpp \
    CheckersParser.cpp \
    figures/CheckerPawn.cpp

HEADERS += \
    figures/Jezdec.hpp \
        mainwindow.hpp\
        Figure.hpp\
        Board.hpp\
        Game.hpp\
        Field.hpp\
        Tah.hpp\
        figures/Kral.hpp\
        figures/Strelec.hpp\
        figures/Vez.hpp\
        figures/Pesec.hpp\
        figures/Dama.hpp \
    Parser.hpp \
    games/ChessGame.hpp \
    games/CheckersGame.hpp \
    Message.hpp \
    Adapter.hpp \
    gamewindow.hpp \
    CheckersParser.hpp \
    figures/CheckerPawn.hpp

FORMS += \
        mainwindow.ui \
    gamewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
