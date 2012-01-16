#include <QPrinter>
#include <QPainter>
#include <QPixmap>
#include "SonglistPainter.h"

// page padding
const int PAGE_PADDING = 18; // pixel count ( 4 border )
const int LR_PAGE_PADDING = PAGE_PADDING * 2; // sum of left and right page padding

// the ratio of title, subtile, and table
const double TABLE_TITLE_RATIO_TO_HEIGHT    =  3.5 / 20.0;
const double TABLE_SUBTITLE_RATIO_TO_HEIGHT =  1.9 / 20.0;
const double TABLE_RATIO_TO_HEIGHT          = 14.6 / 20.0;

// column width ratio
const int COLUMN_TYPE_COUNT = 3;
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

SonglistPainter::SonglistPainter( SongDatabase const * aSongDatabase )
    : mSongDatabase( aSongDatabase )
{
    makePdf( QString() );
}

int SonglistPainter::getTableTitleBeginY( QRect const & aRect ) const
{
    return PAGE_PADDING;
}

int SonglistPainter::getTableSubTitleBeginY( QRect const & aRect ) const
{
    return PAGE_PADDING + ( aRect.height() - 2 * PAGE_PADDING ) * TABLE_TITLE_RATIO_TO_HEIGHT;
}

int SonglistPainter::getTableBeginY( QRect const & aRect ) const
{
    return getTableTitleBeginY( aRect ) + ( aRect.height() - 2 * PAGE_PADDING ) * TABLE_SUBTITLE_RATIO_TO_HEIGHT;
}

void SonglistPainter::makePdf( QString aFileName )
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("out.pdf");
    printer.newPage();

    QPainter printerPainter(&printer);

    QPixmap paperPixmap( printer.pageRect().size() );
    paperPixmap.fill(); // default with White
    QPainter pixmapPainter( &paperPixmap );
    pixmapPainter.setRenderHint( QPainter::Antialiasing, true );

    // draw title
    const int TABLE_TITLE_BEGIN_Y = getTableTitleBeginY( printer.pageRect() );

    // draw subtitle
    const int TABLE_SUBTITLE_BEGIN_Y = getTableSubTitleBeginY( printer.pageRect() );

    // draw table
    QPen pen( Qt::black, TABLE_BORDER );
    pixmapPainter.setPen( pen );
    const int TABLE_BEGIN_Y = getTableBeginY( printer.pageRect() );
    for ( int rowIndex = 0; rowIndex < TABLE_ROW_COUNT + 1; ++rowIndex ) // the horizontal line is 1 more than the row count
    {
        pixmapPainter.drawLine
            (
            PAGE_PADDING,
            TABLE_BEGIN_Y + ( printer.pageRect().height() - PAGE_PADDING - TABLE_BEGIN_Y - TABLE_BORDER ) / TABLE_ROW_COUNT * rowIndex,
            printer.pageRect().width() - PAGE_PADDING - TABLE_BORDER,
            TABLE_BEGIN_Y + ( printer.pageRect().height() - PAGE_PADDING - TABLE_BEGIN_Y - TABLE_BORDER ) / TABLE_ROW_COUNT * rowIndex
            );

        if ( rowIndex == TABLE_ROW_COUNT )
            break;

        double xPos = PAGE_PADDING; // do not use int to avoid the error accumulation
        for ( int colIndex = 0; colIndex < TABLE_COL_COUNT; ++colIndex )
        {
            pixmapPainter.drawLine
                (
                xPos,
                TABLE_BEGIN_Y + ( printer.pageRect().height() - PAGE_PADDING - TABLE_BEGIN_Y - TABLE_BORDER ) / TABLE_ROW_COUNT * rowIndex,
                xPos,
                TABLE_BEGIN_Y + ( printer.pageRect().height() - PAGE_PADDING - TABLE_BEGIN_Y - TABLE_BORDER ) / TABLE_ROW_COUNT * ( rowIndex + 1 )
                );
            xPos += TABLE_BORDER + ( TABLE_EACH_COL_WIDTH_RATIO[colIndex % COLUMN_TYPE_COUNT] * ( printer.pageRect().width() - LR_PAGE_PADDING - ( TABLE_COL_COUNT + 1 ) * TABLE_BORDER ) / N_SONG_PER_ROW );
        }
        pixmapPainter.drawLine
            (
            xPos,
            TABLE_BEGIN_Y + ( printer.pageRect().height() - PAGE_PADDING - TABLE_BEGIN_Y - TABLE_BORDER ) / TABLE_ROW_COUNT * rowIndex,
            xPos,
            TABLE_BEGIN_Y + ( printer.pageRect().height() - PAGE_PADDING - TABLE_BEGIN_Y - TABLE_BORDER ) / TABLE_ROW_COUNT * ( rowIndex + 1 )
            );
    }


    printerPainter.drawPixmap( 0, 0, paperPixmap );
}
