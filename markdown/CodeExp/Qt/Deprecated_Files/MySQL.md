### 1.使用数据库 pro文件中加入==QT  +=sql==

### 复制mysql驱动文件
==找到mysql安装文件夹\lib\下的libmysql.dll，复制到Qt\bin下==
![image](https://note.youdao.com/yws/res/244/B9A0B0E14F1C4C2EAEE6CA409A299D99)

==**注意：Qt与mysql需要同为32位或64位**==

### 2.打印Qt支持的数据库驱动
```c++
qDebug()<<QSqlDatabase::drivers();
```

### 3.添加mysql数据库
```c++
QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
```

### 4.连接数据库
```sql
db.setHostName("127.0.0.1");//数据库服务器IP
db.setUserName("root");//数据库用户名
db.setPassword("1126");//数据库密码
db.setDatabaseName("test");//使用哪个数据库
```

### 5.打开数据库
```c++
    if(db.open()==false)//如果打开失败
    {
        QMessageBox::warning(this,"数据库打开失败",db.lastError().text());//如果打开失败，弹出waring窗口，提示最近的错误信息
        return;
    }
```

### 6.数据库插入
- 普通
```c++
QSqlQuery query;
query.exec("INSERT INTO student(id,name,age,score) VALUES(1,'tom',18,59);");
```

- 格式化字符串
```c++
QSqlQuery query;
QString todo;
todo=todo.sprintf("INSERT INTO student VALUES(%d,'%s',%d,%d);",3,"jerry",34,100);
query.exec(todo);
```

- 批量插入
  - ODBC风格
  ```c++
    //预处理语句
    query.prepare("INSERT INTO student VALUES(?,?,?,?)");//?相当于占位符
    //给字段内容设置内容list
    QVariantList idList;
    idList<<4<<5<<6;

    QVariantList nameList;
    nameList<<"xiaoa"<<"xiaob"<<"xiaoc";

    QVariantList ageList;
    ageList<<56<<65<<76;

    QVariantList scoreList;
    scoreList<<123<<45<<23;

    //给字段绑定相应的值，按 顺序 绑定
    query.addBindValue(idList);
    query.addBindValue(nameList);
    query.addBindValue(ageList);
    query.addBindValue(scoreList);

    //执行预处理命令
    query.execBatch();
  ```
  
  - oracle风格
  ```c++
    //预处理语句
    //占位符： ：+自定义名字
    query.prepare("INSERT INTO student VALUES(:id,:name,:age,:score)");
    QVariantList idList;
    idList<<7<<8<<9;

    QVariantList nameList;
    nameList<<"xiaoe"<<"xiaof"<<"xiaog";

    QVariantList ageList;
    ageList<<562<<45<<11;

    QVariantList scoreList;
    scoreList<<23<<45<<20;
    //给字段绑定
    query.bindValue(":id",idList);
    query.bindValue(":name",nameList);
    query.bindValue(":age",ageList);
    query.bindValue(":score",scoreList);

    //执行预处理命令
    query.execBatch();
    ```
    
### 7.事务
```c++
void MainWindow::on_delete_clicked()
{
    //获取行编辑内容
    QString name=ui->lineEdit->text();

    //sql语句
    QString sql_delete=QString("delete from student where name ='%1'").arg(name);

    //开启事务
    QSqlDatabase::database().transaction();//获取当前操作的数据库,开启事务

    QSqlQuery query;
    query.exec(sql_delete);//执行
}

void MainWindow::on_commit_clicked()
{
    QSqlDatabase::database().commit();//提交
}

void MainWindow::on_rollback_clicked()
{
    QSqlDatabase::database().rollback();
}
```


### 8.查询
```C++
query.exec("select * from student");
while(query.next())//遍历每一行
{
    //取出当前行的内容
    qDebug()<<query.value(0).toInt()//转化为其原始数据类型
            <<query.value(1).toString()
            <<query.value("age").toInt()
            <<query.value("score").toInt();
}
```

### 数据库可视化model-view
![image](https://note.youdao.com/yws/res/587/3EA9598D7DC74C5F8A98F30D4856B799)

```c++
//头文件
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>

//构造函数
    qDebug()<<QSqlDatabase::drivers();//打印支持的数据库

    //添加mysql数据库
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    //连接数据库
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("1126");
    db.setDatabaseName("test");

    //打开数据库
    if(db.open()==false)
    {
        QMessageBox::warning(this,"数据库打开错误",db.lastError().text());
        return;
    }

    //设置模型
    theModel=new QSqlTableModel(this);
    theModel->setTable("student");

    //将model放入view中
    ui->tableView->setModel(theModel);

    //显示model中数据
    theModel->select();

    //设置显示的水平表头，不干扰数据库内数据
    theModel->setHeaderData(0,Qt::Horizontal,"序号");
    theModel->setHeaderData(1,Qt::Horizontal,"名字");
    theModel->setHeaderData(1,Qt::Horizontal,"年龄");
    theModel->setHeaderData(1,Qt::Horizontal,"得分");

    //设置model编辑模式，手动提交
    theModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //设置tableview中数据不允许修改
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

//功能槽函数

//增加
    //添加空记录
    QSqlRecord record=theModel->record();

    theModel->insertRecord(theModel->rowCount(),record);
    
//确认提交
    theModel->submitAll();
    
//删除
        //获取选中的模型
    QItemSelectionModel *sModel=ui->tableView->selectionModel();
    //取出模型中的索引
    QModelIndexList list=sModel->selectedRows();
    //删除选中的行
    for(int i=0;i<list.count();i++)
    {
        theModel->removeRow(list.at(i).row());
    }
    
//取消
    theModel->revertAll();
    theModel->submitAll();
    
//查找
    //获取查找内容
    QString name=ui->lineEdit->text();

    //组包
    QString sql=QString("name='%1'").arg(name);

    theModel->setFilter(sql);
    theModel->select();
    
```
