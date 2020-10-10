#ifndef LOADGAMEDIALOG_H
#define LOADGAMEDIALOG_H

#include <QDialog>
#include "savegamedialog.h"

class LoadGameDialog : public SaveGameDialog
{
    Q_OBJECT
public:
    LoadGameDialog(QWidget *parent = 0);

protected slots:
    void okButton_Clicked();
};

#endif // LOADGAMEDIALOG_H
