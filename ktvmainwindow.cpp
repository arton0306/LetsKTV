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
    DEBUG() << "KtvMainWindow set mSongDatabase";
}

void KtvMainWindow::addSongToPlayList( Song const & aSong )
{
    if ( mPlayListTableModel->isEmpty() )
    {
        mPlayListTableModel->addSong( aSong );
        emit sgnlPlaySong( mPlayListTableModel->front() );
    }
    else
    {
        mPlayListTableModel->addSong( aSong );
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

    // in case that user cut song when playlist is empty
    if ( !mPlayListTableModel->isEmpty() )
    {
        mPlayListTableModel->removeFrontSong();
    }
    if ( !mPlayListTableModel->isEmpty() )
    {
        emit sgnlPlaySong( mPlayListTableModel->front() );
    }
}

void KtvMainWindow::songAlmostEnded()
{
    DEBUG() << "song almost ended()";
}

void KtvMainWindow::setupConnections()
{
}
