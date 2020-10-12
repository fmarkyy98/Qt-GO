#include "gogameview.h"
#include "ui_gogameview.h"
#include "gogamemodell.h"
#include "newgamedialog.h"

GoGameView::GoGameView(QWidget *parent) : QWidget(parent), ui(new Ui::GoGameView)
{
    ui->setupUi(this);
    goGameModell = new GoGameModell();
    resizeGrid();
    connect(goGameModell, SIGNAL(boardChanged(FieldType**, Player, int, int, int)),
             this,           SLOT(updateUi(FieldType**, Player, int, int, int)));
}

GoGameView::~GoGameView()
{
    delete ui;
}

void GoGameView::resizeGrid()
{
    foreach(QPushButton* item, buttonVector)
    {
        ui->playground_gridLayout->removeWidget(item);
        delete item;
    }
    buttonVector.clear();
    for(int i = 0; i < goGameModell->getBoardSize(); ++i)
    {
        for(int j = 0; j < goGameModell->getBoardSize(); ++j)
        {
            QPushButton* button = new QPushButton(this);
            buttonVector.push_back(button);
            ui->playground_gridLayout->addWidget(button, i, j);
            connect(button, SIGNAL(clicked()), this, SLOT(step()));
        }
    }
}

void GoGameView::step()
{
    QPushButton* senderButton = (QPushButton*)sender();
    int coardinate = ui->playground_gridLayout->indexOf(senderButton);
    int x = coardinate / goGameModell->getBoardSize();
    int y = coardinate % goGameModell->getBoardSize();
    goGameModell->step(x, y);
}

void GoGameView::updateUi(FieldType** visibleBoard, Player activePlayer, int whiteScore, int blackScore, int remainingSteps)
{
    ui->nextPlayerValue_label->setText(activePlayer == WhitePlayer ? "White" : "Black");
    ui->whiteScoreValue_label->setText(QString::number(whiteScore));
    ui->blackScoreValue_label->setText(QString::number(blackScore));
    ui->remainingStepsValue_label->setText(QString::number(remainingSteps));
    int n = goGameModell->getBoardSize();
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
        {
            if(visibleBoard[i][j] == White)
                this->buttonVector[i * n + j]->setStyleSheet("background-color:white;");
            else if(visibleBoard[i][j] == Black)
                this->buttonVector[i * n + j]->setStyleSheet("background-color:black;");
            else
                this->buttonVector[i * n + j]->setStyleSheet("background-color:grey;");
        }
}

void GoGameView::newGame()
{
    delete goGameModell;
    goGameModell = new GoGameModell((BoardSize)newGameDialog->getSize(), newGameDialog->getSteps());
    connect(goGameModell, SIGNAL(boardChanged(FieldType**, Player, int, int, int)),
             this,           SLOT(updateUi(FieldType**, Player, int, int, int)));
    resizeGrid();
    goGameModell->requestData();
}

void GoGameView::on_newGame_pushButton_clicked()
{
    if (newGameDialog == nullptr)
    {
        newGameDialog = new NewGameDialog();
        connect(newGameDialog, SIGNAL(accepted()), this, SLOT(newGame()));
    }
    newGameDialog->open();
}

void GoGameView::saveGame()
{
    // elmentjük a kiválasztott játékot

    if (goGameModell->saveGame(saveGameDialog->selectedGame()))
    {
        goGameModell->requestData();
        QMessageBox::information(this, trUtf8("GO"), trUtf8("Játék sikeresen mentve!"));
    }
    else
    {
        QMessageBox::warning(this, trUtf8("GO"), trUtf8("A játék mentése sikertelen!"));
    }
}

void GoGameView::on_saveGame_pushButton_clicked()
{
    if (saveGameDialog == nullptr)
    {
        saveGameDialog = new SaveGameDialog();
        connect(saveGameDialog, SIGNAL(accepted()), this, SLOT(saveGame()));
    }
    saveGameDialog->setGameList(goGameModell->saveGameList());
    saveGameDialog->open();
}

void GoGameView::loadGame()
{
    // betöltjük a kiválasztott játékot
    if (goGameModell->loadGame(loadGameDialog->selectedGame()))
    {
        resizeGrid();
        goGameModell->requestData();
        QMessageBox::information(this, trUtf8("JO"), trUtf8("Játék betöltve!"));
    }
    else
    {
        QMessageBox::warning(this, trUtf8("GO"), trUtf8("A játék betöltése sikertelen!"));
    }
}

void GoGameView::on_loadGame_pushButton_clicked()
{
    if (loadGameDialog == NULL) // ha még egyszer sem nyitották meg az ablakot
    {
        loadGameDialog = new LoadGameDialog();
        connect(loadGameDialog, SIGNAL(accepted()), this, SLOT(loadGame()));
    }

    // beállítjuk a listát, és megnyitjuk az ablakot
    loadGameDialog->setGameList(goGameModell->saveGameList());
    loadGameDialog->open();
}
