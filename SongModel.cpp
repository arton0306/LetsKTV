#include <QDir>
#include "SongModel.h"

SongModel::SongModel( QString aSongFolderPath )
{
    QDir dir;
    dir.setPath( aSongFolderPath );
    dir.setFilter( QDir::Files | QDir::NoSymLinks );
    dir.setSorting( QDir::Name );

    const QFileInfoList fileList = dir.entryInfoList();
    for ( int i = 0; i < fileList.size(); ++i )
    {
        SongEntry songEntry( fileList.at( i ).baseName() );
        songEntry.setFilePath( fileList.at( i ).absoluteFilePath() );
        songEntry.setTimeLength( SongEntry::TIME_UNKNOWN );
        songEntry.setId( i + 1 ); // so that the id of song begining from 1
        mSongs.push_back( songEntry );
    }
}

int SongModel::getSongCount() const
{
    return mSongs.size();
}

SongEntry const & SongModel::getSong( int aNthSong ) const
{
    return mSongs[aNthSong];
}
