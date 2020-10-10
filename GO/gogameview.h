#ifndef GOGAMEVIEW_H
#define GOGAMEVIEW_H

#include <QVector>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include "gogamemodell.h"
#include "savegamedialog.h"
#include "loadgamedialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GoGameView; }
QT_END_NAMESPACE

class GoGameView : public QWidget
{
    Q_OBJECT

public:
    GoGameView(QWidget *parent = nullptr);
    ~GoGameView();

private slots:
    void resizeGrid();
    void step();
    void updateUi(FieldType** visibleBoard, Player activePlayer, int whiteScore, int blackScore, int remainingSteps);
    void on_newGame_pushButton_clicked();
    void saveGame();
    void on_saveGame_pushButton_clicked();
    void loadGame();
    void on_loadGame_pushButton_clicked();

private:
    Ui::GoGameView *ui;
    GoGameModell goGameModell;
    QVector<QPushButton*> buttonVector;
    SaveGameDialog* saveGameDialog = nullptr;
    LoadGameDialog* loadGameDialog = nullptr;
};
#endif // GOGAMEVIEW_H
