#ifndef SONGLISTPAINTER_H
#define SONGLISTPAINTER_H

#include <QPixmap>
#include "Song.h"
#include "SongDatabase.h"
#include "SonglistPage.h"
#include <vector>

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
                        Functions
    ---------------------------------------------*/
    QString getTitleTextToPrint( Song::LanguageType aLanguageType, Song::GenderType aGenderType ) const;

    /*---------------------------------------------
                       Variables
    ---------------------------------------------*/
    std::vector<Song> mSongList;
    std::vector<SonglistPage> mSonglistPage;
};

#endif // SONGLISTPAINTER_H
