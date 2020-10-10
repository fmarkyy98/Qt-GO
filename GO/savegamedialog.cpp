#include "savegamedialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

SaveGameDialog::SaveGameDialog(QWidget *parent) : QDialog(parent)
{
    setFixedSize(300, 200);
    setWindowTitle("GO - Save");

    listWidget = new QListWidget();
    okButton = new QPushButton("Ok");
    cancelButton = new QPushButton("Cancel");

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addWidget(okButton);
    hlayout->addWidget(cancelButton);

    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->addWidget(listWidget);
    vlayout->addLayout(hlayout);

    setLayout(vlayout);

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void SaveGameDialog::setGameList(QVector<QString> saveGameList)
{
    listWidget->clear();

    // betöltjük az elemeket a listából
    for (int i = 0; i < 5; i++)
    {
        if (i < saveGameList.size() && !saveGameList[i].isEmpty())
            listWidget->addItem(saveGameList[i]);
        else
            listWidget->addItem("üres"); // ami nincs megadva, az üres lesz
    }
}
