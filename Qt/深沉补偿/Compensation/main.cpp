#include "compensation.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Compensation w;
    w.show();

    return a.exec();
}
