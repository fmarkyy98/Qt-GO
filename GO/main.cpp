#include "gogameview.h"

#include <QApplication>

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    GoGameView w;
    w.show();
    return a.exec();
}
