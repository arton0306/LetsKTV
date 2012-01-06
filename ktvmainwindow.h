#ifndef KTVMAINWINDOW_H
#define KTVMAINWINDOW_H

#include <QMainWindow>
#include "ui_ktvmainwindow.h"

class KtvMainWindow : public QMainWindow,
                      private Ui::KtvMainWindow
{
    Q_OBJECT

public:
    explicit KtvMainWindow(QWidget *parent = 0);
    ~KtvMainWindow();
};

#endif // KTVMAINWINDOW_H
