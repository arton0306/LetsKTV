#include <QtGui/QApplication>
#include "KtvMainWindow.h"
#include "VideoWindow.h"
#include "SongDbWindow.h"

int main(int argc, char *argv[])
{
    QApplication letsKtv(argc, argv);
    KtvMainWindow ktvMainWindow;
    ktvMainWindow.show();

    VideoWindow videoWindow;
    videoWindow.show();

    SongDbWindow songDbWindow;
    songDbWindow.show();

    return letsKtv.exec();
}
