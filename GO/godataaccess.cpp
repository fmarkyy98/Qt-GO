#include "godataaccess.h"
#include <QDateTime>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>

QVector<QString> GoDataAccess::saveGameList() const
{
    QVector<QString> result(5);

    // végigmegyünk az 5 helyen
    for (int i = 0; i < 5; i++)
    {
        if (QFile::exists("game" + QString::number(i) + ".save")) // ha az adott mentés létezik
        {
            QFileInfo info("game"+ QString::number(i) + ".save");
            result[i] = "[" + QString::number(i + 1) + "] " + info.lastModified().toString("yyyy.MM.dd HH:mm:ss");
            // akkor betöltjük a fájl módosítás időpontját
        }
    }

    return result;
}

bool GoDataAccess::saveGame(int gameIndex, const QVector<int> &saveGameData)
{
    QFile file("game" + QString::number(gameIndex) + ".save");
    if (!file.open(QFile::WriteOnly))
        return false;

    QTextStream stream(&file);

    // soronként egy adatot írunk ki
    for(int item : saveGameData)
        stream << item << Qt::endl;

    file.close();

    return true;
}

bool GoDataAccess::loadGame(int gameIndex, QVector<int> &saveGameData)
{
    QFile file("game" + QString::number(gameIndex) + ".save");
    if (!file.open(QFile::ReadOnly))
        return false;

    QTextStream stream(&file);

    // soronként beolvassuk az adatokat a fájlból
    while(!stream.atEnd())
        saveGameData.push_back(stream.readLine().toInt());

    file.close();

    return true;
}
