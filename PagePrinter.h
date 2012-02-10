#ifndef PAGE_H
#define PAGE_H

#include <vector>
#include <QString>
#include <QPrinter>
#include <QPainter>
#include "Song.h"
#include "Page.h"

namespace SongBook
{
    class PagePrinter
    {
    public:
        PagePrinter( Page const & aPage );
        void print( QPrinter & aPrinter, QPainter & aPainter ) const;

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

        double getHlineBeginY( QPrinter & aPrinter, int aRowIndex ) const;
        double getRowHeight( QPrinter & aPrinter ) const;
        double getColWidth( QPrinter & aPrinter, int aColIndex ) const;
        void drawSongText( QPainter & aPainter, QRect const & aRect, QString const & aString, ColumnType aColType ) const;
        double estimatedFontSize( QRect const & aRect, QString const & aString ) const;
        void drawSinger( QPainter & aPainter, QRect const & aRect, QString const & aString ) const;

        /*---------------------------------------------
                            Variable
        ---------------------------------------------*/
        Page mPage;
    };
}

#endif // PAGE_H
