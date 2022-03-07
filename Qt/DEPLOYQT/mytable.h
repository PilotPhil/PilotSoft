#ifndef MYTABLE_H
#define MYTABLE_H

#include <QWidget>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QFont>
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QDir>

namespace Ui {
class MYTABLE;
}

class MYTABLE : public QWidget
{
    Q_OBJECT

public:
    explicit MYTABLE(QWidget *parent = nullptr);
    ~MYTABLE();

    void receiveExeAddress(QString address);



private slots:
    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::MYTABLE *ui;

    QStandardItemModel *model;
    QItemSelectionModel *selection;
    QStringList horizontalHeader;
    QStandardItem *item;

    void insert2TableNoRepete(QString address);
    void save2Csv();//表格数据写入到csv
    void read4Csv();//从csv读取到表格

signals:
    void sendRecordExeAddress(QString address);
};

#endif // MYTABLE_H
