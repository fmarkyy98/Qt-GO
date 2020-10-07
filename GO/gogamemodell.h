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
    GoGameModell();
    ~GoGameModell();
    void step(int, int);

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

    void move();

};

#endif // GOGAMEMODELL_H
