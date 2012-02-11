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
    int compare( CompareOrderType aOrder, QString const & aX, QString const & aY ) const;
    int getWordLength( QString const & aStr ) const;
    bool isHeadEnglishLetter( QString const & aString ) const;
    bool isEnglishLetter( QChar const & aChar ) const;
    bool isHalfWidthLetter( QChar const & aChar ) const;
    QString getZuinToken( QChar const & aChar ) const;
    double getWordWidthCount( QString const & aString ) const;
    QString getZuinTable() const;

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
