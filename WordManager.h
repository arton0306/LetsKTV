#ifndef WORDMANAGER_H
#define WORDMANAGER_H

#include <QString>
#include <QMap>
#include <QChar>

class WordManager
{
public:
    /*---------------------------------------------
                         Types
    ---------------------------------------------*/
    enum CompareOrderType
    {
        LENG_1ST_STROKE_2ND,
        ZUIN_ORDER
    };

    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/
    static bool compare( CompareOrderType aOrder, QString const & aX, QString const & aY );
    static int getWordLength( QString const & aStr );
    static bool isInit();

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
