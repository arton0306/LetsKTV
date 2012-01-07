#include "SongEntry.h"

SongEntry::SongEntry
    (
    QString aSinger,
    QString aSongName,
    QString aGender,
    QString aLanguage,
    int aTimeLength,
    QString aFilePath,
    QString aNotes
    )
    : mSinger ( aSinger )
    , mSongName ( aSongName )
    , mGender ( aGender )
    , mLanguage ( aLanguage )
    , mTimeLength ( aTimeLength )
    , mFilePath ( aFilePath )
    , mNotes ( aNotes )
{
}

void SongEntry::setId( int aId )
{
    mId = aId;
}

int SongEntry::getId()
{
    return mId;
}

QString SongEntry::getSinger()
{
    return mSinger;
}

QString SongEntry::getGender()
{
    return mGender;
}

QString SongEntry::getLanguage()
{
    return mLanguage;
}

int SongEntry::getTimeLength()
{
    return mTimeLength;
}

QString SongEntry::getFilePath()
{
    return mFilePath;
}

QString SongEntry::getNotes()
{
    return mNotes;
}

