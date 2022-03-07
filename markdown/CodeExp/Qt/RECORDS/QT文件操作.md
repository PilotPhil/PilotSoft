### 1.创建文件
```c++
QFile file( strPath );
if ( file.exists())
{
        return true;
}
file.open( QIODevice::WriteOnly );
file.close();
```
 
### 2.CSV
xls文件是Excel电子表格的文件格式，而csv是一种比较通用的文件格式，xls文件只能用Excel才能打开，而csv文件可以用Excel、记事本、文本编辑器打开。

大体思路，读取csv文件中的数据，就是先以换行符进行断开，这样就能获取到每行的数据，然后再以半角的逗号断开，这样就能获取到具体每个单元格中的数据，话不多说，上代码：

```c++
QFileDialog* fd = new QFileDialog(this)；//创建打开文件对话框
QString fileName = fd->getOpenFileName(this,tr("Open File"),"/home",tr("Excel(*.csv)"));
if(fileName == "")
      return;
QDir dir = QDir::current();
QFile file(dir.filePath(fileName));
if(!file.open(QIODevice::ReadOnly))
     qDebug()<<"OPEN FILE FAILED";
QTextStream * out = new QTextStream(&file);//文本流
QStringList tempOption = out->readAll().split("\n");//每行以\n区分
for(int i = 0 ; i < tempOption.count() ; i++)
{
     QStringList tempbar = tempOption.at(i).split(",");//一行中的单元格以，区分
     ...//省略具体对数据的操作
}
file.close();//操作完成后记得关闭文件
```

实例：
```c++
//读取：
void DOCSV::receiveFileNameRead(QString fileName)
{
    data->clear();//先清除成员元素
    QDir dir = QDir::current();
    QFile file(dir.filePath(fileName));

    if(!file.open(QIODevice::ReadOnly))
         qDebug()<<"OPEN FILE FAILED";
    else
        qDebug()<<"OPEN FILE SUCESSED";
    QTextStream * out = new QTextStream(&file);//文本流
    QStringList tempOption = out->readAll().split("\n");//每行以\n区分
    qDebug()<<tempOption.size();
    for(int i = 0 ; i < tempOption.count() ; i++)
    {
         qDebug()<<tempOption.at(i);
         data->append(tempOption.at(i).toDouble());//逐个拷贝内容
    }
    file.close();//操作完成后记得关闭文件
    sendCsvData(*data);//发送读取到的数据
}

//写入：
void MYTABLE::save2Csv()
{
    QFile data("ExeRecord.csv");// 以上两行用时间戳作为文件名
    if(data.open(QFile::WriteOnly | QFile::Truncate))// 打开文件
    {
        QTextStream out(&data);    // 输入流

        int row=model->rowCount();
        for(int i=0;i<row;i++)
        {
            out<<model->item(i,0)->text()<<","<<model->item(i,1)->text()<< "\n";
        }
    }
    data.close();
}
```

