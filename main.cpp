#include <QtGui/QApplication>
#include "debug.h"
#include "KtvMainWindow.h"
#include "VideoWindow.h"
#include "SongDbWindow.h"

int main(int argc, char *argv[])
{
    QApplication letsKtv(argc, argv);
    #ifdef Q_WS_WIN
        qInstallMsgHandler( debugWinMsgHandler );
    #endif
    KtvMainWindow ktvMainWindow;
    ktvMainWindow.show();

    VideoWindow videoWindow;
    videoWindow.show();

    SongDbWindow songDbWindow;
    songDbWindow.show();

    return letsKtv.exec();
}
