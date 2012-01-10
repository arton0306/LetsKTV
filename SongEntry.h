#ifndef SONGENTRY_H
#define SONGENTRY_H

#include <QString>

class SongEntry
{
public:
    /*---------------------------------------------
                       Constants
    ---------------------------------------------*/
    static const int TIME_UNKNOWN = -1;

    /*---------------------------------------------
                         Types
    ---------------------------------------------*/
    enum SongFileColumnType
    {
        // the order is according to the specail file name format
        LANGUAGE,
        GENDER,
        SINGER,
        SONGNAME
    };

    enum SongFileExtraInfo
    {
        FILEPATH,
        NOTES
    };

    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/
    SongEntry
        (
        QString mSinger,
        QString mSongName,
        QString mGender,
        QString mLanguage,
        QString mFilePath
        );

    SongEntry( QString aFileName );

    void setId( int aId );
    void setTimeLength( int aSeconds );
    void setFilePath( QString aFilePath );
    int getId() const;
    QString getIdText() const;
    QString getSongName() const;
    QString getSinger() const;
    QString getGender() const;
    QString getLanguage() const;
    int getTimeLength() const;
    QString getTimeLengthText() const;
    QString getFilePath() const;
    QString getNotes() const;

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
