#include <QDir>
#include "SongDatabase.h"

SongDatabase::SongDatabase( QString aSongFolderPath )
{
    QDir dir;
    dir.setPath( aSongFolderPath );
    dir.setFilter( QDir::Files | QDir::NoSymLinks );
    dir.setSorting( QDir::Name );

    const QFileInfoList fileList = dir.entryInfoList();
    for ( int i = 0; i < fileList.size(); ++i )
    {
        Song song( fileList.at( i ).baseName() );
        song.setFilePath( fileList.at( i ).absoluteFilePath() );
        song.setTimeLength( Song::TIME_UNKNOWN );
        song.setId( i + 1 ); // so that the id of song begining from 1
        mSongs.push_back( song );
    }
}

int SongDatabase::getSongCount() const
{
    return mSongs.size();
}

bool SongDatabase::isEmpty() const
{
    return getSongCount() == 0;
}

Song const & SongDatabase::getSong( int aNthSong ) const
{
    return mSongs[aNthSong];
}
