#include "smos.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SMOS w;
    w.show();

    return a.exec();
}
