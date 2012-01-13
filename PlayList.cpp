#include <algorithm>
#include "PlayList.h"

PlayList::PlayList()
{
}

void PlayList::push_back( Song const * aSong )
{
    mPlayList.push_back( aSong );
}

void PlayList::push_front( Song const * aSong )
{
    mPlayList.push_front( aSong );
}

void PlayList::pop_front()
{
    mPlayList.pop_front();
}

Song const * PlayList::front()
{
    return mPlayList.front();
}

void PlayList::remove( int aIndex )
{
    mPlayList.erase( mPlayList.begin() + aIndex );
}

void PlayList::shuffle()
{
    random_shuffle( mPlayList.begin(), mPlayList.end() );
}

