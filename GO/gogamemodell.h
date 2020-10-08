#ifndef GOGAMEMODELL_H
#define GOGAMEMODELL_H

#include <QObject>
#include <QVector>
#include <QSet>
#include "enums.h"
#include "field.h"

class GoGameModell : public QObject
{
public:
    GoGameModell(const BoardSize boardSize = Medium, int stepCount = 30);
    ~GoGameModell();
    void step(int x, int y);

signals:
    void boardChanged() { }
    void gameFinished() { }

private:
    BoardSize boardSize = Medium;
    Player activePlayer = WhitePlayer;
    Field** board;
    QVector<QSet<Field*>*>* groups;
    int whiteScore = 0;
    int blackScore = 0;
    int stepCount = 30;

    void placeStone(const int x, const int y);
    void manageGroups(const int x, const int y);
    void manageHealth(const int x, const int y);
    void manageAllHealths();
    bool freeSurroundedGroups();
};

#endif // GOGAMEMODELL_H
