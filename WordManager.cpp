#include <QTextStream>
#include <QStringList>
#include <QFile>
#include <cassert>
#include <algorithm>
#include "WordManager.h"
#include "debug.h"

WordManager * WordManager::wordManager = NULL;

WordManager::WordManager()
{
}

/* static */ bool WordManager::isInit()
{
    return ( NULL != wordManager );
}

/**Function****************************************************************
   Synopsis     [ According to the rule of order, return the relation. ]
   Description  [ aX > aY return 1, aX == aY return 0, aX < aY return -1]
   SideEffects  [ none ]
**************************************************************************/
/* static */ int WordManager::compare( CompareOrderType aOrder, QString const & aX, QString const & aY )
{
    checkInit();
    if ( MEANING_LENGTH_ORDER == aOrder )
    {
        if ( getWordLength( aX ) < getWordLength( aY ) ) return -1;
        if ( getWordLength( aX ) > getWordLength( aY ) ) return 1;
        return 0;
    }
    else if ( STROKE_ORDER == aOrder )
    {
        QMap<QString, int> const & stroke = wordManager->mStrokeTable;
        for ( int i = 0; i < std::min( getWordLength( aX ), getWordLength( aY ) ); ++i )
        {
            if ( stroke.contains( aX[i] ) && stroke.contains( aY[i] ) )
            {
                if ( stroke[aX[i]] < stroke[aY[i]] ) return -1;
                if ( stroke[aX[i]] > stroke[aY[i]] ) return 1;
                continue;
            }
            if ( stroke.contains( aX[i] ) ) return -1;
            if ( stroke.contains( aY[i] ) ) return 1;
            if ( aX[i] < aY[i] ) return -1;
            if ( aX[i] > aY[i] ) return 1;
            continue;
        }
        return 0;
    }
    else
    {
        return true;
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
/* static */ int WordManager::getWordLength( QString const & aStr )
{
    assert( WordManager::isInit() );
    int result = 0;
    bool isInLetterLanguege = false;
    bool isInNumber = false;
    for ( int i = 0; i < aStr.count(); ++i )
    {
        if ( aStr[i].isLower() || aStr[i].isUpper() ) // a Unicode Word "isLetter", don't use it
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

/* static */ void WordManager::checkInit()
{
    if ( wordManager == NULL )
    {
        wordManager = new WordManager;
        wordManager->readStrokeOrderFile();
    }
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
        mStrokeTable[line.at(0)] = line.at(1).toInt();
    }
    file.close();
}
