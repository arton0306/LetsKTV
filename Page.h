#ifndef PAGETEXT_H
#define PAGETEXT_H

#include <vector>
#include <QPrinter>
#include <QPainter>
#include <QString>
#include "Song.h"

namespace SongBook
{
    class Page
    {
    public:
        /*---------------------------------------------
                            Function
        ---------------------------------------------*/
        Page();
        void addSong( Song const & aSong );
        Song const & getSong( int aIndex ) const;
        int getSongCount() const;
        void setTitle( QString aTitle );
        QString getTitle() const;
        void produceSubtitle();
        QString getSubTitle() const;
        void print( QPrinter & aPrinter, QPainter & aPainter ) const;

    private:
        /*---------------------------------------------
                            Function
        ---------------------------------------------*/
        bool isZuinHintNeeded() const;

        /*---------------------------------------------
                            Variable
        ---------------------------------------------*/
        QString mTitle;              // plain text
        QString mSubTitle;           // rich text
        std::vector<Song> mSonglist; // the songs which will be printed on a page
    };
}

#endif // PAGETEXT_H
