#include <QStringList>
#include "SongEntry.h"

SongEntry::SongEntry
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

SongEntry::SongEntry( QString aFileName )
{
    QStringList fileNameCols = aFileName.split( QChar( '-' ) );
    mSinger = fileNameCols[ SINGER ];
    mSongName= fileNameCols[ SONGNAME ];
    mGender = fileNameCols[ GENDER ];
    mLanguage = fileNameCols[ LANGUAGE ];
    mTimeLength = TIME_UNKNOWN;
}

void SongEntry::setId( int aId )
{
    mId = aId;
}

void SongEntry::setTimeLength( int aSeconds )
{
    mTimeLength = aSeconds;
}

void SongEntry::setFilePath( QString aFilePath )
{
    mFilePath = aFilePath;
}

int SongEntry::getId() const
{
    return mId;
}

QString SongEntry::getIdText() const
{
    return QString::number( mId );
}

QString SongEntry::getSongName() const
{
    return mSongName;
}

QString SongEntry::getSinger() const
{
    return mSinger;
}

QString SongEntry::getGender() const
{
    return mGender;
}

QString SongEntry::getLanguage() const
{
    return mLanguage;
}

int SongEntry::getTimeLength() const
{
    return mTimeLength;
}

QString SongEntry::getTimeLengthText() const
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

QString SongEntry::getFilePath() const
{
    return mFilePath;
}

QString SongEntry::getNotes() const
{
    return mNotes;
}

