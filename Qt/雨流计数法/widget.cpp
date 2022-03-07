#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QVector<qreal> test;
    test<<-2<<1<<-3<<5<<-1<<3<<-4<<-3<<-2<<6<<4<<2<<7<<-2<<-4<<4<<-43<<8;


    rf.RunRainFlow(test);

    qDebug()<<"test"<<test;
}

Widget::~Widget()
{
    delete ui;
}
