#include "table_ui.h"
#include "ui_table.h"

Table_UI::Table_UI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Table_UI)
{
    ui->setupUi(this);

    theModel=new QStandardItemModel(this);
    theSelection=new QItemSelectionModel(theModel);

    ui->tableView->setModel(theModel);//设置模型
    ui->tableView->setSelectionModel(theSelection);

    theModel->setRowCount(5);
    theModel->setColumnCount(100);

    verticalHeader<<"幅值"<<"均值"<<"极限应力"<<"修正后幅值"<<"损伤度";
    theModel->setVerticalHeaderLabels(verticalHeader);//设置垂直表头
}

Table_UI::~Table_UI()
{
    delete ui;
}

void Table_UI::updateTable(QVector<qreal> *AMP, QVector<qreal> *AVG, QVector<qreal> *ultraStress, QVector<qreal> *Modified, QVector<qreal> *Damage)
{
    theModel->setColumnCount(AMP->count());

    QStandardItem *aItem;

    for(int i=0;i<AMP->count();i++)
    {
        aItem=new QStandardItem(QString::number(AMP->at(i)));
        theModel->setItem(0,i,aItem);

        aItem=new QStandardItem(QString::number(AVG->at(i)));
        theModel->setItem(1,i,aItem);

        aItem=new QStandardItem(QString::number(ultraStress->at(i)));
        theModel->setItem(2,i,aItem);

        aItem=new QStandardItem(QString::number(Modified->at(i)));
        theModel->setItem(3,i,aItem);

        aItem=new QStandardItem(QString::number(Damage->at(i)));
        theModel->setItem(4,i,aItem);
    }


}
