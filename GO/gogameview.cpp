#include "gogameview.h"
#include "ui_gogameview.h"

GoGameView::GoGameView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GoGameView)
{
    ui->setupUi(this);
}

GoGameView::~GoGameView()
{
    delete ui;
}

