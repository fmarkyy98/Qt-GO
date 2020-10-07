#ifndef GOGAMEVIEW_H
#define GOGAMEVIEW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class GoGameView; }
QT_END_NAMESPACE

class GoGameView : public QWidget
{
    Q_OBJECT

public:
    GoGameView(QWidget *parent = nullptr);
    ~GoGameView();

private:
    Ui::GoGameView *ui;
};
#endif // GOGAMEVIEW_H
