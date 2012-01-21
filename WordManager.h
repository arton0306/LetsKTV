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
    static void test();

private:
    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/
    WordManager();
    static void checkInit();
    static void readStrokeOrderFile();
    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    static bool isInit;
    static QMap<QString, int> * strokeTable;
    static QMap<QString, int> * zuinTable;
};

#endif // WORDMANAGER_H
