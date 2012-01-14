#include "debug.h"
#include "KtvMainWindow.h"
#include "SongDatabase.h"
#include "PlayListTableModel.h"
#include "Song.h"

KtvMainWindow::KtvMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    // TODO: haven't handle the deletion of the PlayListTableModel
    mPlayListTableModel = new PlayListTableModel();
    mPlayListView->setModel( mPlayListTableModel );
    mPlayListView->setSelectionBehavior( QAbstractItemView::SelectRows );
    mPlayListView->setSelectionMode( QAbstractItemView::SingleSelection );
    mPlayListView->show();
}

KtvMainWindow::~KtvMainWindow()
{
}

void KtvMainWindow::setSongDatabase( SongDatabase * aSongDatabase )
{
    mSongDatabase = aSongDatabase;
    qDebug() << "KtvMainWindow set mSongDatabase";
}

void KtvMainWindow::addSongToPlayList( Song const & aSong )
{
    mPlayListTableModel->addSong( aSong );
}
