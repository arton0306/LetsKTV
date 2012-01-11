#ifndef SONGMODEL_H
#define SONGMODEL_H

#include <QString>
#include <vector>
#include "SongEntry.h"

class SongModel
{
public:
    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/
    SongModel( QString aSongFolderPath );
    int getSongCount() const;
    SongEntry const & getSong( int aNthSong ) const;

private:
    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    std::vector<SongEntry> mSongs;
};

#endif // SONGMODEL_H
