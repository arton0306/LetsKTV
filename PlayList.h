/*
This class is not used, but just prepare for replacing the mPlayList in PlayListTableModel
, if more functions must be added in PlayList.
*/

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <deque>
#include "Song.h"

class PlayList
{
public:
    PlayList();
    void push_back( Song const * aSong );
    void push_front( Song const * aSong );
    void pop_front();
    Song const * front();
    void remove( int aIndex );
    void shuffle();

private:
    std::deque<Song const *> mPlayList;
};

#endif // PLAYLIST_H
