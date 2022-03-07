0.QTableView自适应填充伸展列宽的基础上 再固定特定某列宽

```
setModel(model);  
horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//所有列都扩展自适应宽度，填充充满整个屏幕宽度
//horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );//根据列内容来定列宽
horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);//对第0列单独设置固定宽度
setColumnWidth(0, 45);//设置固定宽度
```

1. 将表格变为禁止编辑
在默认情况下，表格里的字符是可以更改的，比如双击一个单元格，就可以修改原来的内容，如果想禁止用户的这种操作，让这个表格对用户只读，可以这样：

```c++
tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
//QAbstractItemView.NoEditTriggers是QAbstractItemView.EditTrigger枚举中的一个，下面都是触发修改单元格内容的条件：
QAbstractItemView.NoEditTriggers// 不能对表格内容进行修改
QAbstractItemView.CurrentChanged // .任何时候都能对单元格修改
QAbstractItemView.DoubleClicked // 双击单元格修改
QAbstractItemView.SelectedClicked // 单击已选中的内容修改
QAbstractItemView.AnyKeyPressed // .按下任意键就能修改
QAbstractItemView.AllEditTriggers //.以上条件全包括
```




2. 设置表格为整行选择 

```
tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中的方式
QAbstractItemView.SelectionBehavior枚举还有如下类型：
QAbstractItemView.SelectItems // 选中单个单元格
QAbstractItemView.SelectRows // .选中一行
QAbstractItemView.SelectColumns // 选中一列
```


3.单个选中和多个选中的设置：

```
tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection); //设置为可以选中多个目标
该函数的参数还可以是：
QAbstractItemView.NoSelection //不能选择
QAbstractItemView.SingleSelection //选中单个目标
QAbstractItemView.MultiSelection //选中多个目标
QAbstractItemView.ExtendedSelection QAbstractItemView.ContiguousSelection
```
 的区别不明显，主要功能是正常情况下是单选，但按下Ctrl或Shift键后，可以多选

4. 表格表头的显示与隐藏
对于水平或垂直方法的表头，可以用以下方式进行 隐藏/显示 的设置：
  注意：需要 `#include <QHeaderView>`
```
tableWidget->verticalHeader()->setVisible(false); //隐藏列表头 
tableWidget->horizontalHeader()->setVisible(false); //隐藏行表头
```


5. 对表头文字的字体、颜色进行设置 

 注意：需要 `#include <QHeaderView>`


```
QTableWidgetItem *columnHeaderItem0 = tableWidget->horizontalHeaderItem(0); //获得水平方向表头的Item对象
columnHeaderItem0->setFont(QFont("Helvetica")); //设置字体 
columnHeaderItem0->setBackgroundColor(QColor(0,60,10)); //设置单元格背景颜色 
columnHeaderItem0->setTextColor(QColor(200,111,30)); //设置文字颜色
```


6. 在单元格里加入控件：
`QTableWidget`不仅允许把文字加到单元格，还允许把控件也放到单元格中。比如，把一个下拉框加入单元格，可以这么做：
view plain

```
QComboBox *comBox = new QComboBox(); 
comBox->addItem("Y"); 
comBox->addItem("N"); 
tableWidget->setCellWidget(0,2,comBox);
```

 
7. 单元格设置字体颜色和背景颜色 及字体字符

```
QTableWidgetItem *item = new QTableWidgetItem("Apple"); 
item->setBackgroundColor(QColor(0,60,10)); 
item->setTextColor(QColor(200,111,100)); 
item->setFont(QFont("Helvetica")); 
tableWidget->setItem(0,3,item);
```

另：如果需要对所有的单元格都使用这种字体，则可以使用 `tableWidget->setFont(QFont("Helvetica"));`

8. 设置单元格内文字的对齐方式
这个比较简单，使用newItem.setTextAlignment()函数即可，该函数的参数为单元格内的对齐方式，和字符输入顺序是自左相右还是自右向左。
水平对齐方式有：
Constant Value Description

```
Qt.AlignLeft// Aligns with the left edge.
Qt.AlignRight // Aligns with the right edge.
Qt.AlignHCenter //Centers horizontally in the available space.
Qt.AlignJustify //Justifies the text in the available space.
```


垂直对齐方式：
Constant Value Description

```
Qt.AlignTop // Aligns with the top.
Qt.AlignBottom // Aligns with the bottom.
Qt.AlignVCenter // Centers vertically in the available space.
```

如果两种都要设置，只要用 `Qt.AlignHCenter | Qt.AlignVCenter` 的方式即可 

9. 合并单元格效果的实现：

```
tableWidget->setSpan(0, 0, 3, 1)//其参数为： 要改变单元格的 1行数 2列数 要合并的
```
 3行数 4列数

10. 设置单元格的大小
首先，可以指定某个行或者列的大小

```
tableWidget->setColumnWidth(3,200); 
tableWidget->setRowHeight(3,60);
```




还可以将行和列的大小设为与内容相匹配

```
tableWidget->resizeColumnsToContents(); 
tableWidget->resizeRowsToContents();
```


11. 获得单击单元格的内容 
```c++
QString str = ui->TableWidget->item(row,column)->text();//取出字符串
int num = str.toInt();//转成int
ui->TableWidget->item(row,column)->setText(QString("%1").arg(num));//写入
```

12.获取点击tableview的索引
有此槽函数
```c++
//tableView的点击槽函数，由设计师界面右键tableView、点击转到槽、点击cliked()选项生成
void tableVieShow::on_tableView_student_clicked(const QModelIndex &index)
{
    index.row();//获取行
    index.column();//获取列
}
```

13.tableview中添加控件
```c++
int row = ui->tableWidget_userlist->rowCount(); //获取表格行数
ui->tableWidget_userlist->setRowCount(row+1);  //表格加一行

//添加一个下拉框
QComboBox *comBox = new QComboBox();
comBox->addItem(QObject::tr("female"));
comBox->addItem(QObject::tr("male"));
comBox->setEnabled(true);
ui->tableWidget_userlist->setCellWidget(row,1,comBox);

//添加一个按钮
 QPushButton *button = new QPushButton();
button->setText(tr("scan"));
button->setEnabled(true);
ui->tableWidget_userlist->setCellWidget(row,6,button);

```

14.设置默认行高和列宽
```c++
QTtableView或者QTableWidget的verticalHeader()->setDefaultSectionSize(15)可以设置tableview所有列的默认行高为15。

QTtableView或者QTableWidget的horizontalHeader()->setDefaultSectionSize(15)可以设置tableview所有行的默认列宽为15。
```