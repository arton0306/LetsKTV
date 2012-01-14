#include "VideoWindow.h"
#include "Song.h"
#include <QtGlobal>
#include <Qtimer>

const int ONE_SECOND = 1000;
const int PREFINISH_HINT_MSEC = ONE_SECOND * 30;

VideoWindow::VideoWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    mVideoWidget = new Phonon::VideoWidget( this );
    mGridLayout->addWidget( mVideoWidget );

    mMediaObject = new Phonon::MediaObject( this );
    mMediaObject->setTickInterval( ONE_SECOND );
    Phonon::createPath( mMediaObject, mVideoWidget );

    mAudioOutput = new Phonon::AudioOutput( Phonon::VideoCategory, this );
    Phonon::createPath( mMediaObject, mAudioOutput );

    setupConnections();
}

VideoWindow::~VideoWindow()
{
}

void VideoWindow::setupConnections()
{
    mMediaObject->setPrefinishMark( PREFINISH_HINT_MSEC );
    connect( mMediaObject, SIGNAL(prefinishMarkReached(qint32)), this, SIGNAL(sgnlSongAlmostEnded()) );
    connect( mMediaObject, SIGNAL(finished()), this, SIGNAL(sgnlSongEnded()) );
}

void VideoWindow::playSong( Song const & aSong )
{
    playSong( aSong.getFilePath() );
}

void VideoWindow::playSong( QString aSongFilePath )
{
    mMediaObject->stop();

    mMediaObject->setCurrentSource( QString( aSongFilePath ) );
    if (!mMediaObject->hasVideo()) {
        QEventLoop eventLoop;
        QTimer timer;
        timer.setSingleShot(true);
        timer.setInterval(3 * ONE_SECOND); // at most waiting for 3 seconds
        connect( &timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
        connect( mMediaObject, SIGNAL(hasVideoChanged(bool)), &eventLoop, SLOT(quit()));
        timer.start();
        eventLoop.exec();
    }

    mMediaObject->play();
}
