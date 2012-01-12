#ifndef SONGDBWINDOW_H
#define SONGDBWINDOW_H

#include <QMainWindow>
#include <QString>
#include "ui_SongDbWindow.h"
#include "SongModel.h"

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

signals:
    void sgnlSongModelChanged( SongModel * aSongModel );
    void sgnlDoubleClickOneSong( SongEntry * aSongEntry );

private:
    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/
    void setupActions();
    void dumpSongFolder();

    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    SongModel * mSongModel;

};

#endif // SONGDBWINDOW_H
