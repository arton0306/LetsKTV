#ifndef VIDEOWINDOW_H
#define VIDEOWINDOW_H

#include <QMainWindow>
#include <QString>
#include <phonon>
#include "ui_VideoWindow.h"

class Song;

class VideoWindow : public QMainWindow,
                    private Ui::VideoWindow
{
    Q_OBJECT

public:
    explicit VideoWindow(QWidget *parent = 0);
    ~VideoWindow();

public slots:
    void playSong( Song const & aSong );
    void playSong( QString aSongFilePath );

signals:
    void sgnlSongEnded();
    void sgnlSongAlmostEnded();

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
    bool eventFilter(QObject *target, QEvent *event);
};

#endif // VIDEOWINDOW_H
