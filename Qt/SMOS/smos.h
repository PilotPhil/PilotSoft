#ifndef SMOS_H
#define SMOS_H

#include <QMainWindow>

namespace Ui {
class SMOS;
}

class SMOS : public QMainWindow
{
    Q_OBJECT

public:
    explicit SMOS(QWidget *parent = nullptr);
    ~SMOS();

private:
    Ui::SMOS *ui;
};

#endif // SMOS_H
