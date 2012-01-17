#ifndef SONG_H
#define SONG_H

#include <QString>

class Song
{
public:
    /*---------------------------------------------
                       Constants
    ---------------------------------------------*/
    static const int TIME_UNKNOWN = -1;

    /*---------------------------------------------
                         Types
    ---------------------------------------------*/
    enum SongInfoType
    {
        // the order is according to the specail file name format
        LANGUAGE,
        GENDER,
        SINGER,
        SONGNAME,

        // ExtraInfo
        FILEPATH,
        SONGID,
        NOTES
    };

    /*---------------------------------------------
                       Functions
    ---------------------------------------------*/
    Song
        (
        QString mSinger,
        QString mSongName,
        QString mGender,
        QString mLanguage,
        QString mFilePath
        );

    Song( QString aFileName );

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
    QString getInfo( SongInfoType aInfoType ) const;

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

#endif // SONG_H
