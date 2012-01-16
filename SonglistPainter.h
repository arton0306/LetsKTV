#ifndef SONGLISTPAINTER_H
#define SONGLISTPAINTER_H

#include <QPixmap>
#include "SongDatabase.h"

class SonglistPainter
{
public:
    /*---------------------------------------------
                        Functions
    ---------------------------------------------*/
    SonglistPainter( SongDatabase const * aSongDatabase = 0 ); // = 0 for temp
    void makePdf( QString aFileName );

private:
    /*---------------------------------------------
                         Types
    ---------------------------------------------*/
    enum ColumnType
    {
        SONGID,
        SONGTITLE,
        SINGERNAME,
    };

    /*---------------------------------------------
                        Functions
    ---------------------------------------------*/
    int getTableTitleBeginY( QRect const & aPrinter ) const;
    int getTableSubTitleBeginY( QRect const & aPrinter ) const;
    int getTableBeginY( QRect const & aPrinter ) const;

    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    SongDatabase const * mSongDatabase;
};

#endif // SONGLISTPAINTER_H
