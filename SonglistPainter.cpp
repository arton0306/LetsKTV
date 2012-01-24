#include <QPrinter>
#include <QPainter>
#include <QPixmap>
#include "Song.h"
#include "SonglistPainter.h"
#include "debug.h"
#include <QDate>
#include <QString>
// page padding
const int PAGE_PADDING = 18; // pixel count ( 4 border )
const int LR_PAGE_PADDING = PAGE_PADDING * 2; // sum of left and right page padding

// the ratio of title, subtile, and table
const double TABLE_TITLE_RATIO_TO_HEIGHT    =  3.5 / 20.0;
const double TABLE_SUBTITLE_RATIO_TO_HEIGHT =  1.9 / 20.0;
const double TABLE_RATIO_TO_HEIGHT          = 14.6 / 20.0;

// column type
const int COLUMN_TYPE_COUNT = 3;
const Song::SongInfoType COLUMN_INFO[] = { Song::SONGID, Song::SONGNAME, Song::SINGER };

// column width ratio
const double SONGID_RATIO     = 2.0 / 10.0;
const double SONGTITLE_RATIO  = 5.5 / 10.0;
const double SINGERNAME_RATIO = 2.5 / 10.0;
const double TABLE_EACH_COL_WIDTH_RATIO[] = { SONGID_RATIO, SONGTITLE_RATIO, SINGERNAME_RATIO };

// table border, row, column
const double TABLE_BORDER = 2;  // pixel count
const int TABLE_ROW_COUNT = 18;
const int N_SONG_PER_ROW = 2;
const int TABLE_COL_COUNT = COLUMN_TYPE_COUNT * N_SONG_PER_ROW;
const int TABLE_GRID_PADDING = 3;
const int SONG_COUNT_PER_PAGE = N_SONG_PER_ROW * TABLE_ROW_COUNT;

SonglistPainter::SonglistPainter( SongDatabase const * aSongDatabase )
    : mSongDatabase( aSongDatabase )
{
    // fucking code, just for test
    SongDatabase * songDatabase = new SongDatabase( mSongDatabase->getSongSingerOrderList() );
    mSongDatabase = songDatabase;
}

int SonglistPainter::getTableTitleBeginY( QRect const & aRect ) const
{
    return PAGE_PADDING;
}

int SonglistPainter::getTableSubTitleBeginY( QRect const & aRect ) const
{
    return PAGE_PADDING + ( aRect.height() - LR_PAGE_PADDING ) * TABLE_TITLE_RATIO_TO_HEIGHT;
}

int SonglistPainter::getTableBeginY( QRect const & aRect ) const
{
    return getTableTitleBeginY( aRect ) + ( aRect.height() - LR_PAGE_PADDING ) * TABLE_SUBTITLE_RATIO_TO_HEIGHT;
}

void SonglistPainter::makePdf( QString aFileName )
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName( aFileName );

    QPainter painter( &printer );
    painter.setRenderHint( QPainter::Antialiasing, true );
    painter.setRenderHint( QPainter::TextAntialiasing, true );
    painter.setRenderHint( QPainter::HighQualityAntialiasing, true );

    for ( int songBeginIndex = 0; songBeginIndex < mSongDatabase->getSongCount(); songBeginIndex += SONG_COUNT_PER_PAGE )
    {
        drawOnePage( printer, painter, songBeginIndex );

        // qt automacially produce a new page first, so do not need to put this before drawOnePage
        if ( songBeginIndex + SONG_COUNT_PER_PAGE < mSongDatabase->getSongCount() )
        {
            printer.newPage();
        }
    }
}

int SonglistPainter::getHlineBeginY( QPrinter & aPrinter, int aRowIndex ) const
{
    return getTableBeginY( aPrinter.pageRect() ) + ( aPrinter.pageRect().height() - PAGE_PADDING - getTableBeginY( aPrinter.pageRect() ) - TABLE_BORDER ) / TABLE_ROW_COUNT * aRowIndex;
}

int SonglistPainter::getRowHeight( QPrinter & aPrinter ) const // just the height of blanket area, ignore border
{
    return ( aPrinter.pageRect().height() - getTableBeginY( aPrinter.pageRect() ) - PAGE_PADDING - TABLE_BORDER * ( 1 + TABLE_ROW_COUNT ) ) / TABLE_ROW_COUNT;
}

// return double to avoid error accumulation
double SonglistPainter::getColWidth( QPrinter & aPrinter, int aColIndex ) const
{
    return TABLE_EACH_COL_WIDTH_RATIO[aColIndex % COLUMN_TYPE_COUNT] * ( aPrinter.pageRect().width() - LR_PAGE_PADDING - ( TABLE_COL_COUNT + 1 ) * TABLE_BORDER ) / N_SONG_PER_ROW;
}

void SonglistPainter::drawSongText( QPainter & aPainter, QRect const & aRect, QString const & aString, ColumnType aColType )
{
    QFont textFont( QString( "微軟正黑體" ) );
    // textFont.setPixelSize( 20 );
    aPainter.setFont( textFont );
    aPainter.drawText( aRect.adjusted( TABLE_GRID_PADDING, TABLE_GRID_PADDING, -TABLE_GRID_PADDING, -TABLE_GRID_PADDING ), aString );
}

void SonglistPainter::drawOnePage( QPrinter & aPrinter, QPainter & aPainter, int aSongBeginIndex )
{
    // draw title
    const int TABLE_TITLE_BEGIN_Y = getTableTitleBeginY( aPrinter.pageRect() );

    // draw subtitle
    const int TABLE_SUBTITLE_BEGIN_Y = getTableSubTitleBeginY( aPrinter.pageRect() );

    // draw table
    QPen pen( Qt::black, TABLE_BORDER );
    aPainter.setPen( pen );
    for ( int rowIndex = 0; rowIndex < TABLE_ROW_COUNT + 1; ++rowIndex ) // the horizontal line is 1 more than the row count
    {
        // draw horizontal line
        aPainter.drawLine
            (
            PAGE_PADDING,
            getHlineBeginY( aPrinter, rowIndex ),
            aPrinter.pageRect().width() - PAGE_PADDING - TABLE_BORDER,
            getHlineBeginY( aPrinter, rowIndex )
            );

        if ( rowIndex == TABLE_ROW_COUNT )
            break;

        double xPos = PAGE_PADDING; // do not use int to avoid the error accumulation
        for ( int colIndex = 0; colIndex < TABLE_COL_COUNT; ++colIndex )
        {
            // draw vertical line
            aPainter.drawLine( xPos, getHlineBeginY( aPrinter, rowIndex ),
                                    xPos, getHlineBeginY( aPrinter, rowIndex + 1 ) );
            // write the text of song info
            QRect textRect
                (
                xPos + TABLE_BORDER,
                getHlineBeginY( aPrinter, rowIndex ) + TABLE_BORDER,
                getColWidth( aPrinter, colIndex ),
                getRowHeight( aPrinter )
                );
            const int songIndex = aSongBeginIndex + rowIndex * N_SONG_PER_ROW + colIndex / COLUMN_TYPE_COUNT;
            if ( songIndex < mSongDatabase->getSongCount() )
            {
                drawSongText
                    (
                    aPainter,
                    textRect,
                    mSongDatabase->getSong( songIndex ).getInfo( COLUMN_INFO[colIndex % COLUMN_TYPE_COUNT ] ),
                    static_cast<ColumnType>( colIndex % COLUMN_TYPE_COUNT )
                    );
            }

            // increase horizontal delta
            xPos += TABLE_BORDER + getColWidth( aPrinter, colIndex );
        }
        // draw last vertical line
        aPainter.drawLine( xPos, getHlineBeginY( aPrinter, rowIndex ),
                                xPos, getHlineBeginY( aPrinter, rowIndex + 1 ) );
    }
}
