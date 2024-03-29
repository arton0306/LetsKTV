#ifndef VIDEOWINDOW_H
#define VIDEOWINDOW_H

#include <QMainWindow>
#include <QString>
#include <phonon>
#include "ui_VideoWindow.h"

class QShortcut;
class Song;

class VideoWindow : public QMainWindow,
                    private Ui::VideoWindow
{
    Q_OBJECT

public:
    explicit VideoWindow(QWidget *parent = 0);
    ~VideoWindow();

public slots:
    void rotateChannel();
    void cutPlay();
    void playSong( Song const & aSong );
    void playSong( QString aSongFilePath );
    void showAddSongSuccess( Song const & aSong );
    void showAddSongFailed();

signals:
    void sgnlSongEnded();
    void sgnlSongAlmostEnded();
    void sgnlAddSong( int aSongId );

private:
    /*---------------------------------------------
                        Types
    ---------------------------------------------*/
    enum ChannelType
    {
        LEFT_CHANNEL,
        RIGHT_CHANNEL,
        STEREO_CHANNEL,

        CHANNEL_COUNT
    };

    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    Phonon::MediaObject * mMediaObject;
    Phonon::VideoWidget * mVideoWidget;
    Phonon::AudioOutput * mAudioOutput;

    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/
    void setupConnections();
    bool eventFilter(QObject *target, QEvent *event);
    void switchToChannel( ChannelType aChannel );
    QString getStrFromNumKey( Qt::Key aKey );
    void requestAddSong();
};

#endif // VIDEOWINDOW_H
