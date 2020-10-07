#include "gogamemodell.h"

GoGameModell::GoGameModell()
{
    this->groups = new QVector<QSet<Field*>*>();
    this->board = new Field*[this->boardSize];
    for (int i = 0; i < this->boardSize; ++i)
    {
        this->board[i] = new Field[this->boardSize];
    }
}

GoGameModell::~GoGameModell()
{

}

void GoGameModell::step(int x, int y)
{
    if(x < this->boardSize && y < this->boardSize)
    {
        board[x][y].fieldType = activePlayer ? Black : White;

        --board[x-1][y].health;
        --board[x+1][y].health;
        --board[x][y-1].health;
        --board[x][y+1].health;

        QSet<Field*>* actualGroup;
        for(int i = x-1; i <= x+1; i+=2)
            for(int j = y-1; j <= y+1; j+=2)
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

        for(int i = 0; i < groups->size(); ++i)
        {
            bool isAllZeroHealth = true;
            for(Field* item : *(*groups)[i])
            {
                if (!isAllZeroHealth) break;
                isAllZeroHealth &= !item->health;
            }
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
            }
        }

        activePlayer = activePlayer ? BlackPlayer : WhitePlayer;
    }
}
