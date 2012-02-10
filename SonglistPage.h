#ifndef SONGLISTPAGE_H
#define SONGLISTPAGE_H

#include <vector>
#include <QString>
#include <QPrinter>
#include <QPainter>
#include "Song.h"

class SonglistPage
{
public:
    SonglistPage();
    SonglistPage( QString aTitle, QString aSubTitle );
    void addSong( Song const & aSong );
    Song const & getSong( int aIndex ) const;
    int getSongCount() const;
    void setTitle( QString aTitle );
    QString getTitle() const;
    void setSubTitle( QString aSubTitle );
    QString getSubTitle() const;
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
    QString mTitle;
    QString mSubTitle;
    std::vector<Song> mSonglist; // the songs which will be printed on a page
};

#endif // SONGLISTPAGE_H
