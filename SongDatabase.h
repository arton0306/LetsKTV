#ifndef SONGDATABASE_H
#define SONGDATABASE_H

#include <QString>
#include <vector>
#include "SongEntry.h"

class SongDatabase
{
public:
    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/
    SongDatabase( QString aSongFolderPath );
    int getSongCount() const;
    SongEntry const & getSong( int aNthSong ) const;

private:
    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    std::vector<SongEntry> mSongs;
};

#endif // SONGDATABASE_H
