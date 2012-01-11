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

private:
    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/
    void setupActions();
    void dumpSongFolder();

    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    QString mSongFolderPath;
    SongModel * mSongModel;

    /*---------------------------------------------
                         Slot
    ---------------------------------------------*/
    private slots:
        QString selectSongFolder();
};

#endif // SONGDBWINDOW_H
