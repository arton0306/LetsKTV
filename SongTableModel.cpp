#include <QDir>
#include <QModelIndex>
#include <QVariant>
#include <QList>
#include "debug.h"
#include "SongTableModel.h"

SongTableModel::SongTableModel( QString aSongFolderPath, QObject *parent ) :
    QAbstractTableModel( parent )
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

int SongTableModel::rowCount( const QModelIndex &aParent ) const
{
    Q_UNUSED( aParent );
    return mSongs.size();
}

int SongTableModel::columnCount( const QModelIndex &aParent ) const
{
    Q_UNUSED( aParent );
    return TITLE_COUNT;
}

QVariant SongTableModel::headerData( int aSection, Qt::Orientation aOrientation, int aRole ) const
{
    if ( aOrientation == Qt::Horizontal )
    {
        if ( aRole == Qt::DisplayRole )
        {
            return getTableHeaderText( aSection );
        }
    }
    return QAbstractTableModel::headerData( aSection, aOrientation, aRole );
}

QVariant SongTableModel::data( const QModelIndex & aIndex, int aRole ) const
{
    if ( !aIndex.isValid() ) return QVariant();
    if ( aRole == Qt::DisplayRole )
    {
        switch ( aIndex.column() )
        {
            case FILEPATH:   return mSongs[aIndex.row()].getFilePath();
            case GENDER:     return mSongs[aIndex.row()].getGender();
            case ID:         return mSongs[aIndex.row()].getIdText();
            case LANGUAGE:   return mSongs[aIndex.row()].getLanguage();
            case NOTES:      return mSongs[aIndex.row()].getNotes();
            case SINGER:     return mSongs[aIndex.row()].getSinger();
            case TIMELENGTH: return mSongs[aIndex.row()].getTimeLengthText();
            case SONGNAME:   return mSongs[aIndex.row()].getSongName();
            default:
            qDebug() << "getdata column error";
                return QVariant();
        }
    }
    return QVariant();
}

QString const & SongTableModel::getTableHeaderText( int aSection )
{
    static bool isInit = false;
    static QList<QString> tableHeaders;
    if ( !isInit )
    {
        // the order must be the same with SongTableTitleType ( can be refactor to map )
        tableHeaders.push_back( "歌曲編號" );
        tableHeaders.push_back( "歌手" );
        tableHeaders.push_back( "歌名" );
        tableHeaders.push_back( "性別" );
        tableHeaders.push_back( "語言" );
        tableHeaders.push_back( "時間" );
        tableHeaders.push_back( "檔案路徑" );
        tableHeaders.push_back( "備註" );
        isInit = true;
    }
    return tableHeaders.at( aSection );
}

void SongTableModel::dumpSongs()
{
    for ( size_t i = 0; i < mSongs.size(); ++i )
    {
        qDebug() << mSongs[i].getSinger() << mSongs[i].getSongName();
    }
}
