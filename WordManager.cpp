#include <QTextStream>
#include <QStringList>
#include <QFile>
#include "WordManager.h"
#include "debug.h"

WordManager * WordManager::wordManager = NULL;

WordManager::WordManager()
{
}

/* static */ int WordManager::compare( CompareOrderType aOrder, QString const & aX, QString const & aY )
{
    checkInit();
    DEBUG() << wordManager->mStrokeTable[aX[0]];
}

/* static */ void WordManager::checkInit()
{
    if ( wordManager == NULL )
    {
        wordManager = new WordManager;
        wordManager->readStrokeOrderFile();
    }
}

void WordManager::readStrokeOrderFile()
{
    QFile file("stroke_order.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qCritical() << "read stroke_order.txt failed";
        return;
    }
    QTextStream in(&file);
    in.setCodec( "UTF-8" );
    while (!in.atEnd()) {
        QStringList line = in.readLine().split(" ");

        // in the file, col 0 is the word, col 1 is #stroke
        mStrokeTable[line.at(0)] = line.at(1).toInt();
    }
    file.close();
}
