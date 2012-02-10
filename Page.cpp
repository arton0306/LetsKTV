#include "Page.h"
#include "PagePrinter.h"

using namespace SongBook;

Page::Page()
{
}

Page::Page( QString aTitle, QString aSubTitle )
    : mTitle( aTitle )
    , mSubTitle( aSubTitle )
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

void Page::setSubTitle( QString aSubTitle )
{
    mSubTitle = aSubTitle;
}

QString Page::getSubTitle() const
{
    return mSubTitle;
}

void Page::print( QPrinter & aPrinter, QPainter & aPainter ) const
{
    PagePrinter( *this ).print( aPrinter, aPainter );
}
