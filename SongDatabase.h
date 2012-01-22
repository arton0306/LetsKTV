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
    Song const & getSong( int aNthSong ) const;
    bool isEmpty() const;
    std::vector<Song> getSongNameOrderList() const;

private:
    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/

    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    std::vector<Song> mSongs;
};


#endif // SONGDATABASE_H
