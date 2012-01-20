#ifndef SONGDBWINDOW_H
#define SONGDBWINDOW_H

#include <QMainWindow>
#include <QString>
#include "ui_SongDbWindow.h"
#include "Song.h"

class SongDatabase;
class SonglistPainter;

class SongDbWindow : public QMainWindow,
                     private Ui::SongDbWindow
{
    Q_OBJECT

public:
    explicit SongDbWindow(QWidget *parent = 0);
    ~SongDbWindow();

public slots:

private slots:
    QString selectSongFolder();
    void toSong( const QModelIndex & aQModelIndexInSongTable );
    void writePdfFile();

signals:
    void sgnlSongDatabaseChanged( SongDatabase * aSongDatabase );
    void sgnlDoubleClickOneSong( Song const & aSong );

private:
    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/
    void setupActions();
    void setupConnections();
    void dumpSongFolder();

    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    SongDatabase * mSongDatabase;
};

#endif // SONGDBWINDOW_H
