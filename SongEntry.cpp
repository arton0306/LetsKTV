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
}

void SongEntry::setId( int aId )
{
    mId = aId;
}

void SongEntry::setTimeLength( int a_scnds )
{
    mTimeLength = a_scnds;
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

