#include "debug.h"
#include "KtvMainWindow.h"
#include "SongDatabase.h"
#include "PlayListTableModel.h"
#include "Song.h"
#include "VideoWindow.h"

KtvMainWindow::KtvMainWindow( QWidget *parent )
    : QMainWindow( parent )
    , mSongDatabase( NULL )
    , mPlayListTableModel( NULL )
    , mCurPlayingSong( NULL )
{
    setupUi( this );
    setupConnections();

    mPlayListTableModel = new PlayListTableModel();
    mPlayListView->setModel( mPlayListTableModel );
    mPlayListView->setSelectionBehavior( QAbstractItemView::SelectRows );
    mPlayListView->setSelectionMode( QAbstractItemView::SingleSelection );
    mPlayListView->show();
}

KtvMainWindow::~KtvMainWindow()
{
    delete mPlayListTableModel;
}

void KtvMainWindow::setSongDatabase( SongDatabase * aSongDatabase )
{
    mSongDatabase = aSongDatabase;
    DEBUG() << "KtvMainWindow set mSongDatabase";
}

void KtvMainWindow::addSongToPlayList( Song const & aSong )
{
    mPlayListTableModel->addSong( aSong );
    if ( mCurPlayingSong == NULL )
    {
        playFirstSongInPlayList();
    }
    emit sgnlAddSongSuccess( aSong );
}

void KtvMainWindow::addSongToPlayList( int aSongId )
{
    if ( mSongDatabase && mSongDatabase->isIdExist( aSongId ) )
    {
        addSongToPlayList( mSongDatabase->getSongById( aSongId ) );
    }
    else
    {
        emit sgnlAddSongFailed();
    }
}

void KtvMainWindow::songEnded()
{
    DEBUG() << "song ended()";
    mCurPlayingSong = NULL;
    if ( !mPlayListTableModel->isEmpty() )
    {
        playFirstSongInPlayList();
    }
}

void KtvMainWindow::songAlmostEnded()
{
    DEBUG() << "song almost ended()";
}

void KtvMainWindow::setupConnections()
{
}

void KtvMainWindow::playFirstSongInPlayList()
{
    mCurPlayingSong = &mPlayListTableModel->front();
    mPlayListTableModel->removeFrontSong();
    emit sgnlPlaySong( *mCurPlayingSong );
}
