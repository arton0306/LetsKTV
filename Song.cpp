#include <QStringList>
#include "Song.h"
#include "debug.h"
#include "WordManager.h"

/*
QMap<QString, Song::GenderType> Song::sGenderOrder = QMap<QString, GenderType>();
QMap<QString, Song::LanguageType> Song::sLanguageOrder = QMap<QString, LanguageType>();
*/

Song::Song
    (
    QString aSinger,
    QString aSongName,
    QString aGender,
    QString aLanguage,
    QString aFilePath
    )
    : mSinger( aSinger )
    , mSongName( aSongName )
    , mGender( aGender )
    , mGenderType( lookupGenderType( aGender ) )
    , mLanguage( aLanguage )
    , mLanguageType( lookupLanguageType( aLanguage ) )
    , mFilePath( aFilePath )
{
    mTimeLength = TIME_UNKNOWN;
}

Song::Song( QString aFileName )
{
    QStringList fileNameCols = aFileName.split( QChar( '-' ) );
    mSinger = fileNameCols[ SINGER ];
    mSongName = fileNameCols[ SONGNAME ];
    mGender = fileNameCols[ GENDER ];
    mGenderType = lookupGenderType( mGender );
    mLanguage = fileNameCols[ LANGUAGE ];
    mLanguageType = lookupLanguageType( mLanguage );
    mTimeLength = TIME_UNKNOWN;
}

Song::GenderType Song::lookupGenderType( QString aGenderText ) const
{
    if ( aGenderText == QString("男") ) return GENDER_MALE;
    if ( aGenderText == QString("女") ) return GENDER_FEMALE;
    if ( aGenderText == QString("合") ) return GENDER_CHORUS;
    if ( aGenderText == QString("團") ) return GENDER_GROUP;
    else return GENDER_OTHERS;
}

Song::GenderType Song::getGenderType() const
{
    return mGenderType;
}

Song::LanguageType Song::lookupLanguageType( QString aLanguageText ) const
{
    if ( aLanguageText == QString("國") ) return LANGUAGE_MANDARIN;
    if ( aLanguageText == QString("台") ) return LANGUAGE_MINNAN;
    if ( aLanguageText == QString("英") ) return LANGUAGE_ENGLISH;
    if ( aLanguageText == QString("日") ) return LANGUAGE_JAPANESE;
    else return LANGUAGE_OTHERS;
}

Song::LanguageType Song::getLanguageType() const
{
    return mLanguageType;
}

void Song::setId( int aId )
{
    mId = aId;
}

void Song::setTimeLength( int aSeconds )
{
    mTimeLength = aSeconds;
}

void Song::setFilePath( QString aFilePath )
{
    mFilePath = aFilePath;
}

int Song::getId() const
{
    return mId;
}

QString Song::getIdText() const
{
    return QString::number( mId );
}

QString Song::getSongName() const
{
    return mSongName;
}

QString Song::getSinger() const
{
    return mSinger;
}

QString Song::getGender() const
{
    return mGender;
}

QString Song::getLanguage() const
{
    return mLanguage;
}

int Song::getTimeLength() const
{
    return mTimeLength;
}

QString Song::getTimeLengthText() const
{
    if ( TIME_UNKNOWN == mTimeLength )
    {
        return QString( "未知" );
    }
    else
    {
        return QString::number( mTimeLength );
    }
}

QString Song::getFilePath() const
{
    return mFilePath;
}

QString Song::getNotes() const
{
    return mNotes;
}

QString Song::getInfo( SongInfoType aInfoType ) const
{
    switch ( aInfoType )
    {
        case LANGUAGE: return getLanguage();
        case GENDER:   return getGender();
        case SINGER:   return getSinger();
        case SONGNAME: return getSongName();
        case FILEPATH: return getFilePath();
        case NOTES:    return getNotes();
        case SONGID:   return getIdText();
        default:
            DEBUG() << "getInfo error";
            return QString();
    }
}

bool Song::compareSongName( Song const & aSong ) const
{
    int lengthCompare = WordManager::getInstance()->compare( WordManager::MEANING_LENGTH_ORDER, mSongName, aSong.mSongName );
    if ( lengthCompare < 0 ) return true;
    if ( lengthCompare > 0 ) return false;
    return WordManager::getInstance()->compare( WordManager::STROKE_ORDER, mSongName, aSong.mSongName ) <= 0;
}

bool Song::compareSinger( Song const & aSong ) const
{
    return WordManager::getInstance()->compare( WordManager::ZUIN_ORDER, mSinger, aSong.mSinger ) <= 0;
}

/*
int Song::getSingerOrderNumber() const
{
}
*/

bool compareSongName( Song const & aX, Song const & aY )
{
    return aX.compareSongName( aY );
}

bool compareSinger( Song const & aX, Song const & aY )
{
    return aX.compareSinger( aY );
}
