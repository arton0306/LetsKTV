#include "Windows.h"
#include "Mmsystem.h"
#include "debug.h"
#include "VideoWindow.h"
#include "Song.h"
#include <QtGlobal>
#include <Qtimer>
#include <QShortcut>
#include <QKeyEvent>

const int ONE_SECOND = 1000;
const int PREFINISH_HINT_MSEC = ONE_SECOND * 30;

VideoWindow::VideoWindow(QWidget *parent)
    : QMainWindow(parent)
    , mMediaObject( NULL )
    , mVideoWidget( NULL )
    , mAudioOutput( NULL )
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

    /********************************************************************************
    I don't know why I cannot just install this videoWindow.
    If I just use installEventfilter(this), when the mVideoWidget is in full screen,
    the event can not be got. If I just use mVideoWidget->ins..., I can not got event
    when mVideoWidget is not in full screen. I don't know why.
    ********************************************************************************/
    mVideoWidget->installEventFilter( this );
    installEventFilter( this );
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

bool VideoWindow::eventFilter(QObject *target, QEvent *event)
{
    /******************************************************************************
    When a key pressed, KeyPress and ShortcutOverride will be triggered
    in a very short time in some unknown condition. I don't know why this happened.
    // if ( event->type() == QEvent::KeyPress || event->type() == QEvent::ShortcutOverride )
    *******************************************************************************/
    if ( event->type() == QEvent::ShortcutOverride )
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        DEBUG() << ("Ate key press %d", keyEvent->key());
        switch ( keyEvent->key() )
        {
            case Qt::Key_Asterisk:
                rotateChannel();
                break;
            case Qt::Key_Slash:
                cutPlay();
                break;
            default:
                break;
        }
        return true;
    }
    else if ( target == mVideoWidget && event->type() == QEvent::MouseButtonPress )
    {
        DEBUG() << "click on video widget";
        if ( mVideoWidget->isFullScreen() )
        {
            mVideoWidget->exitFullScreen();
            DEBUG() << "full screen => exit fullscreen";
        }
        else
        {
            mVideoWidget->setFullScreen( true );
            DEBUG() << "not full screen => full screen";
        }
    }

    return QMainWindow::eventFilter(target, event);
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

/*********************************************************************************
The channel switch ref:
   http://msdn.microsoft.com/en-us/library/windows/desktop/dd743874(v=vs.85).aspx
********************************************************************************/
void VideoWindow::rotateChannel()
{
    static int channel = STEREO_CHANNEL + 1; // start from the next channel of stereo
    switchToChannel( (ChannelType)( channel % CHANNEL_COUNT ) );
    ++channel;
}

void VideoWindow::switchToChannel( ChannelType aChannel )
{
    DWORD dwVolume;
    if (waveOutGetVolume(NULL, &dwVolume) == MMSYSERR_NOERROR)
    {
        switch ( aChannel )
        {
            case LEFT_CHANNEL:
                waveOutSetVolume( NULL, 0x0000FFFF );
                DEBUG() << "switch to left channel";
                break;
            case RIGHT_CHANNEL:
                waveOutSetVolume( NULL, 0xFFFF0000 );
                DEBUG() << "switch to right channel";
                break;
            case STEREO_CHANNEL:
                waveOutSetVolume( NULL, 0xFFFFFFFF );
                DEBUG() << "switch to stereo";
                break;
            default:
                DEBUG() << "shouldn't be here";
                break;
        }
    }
}

void VideoWindow::cutPlay()
{
    DEBUG() << "cut play!";
    mMediaObject->stop();
    sgnlSongEnded();
}
