#include "VideoWindow.h"
#include "SongEntry.h"
#include <Qtimer>

const int ONE_SECOND = 1000;

VideoWindow::VideoWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    mVideoWidget = new Phonon::VideoWidget( this );
    mGridLayout->addWidget( mVideoWidget );
    setupConnections();

    mMediaObject = new Phonon::MediaObject( this );
    mMediaObject->setTickInterval( ONE_SECOND );
    Phonon::createPath( mMediaObject, mVideoWidget );

    mAudioOutput = new Phonon::AudioOutput( Phonon::VideoCategory, this );
    Phonon::createPath( mMediaObject, mAudioOutput );

    playSong( "abc.mpg" );
}

VideoWindow::~VideoWindow()
{
}

void VideoWindow::setupConnections()
{
    
}

void VideoWindow::playSong( SongEntry const & aSongEntry )
{
    
}

void VideoWindow::playSong( QString aSongFilePath )
{
    mMediaObject->stop();

    mMediaObject->setCurrentSource( QString( aSongFilePath ) );
    if (!mMediaObject->hasVideo()) {
        QEventLoop eventLoop;
        QTimer timer;
        timer.setSingleShot(true);
        timer.setInterval(3 * ONE_SECOND);
        connect( &timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
        //connect( mMediaObject, SIGNAL(hasVideoChanged(bool)), eventLoop, SLOT(quit()));
        timer.start();
        eventLoop.exec();
    }

    mMediaObject->play();
}
