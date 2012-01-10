#include <QFileDialog>
#include <QDir>
#include "debug.h"
#include "SongDbWindow.h"
#include "SongTableModel.h"

SongDbWindow::SongDbWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    setupActions();
}

SongDbWindow::~SongDbWindow()
{
}

QString SongDbWindow::selectSongFolder()
{
    QString folder = QFileDialog::getExistingDirectory
        (
        this,
        tr("Please pick the folder containing the songs."),
        QDir::homePath() // TODO: use preference folder
        );
    mSongFolderPath = folder;
    qDebug() << mSongFolderPath;
    dumpSongFolder();

    songTableView->setModel(new SongTableModel( mSongFolderPath, this ) );
    songTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    songTableView->show();

    return folder;
}

void SongDbWindow::setupActions()
{
    connect( actionSelectFolder, SIGNAL(triggered( bool )), this, SLOT(selectSongFolder()) );
}

void SongDbWindow::dumpSongFolder()
{
    QDir dir;
    dir.setPath( mSongFolderPath );
    dir.setFilter( QDir::Files | QDir::NoSymLinks );
    dir.setSorting( QDir::Name );

    const QFileInfoList fileList = dir.entryInfoList();
    for ( int i = 0; i < fileList.size(); ++i )
    {
        qDebug() << fileList.at( i ).absoluteFilePath();
    }
}
