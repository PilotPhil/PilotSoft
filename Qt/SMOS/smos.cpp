#include "smos.h"
#include "ui_smos.h"

SMOS::SMOS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SMOS)
{
    ui->setupUi(this);

}

SMOS::~SMOS()
{
    delete ui;
}
