#ifndef SONGDBWINDOW_H
#define SONGDBWINDOW_H

#include <QMainWindow>
#include "ui_SongDbWindow.h"

class SongDbWindow : public QMainWindow,
                     private Ui::SongDbWindow
{
    Q_OBJECT

public:
    explicit SongDbWindow(QWidget *parent = 0);
    ~SongDbWindow();

};

#endif // SONGDBWINDOW_H
