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
        int getTitleBeginY() const;
        int getSubTitleBeginY( QRect const & aRect ) const;
        int getTableBeginY( QRect const & aPrinter ) const;

        double getHlineBeginY( QPrinter & aPrinter, int aRowIndex ) const;
        double getRowHeight( QPrinter & aPrinter ) const;
        double getColWidth( QPrinter & aPrinter, int aColIndex ) const;
        void drawSongText( QPainter & aPainter, QRect const & aRect, QString const & aString, ColumnType aColType ) const;
        double estimatedFontSize( QRect const & aRect, QString const & aString ) const;
        void drawSinger( QPainter & aPainter, QRect const & aRect, QString const & aString ) const;
        void drawTitle( QPrinter & aPrinter, QPainter & aPainter ) const;
        void drawSubTitle( QPrinter & aPrinter, QPainter & aPainter ) const;

        /*---------------------------------------------
                            Variable
        ---------------------------------------------*/
        Page mPage;
    };
}

#endif // PAGE_H
