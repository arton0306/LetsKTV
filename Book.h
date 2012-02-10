#ifndef SONGLISTPAINTER_H
#define SONGLISTPAINTER_H

#include <QPixmap>
#include "Song.h"
#include "SongDatabase.h"
#include "Page.h"
#include <vector>

namespace SongBook
{
    class Book
    {
    public:
        /*---------------------------------------------
                            Functions
        ---------------------------------------------*/
        Book( SongDatabase const * aSongDatabase = 0 ); // = 0 for temp
        void makePdf( QString aFileName );

    private:
        /*---------------------------------------------
                            Functions
        ---------------------------------------------*/
        QString getTitleTextToPrint( Song::LanguageType aLanguageType, Song::GenderType aGenderType ) const;

        /*---------------------------------------------
                           Variables
        ---------------------------------------------*/
        std::vector<Song> mSongList;
        std::vector<Page> mSongbookPage;
    };
}

#endif // SONGLISTPAINTER_H
