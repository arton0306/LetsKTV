#include <QtGui/QApplication>
#include "ktvmainwindow.h"
#include "videowindow.h"
#include "songdatabasewindow.h"

int main(int argc, char *argv[])
{
    QApplication letsKtv(argc, argv);
    KtvMainWindow ktvMainWindow;
    ktvMainWindow.show();

    VideoWindow videoWindow;
    videoWindow.show();

    SongDatabaseWindow songDatabaseWindow;
    songDatabaseWindow.show();

    return letsKtv.exec();
}
