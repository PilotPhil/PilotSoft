```c++
//设置时间显示的字体
QPalette palette;
palette.setColor(QPalette::WindowText,Qt::red);
ui->label_CurrentTime->setPalette(palette); 

//定时器
QTimer *CurrentTime = new QTimer(this);
CurrentTime->start(0); 

//使用定时器信号槽，尽快更新时间的显示
connect(CurrentTime,&QTimer::timeout,
[=]()
{
    QDateTime current_time = QDateTime::currentDateTime(); 
    //显示时间，格式为：年-月-日 时：分：秒 周几
    QString StrCurrentTime = current_time.toString("yyyy-MM-dd hh:mm:ss ddd"); 
    
    //时间显示格式可自由设定，如hh:mm ddd 显示 时：分 周几 
    //具体格式见函数QString QDateTime::​toString(const QString & format) const
    
    ui->label_CurrentTime->setText(StrCurrentTime); 
});
```