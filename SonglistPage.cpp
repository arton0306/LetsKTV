#include "SonglistPage.h"
#include <QPainter>
#include <QPixmap>
#include "debug.h"
#include <QDate>
#include "WordManager.h"

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
const double TABLE_BORDER = 1;  // pixel count
const int TABLE_ROW_COUNT = 18;
const int N_SONG_PER_ROW = 2;
const int TABLE_COL_COUNT = COLUMN_TYPE_COUNT * N_SONG_PER_ROW;
const int TABLE_GRID_PADDING = 3;
const int SONG_COUNT_PER_PAGE = N_SONG_PER_ROW * TABLE_ROW_COUNT;

SonglistPage::SonglistPage()
{
}

SonglistPage::SonglistPage( QString aTitle, QString aSubTitle )
    : mTitle( aTitle )
    , mSubTitle( aSubTitle )
{
}

int SonglistPage::getTableTitleBeginY( QRect const & aRect ) const
{
    return PAGE_PADDING;
}

int SonglistPage::getTableSubTitleBeginY( QRect const & aRect ) const
{
    return PAGE_PADDING + ( aRect.height() - LR_PAGE_PADDING ) * TABLE_TITLE_RATIO_TO_HEIGHT;
}

int SonglistPage::getTableBeginY( QRect const & aRect ) const
{
    return getTableTitleBeginY( aRect ) + ( aRect.height() - LR_PAGE_PADDING ) * TABLE_SUBTITLE_RATIO_TO_HEIGHT;
}

void SonglistPage::addSong( Song const & aSong )
{
    mSonglist.push_back( aSong );
}

Song const & SonglistPage::getSong( int aIndex ) const
{
    return mSonglist[aIndex];
}

int SonglistPage::getSongCount() const
{
    return mSonglist.size();
}

void SonglistPage::setTitle( QString aTitle )
{
    mTitle = aTitle;
}

QString SonglistPage::getTitle() const
{
    return mTitle;
}

void SonglistPage::setSubTitle( QString aSubTitle )
{
    mSubTitle = aSubTitle;
}

QString SonglistPage::getSubTitle() const
{
    return mSubTitle;
}

double SonglistPage::getHlineBeginY( QPrinter & aPrinter, int aRowIndex ) const
{
    return getTableBeginY( aPrinter.pageRect() ) + ( aPrinter.pageRect().height() - PAGE_PADDING - getTableBeginY( aPrinter.pageRect() ) - TABLE_BORDER ) / static_cast<double>(TABLE_ROW_COUNT) * aRowIndex;
}

double SonglistPage::getRowHeight( QPrinter & aPrinter ) const // just the height of blanket area, ignore border
{
    return ( aPrinter.pageRect().height() - getTableBeginY( aPrinter.pageRect() ) - PAGE_PADDING - TABLE_BORDER * ( 1 + TABLE_ROW_COUNT ) ) / static_cast<double>(TABLE_ROW_COUNT);
}

// return double to avoid error accumulation
double SonglistPage::getColWidth( QPrinter & aPrinter, int aColIndex ) const
{
    return TABLE_EACH_COL_WIDTH_RATIO[aColIndex % COLUMN_TYPE_COUNT] * ( aPrinter.pageRect().width() - LR_PAGE_PADDING - ( TABLE_COL_COUNT + 1 ) * TABLE_BORDER ) / static_cast<double>(N_SONG_PER_ROW);
}

void SonglistPage::drawSinger( QPainter & aPainter, QRect const & aRect, QString const & aString ) const
{
    const int gridStyleCount = 4;
    static int rowCount[gridStyleCount] = { 1, 2, 2, 3 };
    static int colCount[gridStyleCount] = { 1, 1, 2, 2 };
    QStringList singers = aString.split("&");

    // determine how to cut the origin grid
    int style = gridStyleCount - 1; // in case there are too many singer, the forloop below won't set style
    for ( int i = 0; i < gridStyleCount; ++i )
    {
        if ( rowCount[i] * colCount[i] >= singers.count() )
        {
            style = i;
            break;
        }
    }

    // put each singers to each small grid
    double newWidth = double(aRect.width()) / colCount[style]; // use double to avoid minor error
    double newHeight = double(aRect.height()) / rowCount[style];
    for ( int r = 0; r < rowCount[style]; ++r )
    {
        int newY = aRect.y() + newHeight * r;
        for ( int c = 0; c < colCount[style]; ++c )
        {
            int singerIndex = r * colCount[style] + c;
            if ( singerIndex >= singers.count() ) return;
            QRect finalRect( QPoint( aRect.x() + newWidth * c, newY ), QSize( newWidth, newHeight ) );
            QFont textFont( QString( "微軟正黑體" ) );
            textFont.setPixelSize( estimatedFontSize( finalRect, singers[singerIndex] ) );
            aPainter.setFont( textFont );
            aPainter.drawText( finalRect, Qt::AlignCenter | Qt::TextWordWrap, singers[singerIndex] );
        }
    }
}

double SonglistPage::estimatedFontSize( QRect const & aRect, QString const & aString ) const
{
    const double ratio[] = { 0.7, 0.6, 0.5, 0.4, 0.35, 0.3 };
    double result = 0;
    for ( int i = 0; i < sizeof( ratio ) / sizeof( ratio[0] ); ++i )
    {
        result = ratio[i] * aRect.height();
        if ( result * WordManager::getWordWidthCount( aString ) < aRect.width() )
        {
            break;
        }
    }
    return result;
}

void SonglistPage::drawSongText( QPainter & aPainter, QRect const & aRect, QString const & aString, ColumnType aColType ) const
{
    QFont textFont( QString( "微軟正黑體" ) );
    textFont.setPixelSize( estimatedFontSize( aRect, aString ) );
    aPainter.setFont( textFont );

    QRect paddingRect = aRect.adjusted( TABLE_GRID_PADDING, TABLE_GRID_PADDING, -TABLE_GRID_PADDING, -TABLE_GRID_PADDING );
    switch ( aColType )
    {
        case SONGID:
            aPainter.fillRect( aRect, QColor( 128, 128, 255, 255 ) );
            aPainter.drawText( paddingRect, Qt::AlignCenter, aString );
            break;
        case SONGTITLE:
            aPainter.drawText( paddingRect, Qt::AlignVCenter | Qt::TextWordWrap, aString );
            break;
        case SINGER:
            drawSinger( aPainter, paddingRect, aString );
            break;
        default:
            qCritical() << "ColType not exsits!";
            break;
    }
}

void SonglistPage::print( QPrinter & aPrinter, QPainter & aPainter ) const
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
            const int songIndex = rowIndex * N_SONG_PER_ROW + colIndex / COLUMN_TYPE_COUNT;
            if ( songIndex < mSonglist.size() )
            {
                drawSongText
                    (
                    aPainter,
                    textRect,
                    mSonglist[songIndex].getInfo( COLUMN_INFO[colIndex % COLUMN_TYPE_COUNT ] ),
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
