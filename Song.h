#ifndef SONG_H
#define SONG_H

#include <QString>
#include <QMap>

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

    enum GenderType
    {
        // the order will be used to sort
        GENDER_MALE,
        GENDER_FEMALE,
        GENDER_GROUP,
        GENDER_CHORUS,
        GENDER_OTHERS,

        GENDER_COUNT
    };

    enum LanguageType
    {
        // the order will be used to sort
        LANGUAGE_MANDARIN,
        LANGUAGE_MINNAN,
        LANGUAGE_ENGLISH,
        LANGUAGE_JAPANESE,
        LANGUAGE_OTHERS,

        LANGUAGE_COUNT
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
    GenderType getGenderType() const;
    QString getLanguage() const;
    LanguageType getLanguageType() const;
    int getTimeLength() const;
    QString getTimeLengthText() const;
    QString getFilePath() const;
    QString getNotes() const;
    QString getInfo( SongInfoType aInfoType ) const;
    bool compareSongName( Song const & ) const;
    bool compareSinger( Song const & aSong ) const;

private:
    GenderType lookupGenderType( QString aGenderText ) const;
    LanguageType lookupLanguageType( QString aLanguageText ) const;
    // static QMap<QString, GenderType> sGenderOrder;
    // static QMap<QString, LanguageType> sLanguageOrder;
    int mId;
    QString mSinger;
    QString mSongName;
    QString mGender;
    GenderType mGenderType;
    QString mLanguage;
    LanguageType mLanguageType;
    int mTimeLength; // in seconds
    QString mFilePath;
    QString mNotes;
};

bool compareSongName( Song const & aX, Song const & aY );
bool compareSinger( Song const & aX, Song const & aY );

#endif // SONG_H
