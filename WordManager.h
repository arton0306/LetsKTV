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
        MEANING_LENGTH_ORDER,
        STROKE_ORDER,
        ZUIN_ORDER
    };

    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/
    static int compare( CompareOrderType aOrder, QString const & aX, QString const & aY );
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
