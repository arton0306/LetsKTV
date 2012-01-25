#ifndef PLAYLISTTABLEMODEL_H
#define PLAYLISTTABLEMODEL_H

#include <deque>
#include <QAbstractTableModel>
#include "Song.h"

class PlayListTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    /*---------------------------------------------
                         Types
    ---------------------------------------------*/
    enum PlayListTableTitleType
    {
        // the order is the same with the order of table titles in UI
        SINGER,
        SONGNAME,

        TITLE_COUNT
    };

    /*---------------------------------------------
                        Functions
    ---------------------------------------------*/
    explicit PlayListTableModel(QObject *parent = 0);
    bool isEmpty() const;
    int rowCount( const QModelIndex &aParent ) const;
    int columnCount( const QModelIndex &aParent ) const;
    QVariant headerData( int aSection, Qt::Orientation aOrientation, int aRole ) const;
    QVariant data( const QModelIndex & aIndex, int aRole ) const;
    void addSong( Song const & aSong );
    void removeFrontSong();
    Song const & front() const;
    void shufflePlayList();

signals:

public slots:

private:
    /*---------------------------------------------
                        Functions
    ---------------------------------------------*/
    static QString const & getTableHeaderText( int aSection );

    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    std::deque<Song const *> mPlayList;
};

#endif // PLAYLISTTABLEMODEL_H
