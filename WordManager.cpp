#include <QTextStream>
#include <QStringList>
#include <QFile>
#include <cassert>
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

/* static */ bool WordManager::compare( CompareOrderType aOrder, QString const & aX, QString const & aY )
{
    checkInit();
    if ( LENG_1ST_STROKE_2ND == aOrder )
    {
        QMap<QString, int> const & stroke = wordManager->mStrokeTable;
        if ( getWordLength( aX ) == getWordLength( aY ) )
        {
            for ( int i = 0; i < getWordLength( aX ); ++i )
            {
                if ( stroke.contains( aX[i] ) && stroke.contains( aY[i] ) && stroke[aX[i]] != stroke[aY[i]] ) return stroke[aX[i]] < stroke[aY[i]];
                else if ( stroke.contains( aX[i] ) ) return false;
                else if ( stroke.contains( aY[i] ) ) return true;
                else if ( aX[i] != aY[i] ) return aX[i] < aY[i];
                else continue;
            }
            return true;
        }
        else
        {
            return getWordLength( aX ) < getWordLength( aY );
        }
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
