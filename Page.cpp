#include <QSet>
#include "WordManager.h"
#include "Page.h"
#include "PagePrinter.h"

using namespace SongBook;

Page::Page()
{
}

void Page::addSong( Song const & aSong )
{
    mSonglist.push_back( aSong );
}

Song const & Page::getSong( int aIndex ) const
{
    return mSonglist[aIndex];
}

int Page::getSongCount() const
{
    return mSonglist.size();
}

void Page::setTitle( QString aTitle )
{
    mTitle = aTitle;
}

QString Page::getTitle() const
{
    return mTitle;
}

void Page::produceSubtitle()
{
    mSubTitle = "";
    if ( isZuinHintNeeded() )
    {
        QSet<QString> headZuin;
        for ( int songIndex = 0; songIndex < mSonglist.size(); ++songIndex )
        {
            headZuin += WordManager::getInstance()->getZuinToken( mSonglist[songIndex].getSinger()[0] ); // find the zuin of first word
        }
        static QString zuin("ㄅㄆㄇㄈㄉㄊㄋㄌㄍㄎㄏㄐㄑㄒㄓㄔㄕㄖㄗㄘㄙㄧㄨㄩㄚㄛㄜㄝㄞㄟㄠㄡㄢㄣㄤㄥㄦ");
        for ( int zuinIndex = 0; zuinIndex < zuin.size(); ++zuinIndex )
        {
            if ( headZuin.contains( QString( zuin[zuinIndex] ) ) )
            {
                mSubTitle += QString( "<font color=#ff0000>" ) + zuin[zuinIndex] + QString( "</font>" );
            }
            else
            {
                mSubTitle += zuin[zuinIndex];
            }
        }
    }
}

bool Page::isZuinHintNeeded() const
{
    bool result = true;
    for ( int songIndex = 0; songIndex < mSonglist.size(); ++songIndex )
    {
        Song::LanguageType const langType = mSonglist[songIndex].getLanguageType();
        Song::GenderType const genderType = mSonglist[songIndex].getGenderType();
        if ( langType != Song::LANGUAGE_MANDARIN && langType != Song::LANGUAGE_MINNAN )
        {
            result = false;
            break;
        }
        else
        {
            if ( genderType == Song::GENDER_CHORUS ||
                 genderType == Song::GENDER_OTHERS )
            {
                result = false;
                break;
            }
        }
    }

    return result;
}

QString Page::getSubTitle() const
{
    return mSubTitle;
}

void Page::print( QPrinter & aPrinter, QPainter & aPainter ) const
{
    PagePrinter( *this ).print( aPrinter, aPainter );
}
