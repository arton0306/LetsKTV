#include <QtGui/QApplication>
#include <QTextCodec>
#include "debug.h"
#include "KtvMainWindow.h"
#include "VideoWindow.h"
#include "SongDbWindow.h"

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
    qDebug() << "測試codec 程式開始…";

    KtvMainWindow ktvMainWindow;
    ktvMainWindow.show();

    VideoWindow videoWindow;
    videoWindow.show();

    SongDbWindow songDbWindow;
    songDbWindow.show();

    QObject::connect( &songDbWindow, SIGNAL(sgnlSongModelChanged( SongModel * )),
             &ktvMainWindow, SLOT(setSongModel( SongModel * )) );

    return letsKtv.exec();
}

