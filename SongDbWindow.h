#ifndef SONGDBWINDOW_H
#define SONGDBWINDOW_H

#include <QMainWindow>
#include <QString>
#include "ui_SongDbWindow.h"
#include "SongDatabase.h"

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
    void toSongEntry( const QModelIndex & aQModelIndexInSongTable );

signals:
    void sgnlSongDatabaseChanged( SongDatabase * aSongDatabase );
    void sgnlAddOneSong( SongEntry const & aSongEntry );

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
