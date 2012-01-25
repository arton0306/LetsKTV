#ifndef KTVMAINWINDOW_H
#define KTVMAINWINDOW_H

#include <QMainWindow>
#include "ui_KtvMainWindow.h"

class PlayListTableModel;
class SongDatabase;
class Song;
class VideoWindow;

class KtvMainWindow : public QMainWindow,
                      private Ui::KtvMainWindow
{
    Q_OBJECT

public:
    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/
    explicit KtvMainWindow( QWidget *parent = 0 );
    ~KtvMainWindow();

public slots:
    void setSongDatabase( SongDatabase * aSongDatabase );
    void addSongToPlayList( Song const & aSong );
    void addSongToPlayList( int aSongId );
    void songEnded();
    void songAlmostEnded();

signals:
    void sgnlPlaySong( Song const & aSong );
    void sgnlAddSongFailed();
    void sgnlAddSongSuccess( Song const & aSong );

private:
    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    SongDatabase * mSongDatabase;
    PlayListTableModel * mPlayListTableModel;
    Song const * mCurPlayingSong;

    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/
    void playFirstSongInPlayList();
    void setupConnections();
};

#endif // KTVMAINWINDOW_H
