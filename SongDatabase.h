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
    int getSongCount() const;
    Song const & getSong( int aNthSong ) const;

private:
    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    std::vector<Song> mSongs;
};

#endif // SONGDATABASE_H
