#include <QPrinter>
#include <QString>
#include <algorithm>
#include "Song.h"
#include "Book.h"
#include "debug.h"
#include "PageLayoutInfo.hpp"
#include "WordManager.h"

using namespace std;
using namespace SongBook;

const int SONG_COUNT_PER_PAGE = TABLE_ROW_COUNT * N_SONG_PER_ROW;
const int SMALL_CATEGORY_UPPER_BOUND = SONG_COUNT_PER_PAGE / 2;

Book::Book( SongDatabase const * aSongDatabase )
{
    classifyAllSongs( aSongDatabase );
    sortSongsInCategory();
    produceMergeCategory();
    produceEachPage();
}

/**Function****************************************************************
   Synopsis     [ classify all the song in database into mSongCategory ]
   Description  [ input: song database
                  output: none ]
   SideEffects  [ mSongCategory ]
**************************************************************************/
void Book::classifyAllSongs( SongDatabase const * aSongDatabase )
{
    for ( int songIndex = 0; songIndex < aSongDatabase->getSongCount(); ++songIndex )
    {
        Song const & song = aSongDatabase->getSong( songIndex );
        mSongCategory[song.getLanguageType()][song.getGenderType()].push_back( song );
    }
}

/**Function****************************************************************
   Synopsis     [ sort the songs in each category
                  solo singer or group with singer order ( group only has one name )
                  multi singer with songname order ]
   Description  [ ]
   SideEffects  [ mSongCategory ]
**************************************************************************/
void Book::sortSongsInCategory()
{
    for ( int langType = 0; langType < Song::LANGUAGE_COUNT; ++langType )
    {
        for ( int genderType = 0; genderType < Song::GENDER_COUNT; ++genderType )
        {
            vector<Song> & sc = mSongCategory[langType][genderType]; // sc is "s"ong"C"ategory
            switch ( genderType )
            {
                case Song::GENDER_MALE:   // empty purposely
                case Song::GENDER_FEMALE: // empty purposely
                case Song::GENDER_GROUP:  std::sort( sc.begin(), sc.end(), compareSinger ); break;
                case Song::GENDER_CHORUS: std::sort( sc.begin(), sc.end(), compareSongName ); break;
                case Song::GENDER_OTHERS: break;
            }
        }
    }
}

/**Function****************************************************************
   Synopsis     [ for each category: if a category has few songs, move
                  these songs into mMergeCategory ]
   Description  [ ]
   SideEffects  [ mSongCategory, mMergeCategory ]
**************************************************************************/
void Book::produceMergeCategory()
{
    for ( int langType = 0; langType < Song::LANGUAGE_COUNT; ++langType )
    {
        for ( int genderType = 0; genderType < Song::GENDER_COUNT; ++genderType )
        {
            vector<Song> & sc = mSongCategory[langType][genderType]; // sc is "s"ong"C"ategory
            if ( sc.size() < SMALL_CATEGORY_UPPER_BOUND )
            {
                for ( int songIndex = 0; songIndex < sc.size(); ++songIndex )
                {
                    mMergeCategory.push_back( sc[songIndex] );
                }
                sc.clear();
            }
        }
    }
}

/**Function****************************************************************
   Synopsis     [ produce each page by mSongCategory and mMergeCategory ]
   Description  [ ]
   SideEffects  [ mSongbookPage ]
**************************************************************************/
void Book::produceEachPage()
{
    for ( int langType = 0; langType < Song::LANGUAGE_COUNT; ++langType )
    {
        for ( int genderType = 0; genderType < Song::GENDER_COUNT; ++genderType )
        {
            vector<Song> & sc = mSongCategory[langType][genderType]; // sc is "s"ong"C"ategory
            if ( !sc.empty() )
            {
                for ( int pageIndex = 0; pageIndex * SONG_COUNT_PER_PAGE < sc.size(); ++pageIndex )
                {
                    Page aPage;
                    aPage.setTitle( getTitleTextToPrint( (Song::LanguageType)langType, (Song::GenderType)genderType ) );
                    for ( int songIndex = pageIndex * SONG_COUNT_PER_PAGE; songIndex < ( pageIndex + 1 ) * SONG_COUNT_PER_PAGE && songIndex < sc.size(); ++songIndex )
                    {
                        aPage.addSong( sc[songIndex] );
                    }
                    aPage.produceSubtitle();
                    mSongbookPage.push_back( aPage );
                }
            }
        }
    }
    if ( !mMergeCategory.empty() )
    {
        for ( int pageIndex = 0; pageIndex * SONG_COUNT_PER_PAGE < mMergeCategory.size(); ++pageIndex )
        {
            Page aPage;
            aPage.setTitle( QString("其它") );
            for ( int songIndex = pageIndex * SONG_COUNT_PER_PAGE; songIndex < ( pageIndex + 1 ) * SONG_COUNT_PER_PAGE && songIndex < mMergeCategory.size(); ++songIndex )
            {
                aPage.addSong( mMergeCategory[songIndex] );
            }
            mSongbookPage.push_back( aPage );
        }
    }
}

QString Book::getTitleTextToPrint( Song::LanguageType aLanguageType, Song::GenderType aGenderType ) const
{
    QString genderText, languageText;
    switch ( aGenderType )
    {
        case Song::GENDER_MALE:    genderText = QString("男歌手"); break;
        case Song::GENDER_FEMALE:  genderText = QString("女歌手"); break;
        case Song::GENDER_GROUP:   genderText = QString("團體");   break;
        case Song::GENDER_CHORUS:  genderText = QString("合唱");   break;
        default:             genderText = QString("其它");   break;
    }
    switch ( aLanguageType )
    {
        case Song::LANGUAGE_MANDARIN: languageText = QString("國語歌曲"); break;
        case Song::LANGUAGE_MINNAN:   languageText = QString("台語歌曲"); break;
        case Song::LANGUAGE_ENGLISH:  languageText = QString("英語歌曲"); break;
        case Song::LANGUAGE_JAPANESE: languageText = QString("日語歌曲"); break;
        default:                      languageText = QString("其它語言"); break;
    }
    return languageText + QString(" - ") + genderText;
}

void Book::makePdf( QString aFileName )
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName( aFileName );

    // remember that we must create painter here.
    // It can not be created in the PagePrinter, or the result will be wrong - just produce the last page.
    QPainter painter( &printer );
    painter.setRenderHint( QPainter::Antialiasing, true );
    painter.setRenderHint( QPainter::TextAntialiasing, true );
    painter.setRenderHint( QPainter::HighQualityAntialiasing, true );

    for ( int pageIndex = 0; pageIndex < mSongbookPage.size(); ++pageIndex )
    {
        mSongbookPage[pageIndex].print( printer, painter );
        if ( pageIndex != mSongbookPage.size() - 1 )
        {
            // qt automacially produce a new page first, so do not need to put this before drawOnePage
            printer.newPage();
        }
    }
}

