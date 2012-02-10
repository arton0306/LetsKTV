#include <QPrinter>
#include <QString>
#include "Song.h"
#include "Book.h"
#include "debug.h"

using namespace std;
using namespace SongBook;

Book::Book( SongDatabase const * aSongDatabase )
{
    vector<Song> totalSong = aSongDatabase->getSongSingerOrderList();
    vector<Song> songCategory[Song::LANGUAGE_COUNT][Song::GENDER_COUNT];
    vector<Song> mergeCategory; // some normal category has few songs, so merge them into one category
    for ( vector<Song>::iterator iter = totalSong.begin(); iter != totalSong.end(); ++iter )
    {
        songCategory[iter->getLanguageType()][iter->getGenderType()].push_back( *iter );
        if ( iter->getLanguageType() > Song::LANGUAGE_MINNAN )
        {
            mergeCategory.push_back( *iter );
        }
    }

    for ( int langType = 0; langType <= Song::LANGUAGE_MINNAN; ++langType )
    {
        for ( int genderType = 0; genderType < Song::GENDER_COUNT; ++genderType )
        {
            vector<Song> & sc = songCategory[langType][genderType]; // sc is "s"ong"C"ategory
            if ( !sc.empty() )
            {
                for ( int pageIndex = 0; pageIndex * 36 < sc.size(); ++pageIndex )
                {
                    Page aPage;
                    aPage.setTitle( getTitleTextToPrint( (Song::LanguageType)langType, (Song::GenderType)genderType ) );
                    for ( int songIndex = pageIndex * 36; songIndex < ( pageIndex + 1 ) * 36 && songIndex < sc.size(); ++songIndex )
                    {
                        aPage.addSong( sc[songIndex] );
                    }
                    mSongbookPage.push_back( aPage );
                }
            }
        }
    }
    if ( !mergeCategory.empty() )
    {
        for ( int pageIndex = 0; pageIndex * 36 < mergeCategory.size(); ++pageIndex )
        {
            Page aPage;
            aPage.setTitle( QString("其它") );
            for ( int songIndex = pageIndex * 36; songIndex < ( pageIndex + 1 ) * 36 && songIndex < mergeCategory.size(); ++songIndex )
            {
                aPage.addSong( mergeCategory[songIndex] );
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
        default:                      languageText = QString("其它語言"); break;
    }
    return languageText + QString(" - ") + genderText;
}

void Book::makePdf( QString aFileName )
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName( aFileName );

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

