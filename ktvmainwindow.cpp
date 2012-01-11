#include "debug.h"
#include "KtvMainWindow.h"
#include "SongModel.h"

KtvMainWindow::KtvMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
}

KtvMainWindow::~KtvMainWindow()
{
}

void KtvMainWindow::setSongModel( SongModel * aSongModel )
{
    mSongModel = aSongModel;
    qDebug() << "KtvMainWindow set mSongModel";
}
