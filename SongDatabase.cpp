#include <algorithm>
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

SongDatabase::SongDatabase( std::vector<Song> aSongList )
    : mSongs( aSongList )
{
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

std::vector<Song> SongDatabase::getSongNameOrderList() const
{
    std::vector<Song> result = mSongs;
    std::sort( result.begin(), result.end(), compareSongName );
    return result;
}

std::vector<Song> SongDatabase::getSongSingerOrderList() const
{
    std::vector<Song> result = mSongs;
    std::sort( result.begin(), result.end(), compareSinger );
    return result;
}
