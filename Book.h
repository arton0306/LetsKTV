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
        void classifyAllSongs( SongDatabase const * aSongDatabase );
        void sortSongsInCategory();
        void produceMergeCategory();
        void produceEachPage();
        QString getTitleTextToPrint( Song::LanguageType aLanguageType, Song::GenderType aGenderType ) const;
        QString getSubTitleRichTextToPrint( Page const & aPage, Song::LanguageType aLanguageType, Song::GenderType aGenderType ) const;

        /*---------------------------------------------
                           Variables
        ---------------------------------------------*/
        std::vector<Song> mSongCategory[Song::LANGUAGE_COUNT][Song::GENDER_COUNT];
        std::vector<Song> mMergeCategory; // some normal category has few songs, so merge them into one category
        std::vector<Page> mSongbookPage;
    };
}

#endif // SONGLISTPAINTER_H
