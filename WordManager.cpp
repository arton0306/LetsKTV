#include <QTextStream>
#include <QStringList>
#include <QFile>
#include "WordManager.h"
#include "debug.h"

bool WordManager::isInit = false;
QMap<QString, int> * WordManager::strokeTable = NULL;
QMap<QString, int> * WordManager::zuinTable = NULL;

WordManager::WordManager()
{
}

/* static */ int WordManager::compare( CompareOrderType aOrder, QString const & aX, QString const & aY )
{
    DEBUG() << (*strokeTable)[aX[0]];
    //DEBUG() << strokeTable[aY[0]];
}

/* static */ void WordManager::test()
{
    checkInit();
}

/* static */ void WordManager::checkInit()
{
    if ( isInit == false )
    {
        strokeTable = new QMap<QString, int>();
        readStrokeOrderFile();
    }
    isInit = true;
}

/* static */ void WordManager::readStrokeOrderFile()
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
        (*strokeTable)[line.at(0)] = line.at(1).toInt();
    }
    file.close();
}
