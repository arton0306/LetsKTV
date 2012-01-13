#ifndef SONGTABLEMODEL_H
#define SONGTABLEMODEL_H

#include <vector>
#include <QAbstractTableModel>
#include <QString>
#include "SongDatabase.h"

class SongTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    /*---------------------------------------------
                         Types
    ---------------------------------------------*/
    enum SongTableTitleType
    {
        // the order is the same with the order of table titles in UI
        ID,
        SINGER,
        SONGNAME,
        GENDER,
        LANGUAGE,
        TIMELENGTH,
        FILEPATH,
        NOTES,

        TITLE_COUNT
    };

    /*---------------------------------------------
                        Functions
    ---------------------------------------------*/
    explicit SongTableModel( SongDatabase * aSongDatabase, QObject *parent = 0 );
    int rowCount( const QModelIndex &aParent ) const;
    int columnCount( const QModelIndex &aParent ) const;
    QVariant headerData( int aSection, Qt::Orientation aOrientation, int aRole ) const;
    QVariant data( const QModelIndex & aIndex, int aRole ) const;

signals:

public slots:

private:
    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/
    void dumpSongs();
    static QString const & getTableHeaderText( int aSection );

    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    SongDatabase * mSongDatabase;

};

#endif // SONGTABLEMODEL_H
