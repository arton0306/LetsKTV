#include <QtGui/QApplication>
#include <QTextCodec>
#include "debug.h"
#include "KtvMainWindow.h"
#include "VideoWindow.h"
#include "SongDbWindow.h"
#include "PaintWidget.h"
#include "SonglistPainter.h"

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
    DEBUG() << "測試codec 程式開始…";

    VideoWindow videoWindow;
    videoWindow.show();

    KtvMainWindow ktvMainWindow( &videoWindow );
    ktvMainWindow.show();

    SongDbWindow songDbWindow;
    songDbWindow.show();

    // PaintWidget test;
    // test.show();

    QObject::connect( &songDbWindow, SIGNAL(sgnlSongDatabaseChanged( SongDatabase * )),
             &ktvMainWindow, SLOT(setSongDatabase( SongDatabase * )) );
    QObject::connect( &songDbWindow, SIGNAL(sgnlDoubleClickOneSong( Song const & )),
             &ktvMainWindow, SLOT(addSongToPlayList( Song const & )) );

    return letsKtv.exec();
}
