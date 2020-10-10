#include "gogamemodell.h"

GoGameModell::GoGameModell(BoardSize boardSize, int stepCount)
{
    this->boardSize = boardSize;
    this->remainingStepCount = stepCount * 2;
    this->groups = new QVector<QSet<Field*>*>();
    this->board.resize(boardSize);
    for(int i = 0; i < this->boardSize; ++i)
    {
        this->board[i].resize(boardSize);
        for(int j = 0; j < this->boardSize; ++j)
        {
            board[i][j] = new Field();
        }
    }
}

GoGameModell::~GoGameModell()
{

}

void GoGameModell::placeStone(const int x,const int y)
{
    this->board[x][y]->fieldType = (FieldType)this->activePlayer;
}

void GoGameModell::manageHealth(int x, int y)
{
    if(x != 0)
        --this->board[x-1][y]->health;
    else
        --this->board[x][y]->health;

    if(x != boardSize - 1)
        --this->board[x+1][y]->health;
    else
        --this->board[x][y]->health;

    if(y != 0)
        --this->board[x][y-1]->health;
    else
        --this->board[x][y]->health;

    if(y != boardSize - 1)
        --this->board[x][y+1]->health;
    else
        --this->board[x][y]->health;
}

void GoGameModell::manageAllHealths()
{
    for(int i = 0; i < this->boardSize; ++i)
        for(int j = 0; j < this->boardSize; ++j)
            this->board[i][j]->health = 4;

    for(int i = 0; i < this->boardSize; ++i)
        for(int j = 0; j < this->boardSize; ++j)
            if(this->board[i][j]->fieldType != Empty)
                manageHealth(i, j);
}

void GoGameModell::manageGroups(const int x, const int y)
{
    QSet<Field*>* actualGroup = nullptr;
    for(int i = x-1; i <= x+1; ++i)
        for(int j = y-1; j <= y+1; ++j)
            if(((i == x) ^ (j == y)) && 0 <= i && i < boardSize && 0 <= j && j < boardSize &&
                board[i][j]->fieldType == board[x][y]->fieldType)
            {
                int k = 0;
                for(; !(*groups)[k]->contains(board[i][j]); ++k);
                if(actualGroup == nullptr)
                {
                    actualGroup = (*groups)[k];
                    *actualGroup += board[x][y];
                }
                else
                {
                    *actualGroup += *(*groups)[k];
                    if(actualGroup != (*groups)[k])
                    {
                    delete (*groups)[k];
                    (*groups)[k] = groups->last();
                    groups->pop_back();
                    }
                }
            }
    if(actualGroup == nullptr)
    {
        actualGroup = new QSet<Field*>();
        *actualGroup += board[x][y];
        groups->push_back(actualGroup);
    }
}

bool GoGameModell::freeSurroundedGroups()
{
    bool isStonesCaptured = false;
    for(int i = 0; i < groups->size(); ++i)
    {
        bool isAllZeroHealth = true;
        for(Field* item : *(*groups)[i])
        {
            if (!isAllZeroHealth) break;
            isAllZeroHealth &= item->health == 0;
        }
        isStonesCaptured |= isAllZeroHealth;
        if(isAllZeroHealth)
        {
            if((*groups)[i]->values()[0]->fieldType == White) // values is modern toList.
            {
                blackScore += (*groups)[i]->size();
            }
            else
            {
                whiteScore += (*groups)[i]->size();
            }
            for(Field* item : *(*groups)[i])
            {
                item->fieldType = Empty;
            }
            delete (*groups)[i];
            (*groups)[i] = (*groups).last();
            groups->pop_back();
            --i;
        }
    }
    return isStonesCaptured;
}

FieldType** GoGameModell::convertToVisibleBoard(const QVector<QVector<Field*>>& board) const
{
    FieldType** result = new FieldType*[boardSize];
    for(int i = 0; i < boardSize; ++i)
    {
        result[i] = new FieldType[boardSize];
        for(int j = 0; j < boardSize; ++j)
        {
            result[i][j] = board[i][j]->fieldType;
        }
    }
    return result;
}

Player* GoGameModell::decideWinner() const
{
    Player* result = whiteScore > blackScore ? new Player(WhitePlayer) : whiteScore < blackScore ? new Player(BlackPlayer) : nullptr;
    return result;
}

void GoGameModell::step(int x, int y)
{
    if(0 <= x && x < this->boardSize && 0 <= y && y < this->boardSize && board[x][y]->fieldType == Empty)
    {
        placeStone(x, y);
        manageHealth(x, y);
        manageGroups(x, y);
        if(freeSurroundedGroups())
            manageAllHealths();
        --remainingStepCount;
        emit boardChanged(convertToVisibleBoard(board), activePlayer, whiteScore, blackScore, remainingStepCount);
        if(remainingStepCount <= 0)
            emit gameFinished(decideWinner());
        activePlayer = (Player)(activePlayer % 2 + 1);
    }
}

bool GoGameModell::saveGame(int gameIndex)
{
    QVector<int> saveGameData;
    saveGameData.push_back(boardSize);
    saveGameData.push_back(activePlayer);
    saveGameData.push_back(whiteScore);
    saveGameData.push_back(blackScore);
    saveGameData.push_back(remainingStepCount);
    for(int i = 0; i < boardSize; ++i)
        for(int j = 0; j < boardSize; ++j)
        {
            saveGameData.push_back(board[i][j]->fieldType);
            saveGameData.push_back(board[i][j]->health);
        }
    return goDataAccess.saveGame(gameIndex, saveGameData);
}

void GoGameModell::rebuildGroups()
{
    for(int i = 0; i < boardSize; ++i)
        for(int j = 0; j < boardSize; ++j)
            if(board[i][j]->fieldType != Empty)
                manageGroups(i, j);
}

bool GoGameModell::loadGame(int gameIndex)
{
    QVector<int> saveGameData;
    if (!goDataAccess.loadGame(gameIndex, saveGameData))
        return false;
    boardSize = (BoardSize)saveGameData[0];
    activePlayer = (Player)saveGameData[1];
    whiteScore = saveGameData[2];
    blackScore = saveGameData[3];
    remainingStepCount = saveGameData[4];
    int k = 5;
    for(int i = 0; i < boardSize; ++i)
        for(int j = 0; j < boardSize; ++j)
        {
            board[i][j]->fieldType = (FieldType)saveGameData[k];
            board[i][j]->health = saveGameData[k+1];
            ++++k;
        }
    rebuildGroups();
    return true;
}

void GoGameModell::request()
{
    emit boardChanged(convertToVisibleBoard(board), activePlayer, whiteScore, blackScore, remainingStepCount);
}

QVector<QString> GoGameModell::saveGameList() const
{
    return goDataAccess.saveGameList(); // az adatelérés végzi a tevékenységeket
}
