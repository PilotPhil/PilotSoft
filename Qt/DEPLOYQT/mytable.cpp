#include "mytable.h"
#include "ui_mytable.h"

MYTABLE::MYTABLE(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MYTABLE)
{
    ui->setupUi(this);

    model=new QStandardItemModel(this);
    selection=new QItemSelectionModel(model);

    //设置表头
    QStringList labels;
    labels<<"时间"<<"记录的EXE(双击快速打包)";
    model->setHorizontalHeaderLabels(labels);

//    ui->tableView->verticalHeader()->hide();//隐藏垂直表头

    ui->tableView->setAlternatingRowColors(true);//设置相邻行颜色交替显示

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置禁用表格编辑

    ui->tableView->setModel(model);

    //设置列数
    model->setColumnCount(2);


    //设置列宽度
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    ui->tableView->verticalHeader()->setDefaultSectionSize(16);

    read4Csv();
}

MYTABLE::~MYTABLE()
{
    delete ui;
}

void MYTABLE::receiveExeAddress(QString address)
{
    insert2TableNoRepete(address);
}

void MYTABLE::save2Csv()
{
    QFile data("ExeRecord.csv");// 以上两行用时间戳作为文件名
    if(data.open(QFile::WriteOnly | QFile::Truncate))// 打开文件
    {
        QTextStream out(&data);    // 输入流
//        out << "name: ," << "jone," << "\n";

        int row=model->rowCount();
        for(int i=0;i<row;i++)
        {
            out<<model->item(i,0)->text()<<","<<model->item(i,1)->text()<< "\n";
        }
    }
    data.close();

}

void MYTABLE::read4Csv()
{
    QDir dir = QDir::current();
    QFile file(dir.filePath("ExeRecord.csv"));
    if(file.exists()==false)
    {
        qDebug()<<"找不到此文件";
        return;
    }



    if(!file.open(QIODevice::ReadOnly))
         qDebug()<<"OPEN FILE FAILED";

    QTextStream * out = new QTextStream(&file);//文本流
    QStringList tempOption = out->readAll().split("\n");//每行以\n区分

    model->setRowCount(tempOption.count()-1);

    for(int i=0;i<tempOption.count()-1;i++)
    {
        QStringList tempbar = tempOption.at(i).split(",");

        qDebug()<<tempbar.at(0);
        qDebug()<<tempbar.at(1);

        model->setItem(i,0,new QStandardItem(tempbar.at(0)));
        model->setItem(i,1,new QStandardItem(tempbar.at(1)));
    }

    file.close();//操作完成后记得关闭文件
}

void MYTABLE::insert2TableNoRepete(QString address)
{
    int row=model->rowCount();
    bool repeatFlag=false;
    QString temp;

    qDebug()<<"ADDRESS:"<<address;

    int index;
    for(index=0;index<row;index++)
    {
        temp=model->item(index,1)->text();
        if(address==temp)//有重复
        {
            repeatFlag=true;
            break;
        }
    }

    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy/MM/dd hh:mm");
    qDebug()<<"TIME:"<<current_date;

    if(repeatFlag==true)//有重复
    {
        model->setItem(index,0,new QStandardItem(current_date));
        ui->tableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    }
    else//无重复
    {
        QList<QStandardItem *> toInsert;
        toInsert.append(new QStandardItem(current_date));
        toInsert.append(new QStandardItem(address));
        model->insertRow(row,toInsert);
    }


    save2Csv();//保存到csv

}



void MYTABLE::on_tableView_doubleClicked(const QModelIndex &index)
{
    qDebug()<<index;
    QString address;

    address=model->item(index.row(),1)->text();
    qDebug()<<"RECORDER ADDRESS"<<address;
    sendRecordExeAddress(address);
}
