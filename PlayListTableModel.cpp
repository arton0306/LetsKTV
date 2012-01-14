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
                qDebug() << "getdata column error";
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
        tableHeaders.push_back( "ºq¤â" );
        tableHeaders.push_back( "ºq¦W" );
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
    qDebug() << "Now PlayList size: " << mPlayList.size() << " get front";
    return *mPlayList[0];
}

/*
bool PlayListTableModel::setData( const QModelIndex & aIndex, const QVariant & aValue, int aRole )
{
    if ( aIndex.isValid() && aRole == Qt::DisplayRole )
    {
        Song const * song = aValue.value<Song const *>();
        switch ( aIndex.column() )
        {
            case SINGER:     return mPlayList[aIndex.row()]->getSinger();
            case SONGNAME:   return mPlayList[aIndex.row()]->getSongName();
            default:
                qDebug() << "getdata column error";
                return QVariant();
        }
        mPlayList[aIndex.row()]
    }
}

bool PlayListTableModel::insertRows( int aRow, int aCount, QModelIndex const & aModelIndex )
{
    Song const * aSong = static_cast<Song const *>( aModelIndex.internalPointer() );
    beginInsertRows( QModelIndex(), row, 
}
*/
