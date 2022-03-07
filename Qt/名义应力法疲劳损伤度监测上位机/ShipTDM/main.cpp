#include "shiptdm.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShipTDM w;
    w.show();

    return a.exec();
}
