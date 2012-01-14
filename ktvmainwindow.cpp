#include "debug.h"
#include "KtvMainWindow.h"
#include "SongDatabase.h"
#include "PlayListTableModel.h"
#include "Song.h"
#include "VideoWindow.h"

KtvMainWindow::KtvMainWindow( VideoWindow * aVideoWindow, QWidget *parent )
    : QMainWindow( parent )
    , mVideoWindow( aVideoWindow )
{
    setupUi( this );
    setupConnections();

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

void KtvMainWindow::songEnded()
{
    qDebug() << "song ended()";
    mPlayListTableModel->removeFrontSong();
    if ( !mPlayListTableModel->isEmpty() )
    {
        mVideoWindow->playSong( mPlayListTableModel->front() );
    }
}

void KtvMainWindow::songAlmostEnded()
{
    qDebug() << "song almost ended()";
}

void KtvMainWindow::setupConnections()
{
    connect( mVideoWindow, SIGNAL(sgnlSongAlmostEnded()), this, SLOT(songAlmostEnded()) );
    connect( mVideoWindow, SIGNAL(sgnlSongEnded()), this, SLOT(songEnded()) );
}
