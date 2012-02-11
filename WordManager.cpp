#include <QTextStream>
#include <QStringList>
#include <QFile>
#include <cassert>
#include <algorithm>
#include "WordManager.h"
#include "debug.h"

WordManager * WordManager::sWordManager = NULL;

WordManager::WordManager()
{
}

/* static */ WordManager * WordManager::getInstance()
{
    if ( sWordManager == NULL )
    {
        sWordManager = new WordManager;
        sWordManager->readStrokeOrderFile();
        sWordManager->readZuinOrderFile();
    }
    return sWordManager;
}

/**Function****************************************************************
   Synopsis     [ According to the rule of order, return the relation. ]
   Description  [ aX > aY return 1, aX == aY return 0, aX < aY return -1]
   SideEffects  [ none ]
**************************************************************************/
int WordManager::compare( CompareOrderType aOrder, QString const & aX, QString const & aY )
{
    switch ( aOrder )
    {
        case MEANING_LENGTH_ORDER:
            if ( getWordLength( aX ) < getWordLength( aY ) ) return -1;
            if ( getWordLength( aX ) > getWordLength( aY ) ) return 1;
            return 0;
        case STROKE_ORDER: // purposely no break;
        case ZUIN_ORDER:
            for ( int i = 0; i < std::min( getWordLength( aX ), getWordLength( aY ) ); ++i )
            {
                QMap<QChar, int> const & orderTable =
                    ( aOrder == STROKE_ORDER ? mStrokeTable : mZuinOrderTable );
                if ( orderTable.contains( aX[i] ) && orderTable.contains( aY[i] ) )
                {
                    if ( orderTable[aX[i]] < orderTable[aY[i]] ) return -1;
                    if ( orderTable[aX[i]] > orderTable[aY[i]] ) return 1;
                    continue;
                }
                if ( orderTable.contains( aX[i] ) ) return -1;
                if ( orderTable.contains( aY[i] ) ) return 1;
                if ( aX[i] < aY[i] ) return -1;
                if ( aX[i] > aY[i] ) return 1;
                continue;
            }
            return 0;
        default:
            qCritical() << "CompareOrderType not exists";
            return 0;
    }
}

/**Function****************************************************************
   Synopsis     [ getWordLength returns the meaningful word length ]
   Description  [ The calculation of word length is according to
                  different languages. In English, several letters compose
                  a word. In Chinese, there does not exist the concept of
                  letter. Ex: "One Night In 北京" will be counted as 5.
                  "100種生活" will be counted as 4. "戀上(另)一個人" will
                  be counted as 6.
   SideEffects  [ none ]
**************************************************************************/
int WordManager::getWordLength( QString const & aStr )
{
    int result = 0;
    bool isInLetterLanguege = false;
    bool isInNumber = false;
    for ( int i = 0; i < aStr.count(); ++i )
    {
        if ( isEnglishLetter( aStr[i] ) )
        {
            isInLetterLanguege = true;
        }
        else if ( aStr[i].isNumber() )
        {
            isInNumber = true;
        }
        else
        {
            if ( isInLetterLanguege || isInNumber )
            {
                isInLetterLanguege = false;
                isInNumber = false;
                ++result;
            }
            if ( !aStr[i].isPunct() && !aStr[i].isSpace() )
            {
                ++result;
            }
        }
    }
    if ( isInLetterLanguege || isInNumber )
    {
        ++result;
    }
    return result;
}

bool WordManager::isHeadEnglishLetter( QString const & aString )
{
    return ( !aString.isEmpty() && isEnglishLetter( aString[0] ) );
}

bool WordManager::isEnglishLetter( QChar const & aChar )
{
    // a Unicode Char "isLetter", don't use it
    return aChar.isLower() || aChar.isUpper();
}

bool WordManager::isHalfWidthLetter( QChar const & aChar )
{
    return ( isEnglishLetter( aChar ) || aChar.isSpace() || aChar.isPunct() || aChar.isNumber() );
}

/**Function****************************************************************
   Synopsis     [ getWordWidthCount ]
   Description  [ A half-width word will be counted as 0.75
                  A full-width word will be counted as 1
                  return the sum ]
   SideEffects  [ none ]
**************************************************************************/
double WordManager::getWordWidthCount( QString const & aString )
{
    double result = 0;
    for ( int i = 0; i < aString.count(); ++i )
    {
        result += ( isHalfWidthLetter( aString[i] ) ? 0.75 : 1 );
    }
    return result;
}

QString WordManager::getZuinToken( QChar const & aChar )
{
    return mZuinTokenTable[ aChar ];
}

void WordManager::readStrokeOrderFile()
{
    QFile file("stroke_order.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qCritical() << "read stroke_order.txt failed";
        return;
    }
    QTextStream in(&file);
    in.setCodec( "UTF-8" );
    while (!in.atEnd()) {
        QStringList line = in.readLine().split(" ");

        // in the file, col 0 is the word, col 1 is #stroke
        mStrokeTable[line.at(0)[0]] = line.at(1).toInt();
    }
    file.close();
}

void WordManager::readZuinOrderFile()
{
    QFile file("zuin_order.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qCritical() << "read zuin_order.txt failed";
        return;
    }
    QTextStream in(&file);
    in.setCodec( "UTF-8" );
    int order = 0;
    while (!in.atEnd())
    {
        QString line = in.readLine();

        // each line begin from a ZuinToken then its Chinese Word
        for ( int i = 0; i < line.count(); ++i )
        {
            mZuinOrderTable[line[i]] = order;
            mZuinTokenTable[line[i]] = line[0]; // just save the header token for the time being
            ++order;
        }
    }
    file.close();
}
