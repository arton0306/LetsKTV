#ifndef WORDMANAGER_H
#define WORDMANAGER_H

#include <QString>
#include <QMap>
#include <QList>
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
    void readZuinOrderFile();

    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    static WordManager * wordManager;
    QMap<QString, int> mStrokeTable;
    QMap<QString, int> mZuinOrderTable;
    QMap<QString, QString> mZuinTokenTable; // just save the header token for the time being
};

#endif // WORDMANAGER_H
