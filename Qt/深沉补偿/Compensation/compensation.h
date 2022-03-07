#ifndef COMPENSATION_H
#define COMPENSATION_H

#include <QMainWindow>

namespace Ui {
class Compensation;
}

class Compensation : public QMainWindow
{
    Q_OBJECT

public:
    explicit Compensation(QWidget *parent = nullptr);
    ~Compensation();

private:
    Ui::Compensation *ui;
};

#endif // COMPENSATION_H
