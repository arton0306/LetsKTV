#ifndef WORDMANAGER_H
#define WORDMANAGER_H

#include <QString>
#include <QMap>

class WordManager
{
public:
    /*---------------------------------------------
                         Types
    ---------------------------------------------*/
    enum CompareOrderType
    {
        STROKE_ORDER,
        ZUIN_ORDER
    };

    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/
    static int compare( CompareOrderType aOrder, QString const & aX, QString const & aY );

private:
    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/
    WordManager();
    static void checkInit();
    void readStrokeOrderFile();
    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    static WordManager * wordManager;
    QMap<QString, int> mStrokeTable;
    QMap<QString, int> zuinTable;
};

#endif // WORDMANAGER_H
