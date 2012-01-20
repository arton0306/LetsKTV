#ifndef SONGDBWINDOW_H
#define SONGDBWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QSettings>
#include "ui_SongDbWindow.h"
#include "Song.h"

class SongDatabase;
class SonglistPainter;

class SongDbWindow : public QMainWindow,
                     private Ui::SongDbWindow
{
    Q_OBJECT

public:
    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/
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
    QString getDefaultFolder( QString aSettingKey ) const;

    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    SongDatabase * mSongDatabase;
    QSettings mPreference;
};

#endif // SONGDBWINDOW_H
