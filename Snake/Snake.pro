TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        game.cpp \
        main.cpp

LIBS += -L$$PWD/../../PDCurses-3.8/PDCurses-3.8/wincon/ -lpdcurses


INCLUDEPATH += $$PWD/../../PDCurses-3.8/PDCurses-3.8
DEPENDPATH += $$PWD/../../PDCurses-3.8/PDCurses-3.8

HEADERS += \
    game.h
