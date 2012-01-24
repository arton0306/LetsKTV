#include <QtGui/QApplication>
#include <QTextCodec>
#include "debug.h"
#include "KtvMainWindow.h"
#include "VideoWindow.h"
#include "SongDbWindow.h"
#include "PaintWidget.h"
#include "SonglistPainter.h"
#include "LabelWto.h"

int main(int argc, char *argv[])
{
    debug::setProgramTimer();

    QApplication letsKtv(argc, argv);
    #ifdef Q_WS_WIN
        qInstallMsgHandler( debug::debugWinMsgHandler );
    #endif

    // set text codec
    QTextCodec *textc = QTextCodec::codecForName("cp950");
    QTextCodec::setCodecForCStrings( textc );
    QTextCodec::setCodecForTr( textc );
    QTextCodec::setCodecForLocale( textc );
    DEBUG() << "����codec �{���}�l�K";

    VideoWindow videoWindow;
    videoWindow.show();

    KtvMainWindow ktvMainWindow;
    ktvMainWindow.show();

    SongDbWindow songDbWindow;
    songDbWindow.show();

    // PaintWidget test;
    // test.show();

    QObject::connect( &songDbWindow, SIGNAL(sgnlSongDatabaseChanged( SongDatabase * )),
                      &ktvMainWindow, SLOT(setSongDatabase( SongDatabase * )) );
    QObject::connect( &songDbWindow, SIGNAL(sgnlDoubleClickOneSong( Song const & )),
                      &ktvMainWindow, SLOT(addSongToPlayList( Song const & )) );
    QObject::connect( &videoWindow, SIGNAL(sgnlSongAlmostEnded()),
                      &ktvMainWindow, SLOT(songAlmostEnded()) );
    QObject::connect( &videoWindow, SIGNAL(sgnlSongEnded()),
                      &ktvMainWindow, SLOT(songEnded()) );
    QObject::connect( &ktvMainWindow, SIGNAL(sgnlPlaySong( Song const & )),
                      &videoWindow, SLOT( playSong( Song const & )) );
    QObject::connect( &ktvMainWindow, SIGNAL(sgnlAddSongSuccess( Song const & )),
                      &videoWindow, SLOT( showAddSongSuccess( Song const & )) );
    QObject::connect( &ktvMainWindow, SIGNAL(sgnlAddSongFailed()),
                      &videoWindow, SLOT( showAddSongFailed()) );

    ktvMainWindow.installEventFilter( &videoWindow );
    songDbWindow.installEventFilter( &videoWindow );

    return letsKtv.exec();
}
