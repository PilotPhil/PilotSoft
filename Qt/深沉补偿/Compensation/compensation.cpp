#include "compensation.h"
#include "ui_compensation.h"

Compensation::Compensation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Compensation)
{
    ui->setupUi(this);
}

Compensation::~Compensation()
{
    delete ui;
}
