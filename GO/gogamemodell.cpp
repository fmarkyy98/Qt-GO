#include "gogamemodell.h"

GoGameModell::GoGameModell(BoardSize boardSize, int stepCount)
{
    this->boardSize = boardSize;
    this->stepCount = stepCount * 2;
    this->groups = new QVector<QSet<Field*>*>();
    this->board = new Field*[this->boardSize];
    for (int i = 0; i < this->boardSize; ++i)
        this->board[i] = new Field[this->boardSize];
}

GoGameModell::~GoGameModell()
{

}

void GoGameModell::placeStone(const int x,const int y)
{
    this->board[x][y].fieldType = this->activePlayer ? Black : White;
    --stepCount;
}

void GoGameModell::manageHealth(int x, int y)
{
    if(x != 0)
        --this->board[x-1][y].health;

    if(x != boardSize - 1)
        --this->board[x+1][y].health;

    if(y != 0)
        --this->board[x][y-1].health;

    if(y != boardSize - 1)
        --this->board[x][y+1].health;
}

void GoGameModell::manageAllHealths()
{
    for(int i = 0; i < this->boardSize; ++i)
        for(int j = 0; j < this->boardSize; ++j)
            this->board[i][j].health = 4;

    for(int i = 0; i < this->boardSize; ++i)
        for(int j = 0; j < this->boardSize; ++j)
            if(!this->board[i][j].fieldType)
                manageHealth(i, j);
}

void GoGameModell::manageGroups(const int x, const int y)
{
    QSet<Field*>* actualGroup;
    for(int i = x-1; i <= x+1 && 0 <= i && i < boardSize; i+=2)
        for(int j = y-1; j <= y+1 && 0 <= y && i < boardSize; j+=2)
            if(board[i][j].fieldType == board[x][y].fieldType)
            {
                int k = 0;
                for(; !(*groups)[k]->contains(&board[i][j]); ++k);
                if(actualGroup == nullptr)
                {
                    actualGroup = (*groups)[k];
                    *actualGroup += &board[x][y];
                }
                else
                {
                    *actualGroup += *(*groups)[k];
                }
            }
    if(actualGroup == nullptr)
    {
        actualGroup = new QSet<Field*>();
        *actualGroup += &board[x][y];
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
            isAllZeroHealth &= !item->health;
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

void GoGameModell::step(int x, int y)
{
    if(x < this->boardSize && y < this->boardSize && !board[x][y].fieldType)
    {
        placeStone(x, y);

        manageHealth(x, y);

        manageGroups(x, y);

        bool isStonesCaptured = freeSurroundedGroups();

        if(isStonesCaptured)
            manageAllHealths();

        activePlayer = activePlayer ? WhitePlayer : BlackPlayer;
    }
}
