#include <QFileDialog>
#include <QDir>
#include "debug.h"
#include "SongDbWindow.h"
#include "SongTableModel.h"
#include "Book.h"

SongDbWindow::SongDbWindow(QWidget *parent)
    : QMainWindow(parent)
    , mSongDatabase( NULL )
    , mPreference( QSettings::IniFormat, QSettings::UserScope, "Arton Soft", "Lets KTV")
{
    setupUi(this);
    setupActions();
    setupConnections();
}

SongDbWindow::~SongDbWindow()
{
}

void SongDbWindow::reset()
{
    delete songTableView->selectionModel();
    delete mSongDatabase;
}

QString SongDbWindow::getDefaultFolder( QString aSettingKey ) const
{
    QString prefValue = mPreference.value( aSettingKey ).toString();
    DEBUG() << "pref " << aSettingKey << prefValue;
    return QFileInfo( prefValue ).isDir() ? prefValue : QDir::homePath();
}

QString SongDbWindow::selectSongFolder()
{
    QString folder = QFileDialog::getExistingDirectory
        (
        this,
        tr("Please pick the folder containing the songs."),
        getDefaultFolder( "SongDefaultFolder" )
        );

    if ( !folder.isEmpty() )
    {
        DEBUG() << folder;
        mPreference.setValue( "SongDefaultFolder", folder );

        reset();
        mSongDatabase = new SongDatabase( folder );
        songTableView->setModel( new SongTableModel( mSongDatabase ) );
        songTableView->setSelectionBehavior( QAbstractItemView::SelectRows );
        songTableView->setSelectionMode( QAbstractItemView::SingleSelection );
        songTableView->show();

        emit sgnlSongDatabaseChanged( mSongDatabase );
    }
    else
    {
        DEBUG() << "cancel folder selection";
    }
    return folder;
}

void SongDbWindow::setupActions()
{
    connect( actionSelectFolder, SIGNAL(triggered( bool )), this, SLOT(selectSongFolder()) );
    connect( actionPrintSongList, SIGNAL(triggered( bool )), this, SLOT(writePdfFile()) );
}

void SongDbWindow::setupConnections()
{
    connect( songTableView, SIGNAL(doubleClicked( const QModelIndex & )), this, SLOT( toSong( const QModelIndex & )) );
}

void SongDbWindow::toSong( const QModelIndex & aQModelIndexInSongTable )
{
    // TODO: should use song id instead of row number
    DEBUG() << "double clicked on table model at row: " << aQModelIndexInSongTable.row();
    emit sgnlDoubleClickOneSong( mSongDatabase->getSong( aQModelIndexInSongTable.row() ) );
}

void SongDbWindow::writePdfFile()
{
    if ( mSongDatabase != NULL && !mSongDatabase->isEmpty() )
    {
        QString fileName = QFileDialog::getSaveFileName
            (
            this,
            tr("Please enter the file name."),
            getDefaultFolder( "WritePdfDefaultFolder" ),
            tr("Pdf (*.pdf)")
            );

        if ( !fileName.isEmpty() )
        {
            DEBUG() << "ready to write " << fileName;
            SongBook::Book( mSongDatabase ).makePdf( fileName );
            mPreference.setValue( "WritePdfDefaultFolder", QFileInfo( fileName ).canonicalPath() );
        }
        else
        {
            DEBUG() << "filename invalid";
        }
    }
}
