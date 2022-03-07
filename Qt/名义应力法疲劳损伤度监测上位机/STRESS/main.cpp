#include "stress.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    STRESS w;
    w.show();

    return a.exec();
}
