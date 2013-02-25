
#include <QtGui>
#include <QApplication>
#include "KGraph.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KGraph w;
    w.show();
    return a.exec();
}
