#include <QMessageBox>
#include "loadgamedialog.h"

LoadGameDialog::LoadGameDialog(QWidget *parent) : SaveGameDialog(parent)
{
    setWindowTitle("Tic-Tac-Toe - Játék betöltése");

    // ellenőrzést is végzünnk az OK gomb lenyomására
    disconnect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(okButton_Clicked()));
}

void LoadGameDialog::okButton_Clicked()
{
    if (listWidget->currentItem()->text() == "üres")
    {
        // ha üres mezőt választott, akkor nem engedjük tovább
        QMessageBox::warning(this, trUtf8("Tic-Tac-Toe"), trUtf8("Nincs játék kiválasztva!"));
        return;
    }

    accept(); // kül
}
