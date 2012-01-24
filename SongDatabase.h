#ifndef SONGDATABASE_H
#define SONGDATABASE_H

#include <QString>
#include <vector>
#include "Song.h"

class SongDatabase
{
public:
    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/
    SongDatabase( QString aSongFolderPath );
    SongDatabase( std::vector<Song> aSongList );
    int getSongCount() const;
    Song const & getSongById( int aSongId ) const;
    Song const & getSong( int aNthSong ) const;
    bool isEmpty() const;
    std::vector<Song> getSongNameOrderList() const;
    std::vector<Song> getSongSingerOrderList() const;

private:
    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/

    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    std::vector<Song> mSongs; // currently, assume the song id is compact ( no hole );
};


#endif // SONGDATABASE_H
