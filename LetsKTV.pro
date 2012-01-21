#-------------------------------------------------
#
# Project created by QtCreator 2012-01-03T21:00:04
#
#-------------------------------------------------

QT       += core gui phonon

TARGET = LetsKTV
TEMPLATE = app


SOURCES += main.cpp\
    KtvMainWindow.cpp \
    VideoWindow.cpp \
    SongDbWindow.cpp \
    debug.cpp \
    SongTableModel.cpp \
    PlayList.cpp \
    SongDatabase.cpp \
    Song.cpp \
    PlayListTableModel.cpp \
    PaintWidget.cpp \
    SonglistPainter.cpp \
    WordManager.cpp

HEADERS  += \
    KtvMainWindow.h \
    VideoWindow.h \
    SongDbWindow.h \
    debug.h \
    SongTableModel.h \
    PlayList.h \
    SongDatabase.h \
    Song.h \
    PlayListTableModel.h \
    PaintWidget.h \
    SonglistPainter.h \
    WordManager.h

FORMS    += \
    KtvMainWindow.ui \
    VideoWindow.ui \
    SongDbWindow.ui























































win32: LIBS += -lWinMM








