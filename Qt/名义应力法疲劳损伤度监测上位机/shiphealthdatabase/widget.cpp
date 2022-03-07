#include "widget.h"
#include "ui_widget.h"

#include <QTextCodec>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));//解决mysql中中文在Qt中乱码问题
    init_window();
    init_dataBase();
    init_modelView();
}

Widget::~Widget()
{
    delete ui;
}


/*-----------------------初始化设置-----------------------*/
//应用程序初始化
void Widget::init_window()
{
    this->setWindowIcon(QIcon(":/故障分析.png"));
    this->setWindowTitle("船舶疲劳寿命静态管理分析");

    /*----------------两个定时器----------------*/
    mytimer=new QTimer(this);
    mytimer->setInterval(3000);
    mytimer->start();
    connect(mytimer,&QTimer::timeout,this,&Widget::tableSpace);//每个3s更新数据表占用空间

    autoUpdate=new QTimer(this);
    autoUpdate->setInterval(1000);
    connect(autoUpdate,&QTimer::timeout,this,&Widget::tableAutoUpdate);//每个1秒自动刷新表

    /*----------------其他----------------*/
    QStringList comp;
    comp<<"Time"<<"AMP"<<"AVG"<<"US"<<"DAM"<<"SR";
    QCompleter *compForlineEdit_queryBySimplifiedSql=new QCompleter(comp,this);
    ui->lineEdit_queryBySimplifiedSql->setCompleter(compForlineEdit_queryBySimplifiedSql);//输入补全提示

    ui->stackedWidget->setCurrentIndex(0);
    ui->button_choose_databaseInfo->setChecked(true);

    chooseFlag=2;

    setWindowOpacity(0.98);//窗口透明度

}
//数据库连接初始化
void Widget::init_dataBase()
{
    /*----------------数据库连接----------------*/
    db=QSqlDatabase::addDatabase("QMYSQL");

    sqlQuery=new QSqlQuery(db);

    db.setDatabaseName("ship");//从txt文件读取
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("1126");


    //打开数据库
    if(db.open()==false)
    {
        QMessageBox::warning(this,"错误",QString("数据库打开错误%1").arg(db.lastError().text()));//报错
        return;
    }
    else
    {
        qDebug()<<"数据库打开成功";
    }
}
//model-view初始化
void Widget::init_modelView()
{
    /*----------------model-view----------------*/
    model_dam=new myQsqlTableModel();
    model_dam->setTable("shiphealth");
    ui->tableView_dam->setModel(model_dam);
    model_dam->select();

    model_dam->setHeaderData(0,Qt::Horizontal,"时间TIME");
    model_dam->setHeaderData(1,Qt::Horizontal,"幅值AMP");
    model_dam->setHeaderData(2,Qt::Horizontal,"均值AVG");
    model_dam->setHeaderData(3,Qt::Horizontal,"极限应力US");
    model_dam->setHeaderData(4,Qt::Horizontal,"应力范围SR");
    model_dam->setHeaderData(5,Qt::Horizontal,"损伤度DAM");

    ui->tableView_dam->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//表格宽度自适应
    ui->tableView_dam->setAlternatingRowColors(true);
    ui->tableView_dam->verticalHeader()->setVisible(false);//垂直表头隐藏


    model_strain=new myQsqlTableModel();
    model_strain->setTable("realtimestrain");
    model_strain->setHeaderData(0,Qt::Horizontal,"时间TIME");
    model_strain->setHeaderData(1,Qt::Horizontal,"应变STRAIN");
    ui->tableView_strain->setModel(model_strain);
    ui->tableView_strain->verticalHeader()->setVisible(false);//垂直表头隐藏
    model_strain->select();
    ui->tableView_strain->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//表格宽度自适应
    ui->tableView_strain->setAlternatingRowColors(true);

    //    model_user=new myQsqlTableModel();
    //    model_user->setTable("user");
    //    model_user->setEditStrategy(QSqlTableModel::OnManualSubmit);//手动提交
    //    model_user->setHeaderData(0,Qt::Horizontal,"编号");
    //    model_user->setHeaderData(1,Qt::Horizontal,"姓名");
    //    model_user->setHeaderData(2,Qt::Horizontal,"职位");
    //    model_user->setHeaderData(3,Qt::Horizontal,"账号");
    //    model_user->setHeaderData(4,Qt::Horizontal,"密码");
    //    model_user->setHeaderData(5,Qt::Horizontal,"创建时间");

    //    ui->tableView_user->setModel(model_user);
    //    ui->tableView_user->verticalHeader()->setVisible(false);//垂直表头隐藏
    //    model_user->select();
    //    ui->tableView_user->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//表格宽度自适应
    //    ui->tableView_user->setAlternatingRowColors(true);
}



/*-----------------------查询部分-----------------------*/
//按时间选择记录
void Widget::on_Button_queryByTime_clicked()
{
    QDateTime ts=ui->dateTimeEdit_start->dateTime();
    QDateTime te=ui->dateTimeEdit_end->dateTime();

    QString timeStart=ui->dateTimeEdit_start->text();//获取开始时间
    QString timeEnd=ui->dateTimeEdit_end->text();//获取结束时间

    timeStart=timeStart.right(19);//截取字符串
    timeEnd=timeEnd.right(19);//截取字符串

    if(ui->radioButton_timestart->isChecked()==true&&ui->radioButton_timeEnd->isChecked()==true)
    {
        if(ts>=te)//比较时间
        {
            QMessageBox::warning(this,"错误","起始时间需要晚于结束时间");
            return;//时间不对就结束函数
        }
        SQL=QString("Time>='%1' and Time<='%2'").arg(timeStart).arg(timeEnd);//start<?<end
    }
    else if(ui->radioButton_timestart->isChecked()==true&&ui->radioButton_timeEnd->isChecked()==false)
    {
        SQL=QString("Time>='%1'").arg(timeStart);//start<?
    }
    else if(ui->radioButton_timestart->isChecked()==false&&ui->radioButton_timeEnd->isChecked()==true)
    {
        SQL=QString("Time<='%2'").arg(timeEnd);//?<end
    }
    else{}

    switch(chooseFlag)
    {
    case 0://strain
        model_strain->setFilter(SQL);//设置过滤器
        model_strain->select();//显示
        break;
    case 1://dam
        model_dam->setFilter(SQL);//设置过滤器
        model_dam->select();//显示
        break;
    case 2://all
        model_strain->setFilter(SQL);//设置过滤器
        model_strain->select();//显示

        model_dam->setFilter(SQL);//设置过滤器
        model_dam->select();//显示
        break;
    default:
        break;
    }
}
//SQL语言选择记录
void Widget::on_Button_queryBySimplifiedSql_clicked()//
{
    SQL=ui->lineEdit_queryBySimplifiedSql->text();//获取文本并过滤器过滤

    switch(chooseFlag)
    {
    case 0://strain
        model_strain->setFilter(SQL);//设置过滤器
        model_strain->select();//显示
        break;
    case 1://dam
        model_dam->setFilter(SQL);//设置过滤器
        model_dam->select();//显示
        break;
    case 2://all
        model_strain->setFilter(SQL);//设置过滤器
        model_strain->select();//显示

        model_dam->setFilter(SQL);//设置过滤器
        model_dam->select();//显示
        break;
    default:
        break;
    }
}
//显示所有数据
void Widget::on_button_showAllData_clicked()
{
    switch(chooseFlag)
    {
    case 0://strain
        model_strain->setFilter("");//设置过滤器
        model_strain->select();//显示
        break;
    case 1://dam
        model_dam->setFilter("");//设置过滤器
        model_dam->select();//显示
        break;
    case 2://all
        model_strain->setFilter("");//设置过滤器
        model_strain->select();//显示

        model_dam->setFilter("");//设置过滤器
        model_dam->select();//显示
        break;
    default:
        break;
    }
}
//查询数据表占用空间(M)
void Widget::tableSpace()
{
    QString sql="SELECT (sum(DATA_LENGTH)+sum(INDEX_LENGTH))/1048576 "
                "FROM information_schema.TABLES where TABLE_SCHEMA='ship';";
    QSqlQuery query;
    query.exec(sql);

    query.next();//重要!!!
    double space=query.value(0).toDouble();
    ui->lineEdit_table_space->setText(QString("%1 M").arg(space));

    sql="select count(*) from shiphealth";
    query.exec(sql);
    query.next();
    space=query.value(0).toInt();
    ui->lineEdit_shiphealth_rowcount->setText(QString("%1 行").arg(space));

    sql="select count(*) from realtimestrain";
    query.exec(sql);
    query.next();
    space=query.value(0).toInt();
    ui->lineEdit_strain_rowcount->setText(QString("%1行").arg(space));


    query.exec("select sum(dam) from shiphealth;");
    query.next();
    space=query.value(0).toDouble();
    ui->lineEdit_dam_much->setText(QString("%2%").arg(100*space));
}
//数据表自动刷新,滚动条保持在最底部
void Widget::tableAutoUpdate()
{
    switch(chooseFlag)
    {
    case 0:
        model_strain->select();//显示
        ui->tableView_strain->scrollToBottom();
        break;
    case 1:
        model_dam->select();//显示
        ui->tableView_dam->scrollToBottom();
        break;
    case 2:
        model_strain->select();//显示
        ui->tableView_strain->scrollToBottom();
        model_dam->select();//显示
        ui->tableView_dam->scrollToBottom();
        break;
    default:
        break;
    }
}
//按下开启\关闭自动更新表的定时器
void Widget::on_button_autoUpdate_clicked()
{
    static int idx=0;//静态变量
    if(idx==0)
    {
        autoUpdate->start();//自动更新定时器 开
        idx=1;
        ui->button_autoUpdate->setText("自动更新:开");
    }
    else
    {
        autoUpdate->stop();//自动更新定时器 关
        idx=0;
        ui->button_autoUpdate->setText("自动更新:关");
    }
}


/*-----------------------页面切换按钮-损伤-设置-----------------------*/
void Widget::on_button_choose_databaseInfo_clicked()
{
    ui->button_choose_databaseInfo->setChecked(true);

    if(ui->button_choose_databaseInfo->isChecked()==true)
    {
        ui->button_choose_query->setChecked(false);
    }
    ui->stackedWidget->setCurrentIndex(0);
}
void Widget::on_button_choose_query_clicked()
{    
    ui->button_choose_query->setChecked(true);

    if(ui->button_choose_query->isChecked()==true)
    {
        ui->button_choose_databaseInfo->setChecked(false);
    }
    ui->stackedWidget->setCurrentIndex(1);
}


/*-----------------------数据库数据筛选按钮-应变-损伤-两者都要-----------------------*/
void Widget::on_button_switch_strain_clicked()
{
    ui->button_switch_strain->setChecked(true);

    if(ui->button_switch_strain->isChecked()==true)
    {
        ui->button_switch_dam->setChecked(false);
        ui->button_switch_strainAndDam->setChecked(false);
    }

    ui->tableView_dam->hide();
    ui->tableView_strain->show();

    chooseFlag=0;
}
void Widget::on_button_switch_dam_clicked()
{
    ui->button_switch_dam->setChecked(true);

    if(ui->button_switch_dam->isChecked()==true)
    {
        ui->button_switch_strain->setChecked(false);
        ui->button_switch_strainAndDam->setChecked(false);
    }

    ui->tableView_strain->hide();
    ui->tableView_dam->show();

    chooseFlag=1;
}
void Widget::on_button_switch_strainAndDam_clicked()
{
    ui->button_switch_strainAndDam->setChecked(true);

    if(ui->button_switch_strainAndDam->isChecked()==true)
    {
        ui->button_switch_strain->setChecked(false);
        ui->button_switch_dam->setChecked(false);
    }

    ui->tableView_dam->show();
    ui->tableView_strain->show();

    chooseFlag=2;
}


/*-----------------------导出数据相关-----------------------*/
//获取保存路径
void Widget::on_Button_enduce_path_clicked()
{
    QString path=QFileDialog::getExistingDirectory(this,"test","/");

    //验证非空
    if(path.isEmpty()==true)
    {
        QMessageBox::warning(this,"提醒","路径不能为空");
        return;
    }
    path.append("/");

    qDebug()<<"path:"<<path;

    ui->lineedit_educe_path->setText(path);
}
//导出选中的数据
void Widget::on_Button_educe_clicked()
{
    //校验是否为空
    if(ui->lineEdit_educe_columns->text().isEmpty()==true)//校验导出列
    {
        QMessageBox::warning(this,"提醒","导出列不能为空");
        return;
    }

    if(ui->lineedit_educe_path->text().isEmpty()==true)//校验导出路径
    {
        QMessageBox::warning(this,"提醒","路径不能为空");
        return;
    }

    if(ui->lineedit_educe_filename->text().isEmpty()==true)//校验导出文件名
    {
        QMessageBox::warning(this,"提醒","文件名不能为空");
        return;
    }

    //获取导出表名
    //    QString table;//要导出的表
    //    switch(ui->comboBox_educe_table->currentIndex())
    //    {
    //    case 0:
    //        table="realtimestrain";
    //        break;
    //    case 1:
    //        table="shiphealth";
    //        break;
    //    case 2:
    //        table="user";
    //        break;
    //    default:
    //        break;
    //    }

    //获取导出格式
    //    QString formt;
    //    switch(ui->comboBox_educe_formt->currentIndex())
    //    {
    //    case 0:
    //        formt=".csv";
    //        break;
    //    case 1:
    //        formt=".txt";
    //        break;
    //    case 2:
    //        formt=".sql";
    //        break;
    //    default:
    //        break;
    //    }


    //拼接获得导出sql语句
    QString educe;

    if(ui->lineEdit_educe_filter->text().isEmpty()==true)
    {
        educe=QString("select %1 from %2 into outfile '%3%4%5'")
                .arg(ui->lineEdit_educe_columns->text())//要导出的列
                .arg(ui->comboBox_educe_table->currentText())//要导出的表
                .arg(ui->lineedit_educe_path->text())//导出路径
                .arg(ui->lineedit_educe_filename->text())//导出文件名
                .arg(ui->comboBox_educe_formt->currentText());//导出格式
    }
    else
    {
        educe=QString("select %1 from %2 where %3 into outfile '%4%5%6'")
                .arg(ui->lineEdit_educe_columns->text())//要导出的列
                .arg(ui->comboBox_educe_table->currentText())//要导出的表
                .arg(ui->lineEdit_educe_filter->text())//导出过滤条件
                .arg(ui->lineedit_educe_path->text())//导出路径
                .arg(ui->lineedit_educe_filename->text())//导出文件名
                .arg(ui->comboBox_educe_formt->currentText());//导出格式
    }

    qDebug()<<"导出SQL语句："<<educe;

    QSqlQuery query;
    query.exec(educe);
}
//打开path文件夹
void Widget::on_Button_open_path_clicked()
{
    QString path=ui->lineedit_educe_path->text();
    path.replace("/","\\");
    QString run=QString("explorer.exe /open,%1").arg(path);
    QProcess::startDetached(run);
}

/*-----------------------导入数据相关-----------------------*/
//获取导入文件路径
void Widget::on_Button_leadFile_clicked()
{
    QString file=QFileDialog::getOpenFileName(this,"选择导入文件","/");
    //验证非空
    if(file.isEmpty()==true)
    {
        QMessageBox::warning(this,"提醒","文件名不能为空");
        return;
    }
    ui->lineedit_leadFile->setText(file);//
}
//导入
void Widget::on_Button_lead_clicked()
{
    QString run;
    run=QString("LOAD DATA LOCAL INFILE '%1' INTO TABLE %2")
            .arg(ui->lineedit_leadFile->text())
            .arg(ui->comboBox_lead_table->currentText());
    qDebug()<<"lead:"<<run;
    QSqlQuery query;
    query.exec(run);
}



