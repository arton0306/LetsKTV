#ifndef LABELWTO_H
#define LABELWTO_H

#include "ui_LabelWto.h"
#include <Qt>
#include <QWidget>
#include <QTimer>

class LabelWto : public QWidget,
                 private Ui::LabelWto
{
    Q_OBJECT

public:
    explicit LabelWto(QWidget *parent = 0, int aFixedMsec = 1000 );
    ~LabelWto();
    void setFixedMsec( int aMsec );
    void setTextAndTimer( QString aText, int aMsec );
    void setTextAndTimer( QString aText );
    void appendText( QString aText );
    void setAlignment( Qt::Alignment aAlignment );
    QString getText();

private slots:
    void hideLabel();

private:
    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/
    void setupConnections();

    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    QTimer * mTimer;
    int mFixedMsec;
};

#endif // LABELWTO_H
