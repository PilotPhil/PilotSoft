#include "deployqt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DEPLOYQT w;
    w.show();

    return a.exec();
}
