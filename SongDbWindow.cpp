#include <QFileDialog>
#include <QDir>
#include "debug.h"
#include "SongDbWindow.h"
#include "SongTableModel.h"
#include "SonglistPainter.h"

SongDbWindow::SongDbWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    setupActions();
    setupConnections();
}

SongDbWindow::~SongDbWindow()
{
    delete mSonglistPainter;
}

QString SongDbWindow::selectSongFolder()
{
    QString folder = QFileDialog::getExistingDirectory
        (
        this,
        tr("Please pick the folder containing the songs."),
        QDir::homePath() // TODO: use preference folder
        );

    if ( !folder.isEmpty() )
    {
        DEBUG() << folder;
        debug::dumpSongFolder( folder );

        // TODO: haven't handle the deletion of the SongDatabase
        mSongDatabase = new SongDatabase( folder );
        mSonglistPainter = new SonglistPainter( mSongDatabase );

        // TODO: haven't handle the deletion of the SongTableModel
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
            QDir::homePath(), // TODO: use preference folder
            tr("Pdf (*.pdf)")
            );

        if ( !fileName.isEmpty() )
        {
            DEBUG() << "ready to write " << fileName;
            mSonglistPainter->makePdf( fileName );
        }
        else
        {
            DEBUG() << "filename invalid";
        }
    }
}
