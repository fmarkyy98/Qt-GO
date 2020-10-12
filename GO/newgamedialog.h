#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QLabel>

class NewGameDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NewGameDialog(QWidget *parent = 0);
    int getSteps() { return spinBox->value(); }
    int getSize() { return listWidget->currentRow() == 0 ? 5 : listWidget->currentRow() == 1 ? 9 : 19; }

private:
    QPushButton* okButton;
    QPushButton* cancelButton;
    QListWidget* listWidget;
    QSpinBox* spinBox;
    QLabel* label;
};

#endif // NEWGAMEDIALOG_H
