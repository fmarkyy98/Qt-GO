#ifndef GODATAACCESS_H
#define GODATAACCESS_H

#include <QString>
#include <QVector>

class GoDataAccess
{
public:
    explicit GoDataAccess() { }

    QVector<QString> saveGameList() const;
    bool saveGame(int gameIndex, const QVector<int> &saveGameData);
    bool loadGame(int gameIndex, QVector<int> &saveGameData);
};

#endif // GODATAACCESS_H
