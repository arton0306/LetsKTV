#ifndef SONGENTRY_H
#define SONGENTRY_H

#include <QString>

class SongEntry
{
public:
    SongEntry
        (
        QString mSinger = QString(),
        QString mSongName = QString(),
        QString mGender = QString(),
        QString mLanguage = QString(),
        int mTimeLength = 0,
        QString mFilePath = QString(),
        QString mNotes = QString()
        );

    void setId( int aId );
    int getId();
    QString getSinger();
    QString getGender();
    QString getLanguage();
    int getTimeLength();
    QString getFilePath();
    QString getNotes();

private:
    int mId;
    QString mSinger;
    QString mSongName;
    QString mGender;
    QString mLanguage;
    int mTimeLength; // in seconds
    QString mFilePath;
    QString mNotes;
};

#endif // SONGENTRY_H
