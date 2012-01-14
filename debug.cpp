#include <QtGui/QTextEdit>
#include <QtGui/QMessageBox>
#include <QDir>
#include <QTime>
#include "debug.h"

namespace debug
{
    static QTime * programTimer;

    void setProgramTimer()
    {
        programTimer = new QTime( 0, 0, 0 );  // it last to end and we won't delete it for laziness
        programTimer->start();
    }

    QString getElapseTime()
    {
        int elapsedMSec = programTimer->elapsed();
        QTime zeroTime = QTime( 0, 0, 0 );
        QTime elpasedTime = zeroTime.addMSecs( elapsedMSec );
        return elpasedTime.toString( "hh:mm:ss.zzz" );
    }

    void debugWinMsgHandler(QtMsgType type, const char *msg)
    {
        static QTime zeroTime = QTime( 0, 0, 0 );

        static QTextEdit *edit = new QTextEdit();
        edit->setWindowTitle("Debug window");
        edit->show();
        switch (type)
        {
            case QtDebugMsg:
                edit->append(QString("\%1 <b>Debug:</b> \%2").arg(getElapseTime()).arg(msg));
                break;
            case QtWarningMsg:
                edit->append(QString("\%1 <b>Warning:</b> \%2").arg(getElapseTime()).arg(msg));
                break;
            case QtCriticalMsg:
                edit->append(QString("\%1 <font color=\"red\"><b>Critical:</b></font> \%2").arg(getElapseTime()).arg(msg));
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
}
