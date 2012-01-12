#ifndef DEBUG_H
#define DEBUG_H

#include <QtGlobal>
#include <QtDebug>
#include <QString>

namespace debug
{
    void setProgramTimer();
    QString getElapseTime();
    void debugWinMsgHandler(QtMsgType type, const char *msg);
    void dumpSongFolder( QString aSongFolderPath );
};

#endif // DEBUG_H
