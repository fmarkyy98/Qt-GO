#ifndef SAVEGAMEDIALOG_H
#define SAVEGAMEDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>

class SaveGameDialog : public QDialog
{
    Q_OBJECT
public:
    SaveGameDialog(QWidget *parent = 0);
    void setGameList(QVector<QString> saveGameList);
    int selectedGame() const { return listWidget->currentRow(); }

protected:
    QPushButton* okButton;
    QPushButton* cancelButton;
    QListWidget* listWidget;
};

#endif // SAVEGAMEDIALOG_H
