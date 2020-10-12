#ifndef GOGAMEMODELL_H
#define GOGAMEMODELL_H

#include <QObject>
#include <QVector>
#include <QSet>
#include "enums.h"
#include "field.h"
#include "godataaccess.h"

class GoGameModell : public QObject
{
    Q_OBJECT
public:
    GoGameModell(const BoardSize boardSize = Medium, int stepCount = 30);
    ~GoGameModell();

    BoardSize getBoardSize() { return boardSize; }

    void step(int x, int y);
    bool saveGame(int gameIndex);
    bool loadGame(int gameIndex);
    void requestData();

    QVector<QString> saveGameList() const;

signals:
    void boardChanged(FieldType** visibleBoard, Player activePlayer, int whiteScore, int blackScore, int remainingSteps) const;
    void gameFinished(Player* winner);

private:
    BoardSize boardSize = Medium;
    Player activePlayer = WhitePlayer;
    int whiteScore = 0;
    int blackScore = 0;
    int remainingStepCount = 30;
    QVector<QVector<Field*>> board;
    QVector<QSet<Field*>*>* groups;
    GoDataAccess goDataAccess;

    void placeStone(const int x, const int y);
    void manageGroups(const int x, const int y);
    void manageHealth(const int x, const int y);
    void manageAllHealths();
    bool freeSurroundedGroups();
    FieldType** convertToVisibleBoard(const QVector<QVector<Field*>>& board) const;
    Player* decideWinner() const;
    void rebuildGroups();
};

#endif // GOGAMEMODELL_H
