#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <deque>
#include "SongEntry.h"

class PlayList
{
public:
    PlayList();
    void push_back( SongEntry const * aSongEntry );
    void push_front( SongEntry const * aSongEntry );
    void pop_front();
    SongEntry const * front();
    void remove( int aIndex );
    void shuffle();

private:
    std::deque<SongEntry const *> mPlayList;
};

#endif // PLAYLIST_H
