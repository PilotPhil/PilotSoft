1.qss添加入资源文件中
2.
```c++
QFile qssFile(":/styleSheet.css");//资源文件":/css.qss"
qssFile.open(QFile::ReadOnly);
if(qssFile.isOpen())
{
    QString qss = QLatin1String(qssFile.readAll()); //读取
    qApp->setStyleSheet(qss);  //设置
    qssFile.close();
}
```

实例：
```c++
void FATIGUE::loadQSS()
{
//    QFile qssFile(":/AMOLED.qss");
    QFile qssFile(":/Aqua.qss");
//    QFile qssFile(":/MacOS.qss");
//    QFile qssFile(":/Ubuntu.qss");
    qssFile.open(QFile::ReadOnly);

    if(qssFile.isOpen())
    {
        QString qss = QLatin1String(qssFile.readAll()); //读取
        qApp->setStyleSheet(qss);  //设置
        qssFile.close();//记得关闭文件
    }
}
```