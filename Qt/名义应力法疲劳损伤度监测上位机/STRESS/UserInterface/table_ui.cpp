#include "table_ui.h"
#include "ui_table_ui.h"

Table_UI::Table_UI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Table_UI)
{
    ui->setupUi(this);

    theModel=new QStandardItemModel(this);
    theSelection=new QItemSelectionModel(theModel);

    ui->tableView->setModel(theModel);//设置模型
    theModel->setRowCount(100);//100行
    theModel->setColumnCount(5);//5列

    //设置列宽度
    ui->tableView->setColumnWidth(0,80);
    ui->tableView->setColumnWidth(1,80);
    ui->tableView->setColumnWidth(2,80);
    ui->tableView->setColumnWidth(3,90);
    ui->tableView->setColumnWidth(4,125);

    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//行间距自动调整

    ui->tableView->setSelectionModel(theSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置表格为只读

    verticalHeader<<"幅值"<<"均值"<<"极限应力"<<"修正后幅值"<<"损伤度";
    theModel->setHorizontalHeaderLabels(verticalHeader);//设置垂直表头
}

Table_UI::~Table_UI()
{
    delete ui;
}

void Table_UI::updateTable(QVector<qreal> *AMP, QVector<qreal> *AVG, QVector<qreal> *ultraStress, QVector<qreal> *Modified, QVector<qreal> *Damage)
{
    if(theModel->rowCount()<AMP->count())
    {
        theModel->setRowCount(AMP->count());//设置列数等于幅值点个数
    }

    for(int i=0;i<AMP->count();i++)
    {
        aItem=new QStandardItem(QString::number(AMP->at(i)));
        aItem->setTextAlignment(Qt::AlignHCenter);
        aItem->setForeground(QBrush(QColor(83,194,60)));
        aItem->setFont(QFont("Microsoft YaHei",10,QFont::Black));
        theModel->setItem(i,0,aItem);//设置幅值

        aItem=new QStandardItem(QString::number(AVG->at(i)));
        aItem->setTextAlignment(Qt::AlignHCenter);
        aItem->setForeground(QBrush(QColor(83,194,60)));
        aItem->setFont(QFont("Microsoft YaHei",10,QFont::Black));
        theModel->setItem(i,1,aItem);//设置均值

        aItem=new QStandardItem(QString::number(ultraStress->at(i)));
        aItem->setTextAlignment(Qt::AlignHCenter);
        aItem->setForeground(QBrush(QColor(245,211,111)));
        aItem->setFont(QFont("Microsoft YaHei",10,QFont::Black));
        theModel->setItem(i,2,aItem);//设置极限应力

        aItem=new QStandardItem(QString::number(Modified->at(i)));
        aItem->setTextAlignment(Qt::AlignHCenter);
        aItem->setForeground(QBrush(QColor(0,120,215)));
        aItem->setFont(QFont("Microsoft YaHei",10,QFont::Black));
        theModel->setItem(i,3,aItem);//设置修正后应力

        aItem=new QStandardItem(QString::number(Damage->at(i)));
        aItem->setTextAlignment(Qt::AlignHCenter);
        aItem->setForeground(QBrush(QColor(255,0,0)));
        aItem->setFont(QFont("Microsoft YaHei",10,QFont::Black));
        theModel->setItem(i,4,aItem);//设置损伤度
    }


}
