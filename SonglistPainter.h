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
        SINGER,
    };

    /*---------------------------------------------
                        Functions
    ---------------------------------------------*/
    int getTableTitleBeginY( QRect const & aPrinter ) const;
    int getTableSubTitleBeginY( QRect const & aPrinter ) const;
    int getTableBeginY( QRect const & aPrinter ) const;

    int getHlineBeginY( QPrinter & aPrinter, int aRowIndex ) const;
    int getRowHeight( QPrinter & aPrinter ) const;
    double getColWidth( QPrinter & aPrinter, int aColIndex ) const;
    void drawSongText( QPainter & aPainter, QRect const & aRect, QString const & aString, ColumnType aColType );
    void drawOnePage( QPrinter & aPrinter, QPainter & aPainter, int aSongBeginIndex );
    double estimatedFontSize( QRect const & aRect, QString const & aString ) const;
    void drawSinger( QPainter & aPainter, QRect const & aRect, QString const & aString ) const;
    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    SongDatabase const * mSongDatabase;
};

#endif // SONGLISTPAINTER_H
