#include "PlayListTableModel.h"
#include "debug.h"

PlayListTableModel::PlayListTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

bool PlayListTableModel::isEmpty() const
{
    return 0 == rowCount( QModelIndex() );
}

int PlayListTableModel::rowCount( const QModelIndex &aParent ) const
{
    Q_UNUSED( aParent );
    return mPlayList.size();
}

int PlayListTableModel::columnCount( const QModelIndex &aParent ) const
{
    Q_UNUSED( aParent );
    return TITLE_COUNT;
}

QVariant PlayListTableModel::headerData( int aSection, Qt::Orientation aOrientation, int aRole ) const
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

QVariant PlayListTableModel::data( const QModelIndex & aIndex, int aRole ) const
{
    if ( !aIndex.isValid() ) return QVariant();
    if ( aRole == Qt::DisplayRole )
    {
        switch ( aIndex.column() )
        {
            case SINGER:     return mPlayList[aIndex.row()]->getSinger();
            case SONGNAME:   return mPlayList[aIndex.row()]->getSongName();
            default:
                DEBUG() << "getdata column error";
                return QVariant();
        }
    }
    return QVariant();
}

QString const & PlayListTableModel::getTableHeaderText( int aSection )
{
    static bool isInit = false;
    static QList<QString> tableHeaders;
    if ( !isInit )
    {
        // the order must be the same with PlayListTableTitleType ( can be refactor to map )
        tableHeaders.push_back( "歌手" );
        tableHeaders.push_back( "歌名" );
        isInit = true;
    }
    return tableHeaders.at( aSection );
}

void PlayListTableModel::addSong( Song const & aSong )
{
    beginInsertRows( QModelIndex(), mPlayList.size(), mPlayList.size() );
    mPlayList.push_back( &aSong );
    endInsertRows();
}

void PlayListTableModel::removeFrontSong()
{
    beginRemoveRows( QModelIndex(), 0, 0 );
    mPlayList.pop_front();
    endRemoveRows();
}

Song const & PlayListTableModel::front() const
{
    DEBUG() << "Now PlayList size: " << mPlayList.size() << " get front";
    return *mPlayList[0];
}
