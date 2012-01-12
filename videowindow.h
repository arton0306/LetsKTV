#ifndef VIDEOWINDOW_H
#define VIDEOWINDOW_H

#include <QMainWindow>
#include <QString>
#include <phonon>
#include "ui_VideoWindow.h"

class SongEntry;

class VideoWindow : public QMainWindow,
                    private Ui::VideoWindow
{
    Q_OBJECT

public:
    explicit VideoWindow(QWidget *parent = 0);
    ~VideoWindow();

public slots:
    void playSong( SongEntry const & aSongEntry );
    void playSong( QString aSongFilePath );

signals:
    void sgnlSongEnded();

private:
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
};

#endif // VIDEOWINDOW_H
