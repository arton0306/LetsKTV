#include <QtGui/QApplication>
#include "KtvMainWindow.h"
#include "VideoWindow.h"
#include "SongDatabaseWindow.h"

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
