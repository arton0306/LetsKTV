#include <QFileDialog>
#include "debug.h"
#include "SongDbWindow.h"

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
    mSongFolder = folder;
    qDebug() << mSongFolder;
    return folder;
}

void SongDbWindow::setupActions()
{
    connect( actionSelectFolder, SIGNAL(triggered( bool )), this, SLOT(selectSongFolder()) );
}
