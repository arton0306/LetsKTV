#include <QtGui/QTextEdit>
#include <QtGui/QMessageBox>
#include <QDir>
#include "debug.h"

namespace debug
{
    void debugWinMsgHandler(QtMsgType type, const char *msg)
    {
        static QTextEdit *edit = new QTextEdit();
        edit->setWindowTitle("Debug window");
        edit->show();
        switch (type)
        {
            case QtDebugMsg:
                edit->append(QString("<b>Debug:</b> \%1").arg(msg));
                break;
            case QtWarningMsg:
                edit->append(QString("<b>Warning:</b> \%1").arg(msg));
                break;
            case QtCriticalMsg:
                edit->append(QString("<font color=\"red\"><b>Critical:</b></font> \%1").arg(msg));
                break;
            case QtFatalMsg:
                QMessageBox::critical(0, "Debug - Fatal", msg);
                abort();
        }
    }
    void dumpSongFolder( QString aSongFolderPath )
    {
        QDir dir;
        dir.setPath( aSongFolderPath );
        dir.setFilter( QDir::Files | QDir::NoSymLinks );
        dir.setSorting( QDir::Name );

        const QFileInfoList fileList = dir.entryInfoList();
        for ( int i = 0; i < fileList.size(); ++i )
        {
            qDebug() << fileList.at( i ).absoluteFilePath();
        }
    }
};
