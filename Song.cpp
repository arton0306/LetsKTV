#include <QStringList>
#include "Song.h"

Song::Song
    (
    QString aSinger,
    QString aSongName,
    QString aGender,
    QString aLanguage,
    QString aFilePath
    )
    : mSinger ( aSinger )
    , mSongName ( aSongName )
    , mGender ( aGender )
    , mLanguage ( aLanguage )
    , mFilePath ( aFilePath )
{
    mTimeLength = TIME_UNKNOWN;
}

Song::Song( QString aFileName )
{
    QStringList fileNameCols = aFileName.split( QChar( '-' ) );
    mSinger = fileNameCols[ SINGER ];
    mSongName= fileNameCols[ SONGNAME ];
    mGender = fileNameCols[ GENDER ];
    mLanguage = fileNameCols[ LANGUAGE ];
    mTimeLength = TIME_UNKNOWN;
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
        return QString( "¥¼ª¾" );
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

