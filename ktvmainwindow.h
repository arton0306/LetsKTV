#ifndef KTVMAINWINDOW_H
#define KTVMAINWINDOW_H

#include <QMainWindow>
#include "ui_KtvMainWindow.h"

class SongDatabase;

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
    void setSongDatabase( SongDatabase * aSongDatabase );

private:
    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    SongDatabase * mSongDatabase;

};

#endif // KTVMAINWINDOW_H
