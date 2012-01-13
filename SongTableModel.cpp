#include <QDir>
#include <QModelIndex>
#include <QVariant>
#include <QList>
#include "debug.h"
#include "SongTableModel.h"

SongTableModel::SongTableModel( SongDatabase * aSongDatabase, QObject *parent ) 
    : QAbstractTableModel( parent )
    , mSongDatabase( aSongDatabase )
{
}

int SongTableModel::rowCount( const QModelIndex &aParent ) const
{
    Q_UNUSED( aParent );
    return mSongDatabase->getSongCount();
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
            case FILEPATH:   return mSongDatabase->getSong( aIndex.row() ).getFilePath();
            case GENDER:     return mSongDatabase->getSong( aIndex.row() ).getGender();
            case ID:         return mSongDatabase->getSong( aIndex.row() ).getIdText();
            case LANGUAGE:   return mSongDatabase->getSong( aIndex.row() ).getLanguage();
            case NOTES:      return mSongDatabase->getSong( aIndex.row() ).getNotes();
            case SINGER:     return mSongDatabase->getSong( aIndex.row() ).getSinger();
            case TIMELENGTH: return mSongDatabase->getSong( aIndex.row() ).getTimeLengthText();
            case SONGNAME:   return mSongDatabase->getSong( aIndex.row() ).getSongName();
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
    for ( int i = 0; i < mSongDatabase->getSongCount(); ++i )
    {
        qDebug() << mSongDatabase->getSong( i ).getSinger() << mSongDatabase->getSong( i ).getSongName();
    }
}
