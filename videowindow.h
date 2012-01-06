#ifndef VIDEOWINDOW_H
#define VIDEOWINDOW_H

#include <QMainWindow>
#include "ui_VideoWindow.h"

class VideoWindow : public QMainWindow,
                    private Ui::VideoWindow
{
    Q_OBJECT

public:
    explicit VideoWindow(QWidget *parent = 0);
    ~VideoWindow();
};

#endif // VIDEOWINDOW_H
