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
    emit sgnlAddSongSuccess( aSong );
    if ( mCurPlayingSong == NULL )
    {
        playFirstSongInPlayList();
    }
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
    connect( mShufflePlayListBtn, SIGNAL(pressed()), this, SLOT(shufflePlayList()) );
    connect( mCutPlayBtn, SIGNAL(pressed()), this, SIGNAL(sgnlCutPlay()) );
}

void KtvMainWindow::shufflePlayList()
{
    mPlayListTableModel->shufflePlayList();
    emit sgnlShufflePlayList();
}

/**Function****************************************************************
   Synopsis     [ play first song in the playlist ]
   Description  [ Reading song video file will cost some time ( about 1 
                  seconds ). If the slot of sgnlPlaySong is in the same
                  thread, it will cause the feeling of delay.
   SideEffects  [ remove first song in the playlist ]
**************************************************************************/
void KtvMainWindow::playFirstSongInPlayList()
{
    mCurPlayingSong = &mPlayListTableModel->front();
    mPlayListTableModel->removeFrontSong();
    emit sgnlPlaySong( *mCurPlayingSong );
}
