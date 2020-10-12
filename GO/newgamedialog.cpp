#include <QVBoxLayout>
#include <QHBoxLayout>
#include "newgamedialog.h"

NewGameDialog::NewGameDialog(QWidget *parent)
{
    setFixedSize(300, 200);
    setWindowTitle("GO - Save");

    listWidget = new QListWidget();
    label = new QLabel("Steps:");
    spinBox = new QSpinBox();
    okButton = new QPushButton("Ok");
    cancelButton = new QPushButton("Cancel");

    QHBoxLayout* hlayout2 = new QHBoxLayout();
    hlayout2->addWidget(label);
    hlayout2->addWidget(spinBox);

    QHBoxLayout* hlayout1 = new QHBoxLayout();
    hlayout1->addWidget(okButton);
    hlayout1->addWidget(cancelButton);

    listWidget->addItem("5 x 5");
    listWidget->addItem("9 x 9");
    listWidget->addItem("19 x 19");

    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->addWidget(listWidget);
    vlayout->addLayout(hlayout2);
    vlayout->addLayout(hlayout1);

    setLayout(vlayout);

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

