#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "QSqlTableModel"
#include "myqsqltablemodel.h"

#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>
#include <QCompleter>

#include <QTimer>

#include <QFile>
#include <QTextStream>

#include <QFileDialog>
#include <QDialog>
#include <QMessageBox>

#include <QProcess>

#include <QtWin>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void init_window();//窗口初始化
    void init_dataBase();//数据库初始化
    void init_modelView();//model-view初始化
    void tableSpace();//显示数据表大小
    void tableAutoUpdate();//数据表自动更新

private slots:

    //查找
    void on_Button_queryByTime_clicked();//按时间查找
    void on_Button_queryBySimplifiedSql_clicked();//按简化版SQL查询

    //查询query
    void on_button_showAllData_clicked();//显示所有数据按钮
    void on_button_autoUpdate_clicked();//自动更新数据槽函数

    //页面切换
    void on_button_choose_databaseInfo_clicked();//损伤度界面
    void on_button_choose_query_clicked();//设置界面

    //数据表的选择
    void on_button_switch_strain_clicked();//选择应变数据
    void on_button_switch_dam_clicked();//选择损伤数据
    void on_button_switch_strainAndDam_clicked();//选择两者


    //导出
    void on_Button_enduce_path_clicked();//设置路径槽函数
    void on_Button_educe_clicked();//导出数据槽函数
    void on_Button_open_path_clicked();//打开导出的文件夹

    //导入
    void on_Button_leadFile_clicked();//找到要导入的文件
    void on_Button_lead_clicked();//导入按钮

private:
    Ui::Widget *ui;

    QSqlDatabase db;//数据库
    QSqlDatabase db_MYSQL;//
    QSqlQuery *sqlQuery;

    //三个模型
    myQsqlTableModel *model_dam;
    myQsqlTableModel *model_strain;
    myQsqlTableModel *model_user;
    QSqlTableModel *model_user_manage;

    //两个定时器
    QTimer *mytimer;
    QTimer *autoUpdate;

    QString SQL;//执行的SQL语句

    //数据库筛选选择//查询设置标志位
    int chooseFlag;
};

#endif // WIDGET_H
