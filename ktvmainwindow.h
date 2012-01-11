#ifndef KTVMAINWINDOW_H
#define KTVMAINWINDOW_H

#include <QMainWindow>
#include "ui_KtvMainWindow.h"

class SongModel;

class KtvMainWindow : public QMainWindow,
                      private Ui::KtvMainWindow
{
    Q_OBJECT

public:
    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/
    explicit KtvMainWindow(QWidget *parent = 0);
    ~KtvMainWindow();

public slots:
    void setSongModel( SongModel * aSongModel );

private:
    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    SongModel * mSongModel;

};

#endif // KTVMAINWINDOW_H
