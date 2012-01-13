#include <algorithm>
#include "PlayList.h"

PlayList::PlayList()
{
}

void PlayList::push_back( SongEntry const * aSongEntry )
{
    mPlayList.push_back( aSongEntry );
}

void PlayList::push_front( SongEntry const * aSongEntry )
{
    mPlayList.push_front( aSongEntry );
}

void PlayList::pop_front()
{
    mPlayList.pop_front();
}

SongEntry const * PlayList::front()
{
    mPlayList.front();
}

void PlayList::remove( int aIndex )
{
    mPlayList.erase( mPlayList.begin() + aIndex );
}

void PlayList::shuffle()
{
    random_shuffle( mPlayList.begin(), mPlayList.end() );
}

