#include "debug.h"
#include "KtvMainWindow.h"
#include "SongDatabase.h"

KtvMainWindow::KtvMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
}

KtvMainWindow::~KtvMainWindow()
{
}

void KtvMainWindow::setSongDatabase( SongDatabase * aSongDatabase )
{
    mSongDatabase = aSongDatabase;
    qDebug() << "KtvMainWindow set mSongDatabase";
}
