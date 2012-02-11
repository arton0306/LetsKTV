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
    static WordManager * getInstance();
    int compare( CompareOrderType aOrder, QString const & aX, QString const & aY );
    int getWordLength( QString const & aStr );
    bool isHeadEnglishLetter( QString const & aString );
    bool isEnglishLetter( QChar const & aChar );
    bool isHalfWidthLetter( QChar const & aChar );
    QString getZuinToken( QChar const & aChar );
    double getWordWidthCount( QString const & aString );

private:
    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/
    WordManager();
    void readStrokeOrderFile();
    void readZuinOrderFile();

    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    static WordManager * sWordManager;
    QMap<QChar, int> mChineseToStrokeCountTable;
    QMap<QChar, int> mChineseToZuinOrderTable;
    QMap<QChar, QString> mChineseToZuinTable; // just save the header token for the time being
};

#endif // WORDMANAGER_H
