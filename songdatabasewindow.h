#ifndef SONGDATABASEWINDOW_H
#define SONGDATABASEWINDOW_H

#include <QMainWindow>
#include "ui_songdatabasewindow.h"

class SongDatabaseWindow : public QMainWindow,
                           private Ui::SongDatabaseWindow
{
    Q_OBJECT

public:
    explicit SongDatabaseWindow(QWidget *parent = 0);
    ~SongDatabaseWindow();

};

#endif // SONGDATABASEWINDOW_H
