#ifndef DEPLOYQT_H
#define DEPLOYQT_H

#include <QWidget>
#include <QProcess>
#include <QMessageBox>
#include <QTextCodec>
#include <QFileDialog>

#include "cmd.h"
#include "mytable.h"

namespace Ui {
class DEPLOYQT;
}

class DEPLOYQT : public QWidget
{
    Q_OBJECT
private:
    Ui::DEPLOYQT *ui;

    CMD * cmd;//命令行对象
    MYTABLE * myTable;//表格

public:
    explicit DEPLOYQT(QWidget *parent = nullptr);
    ~DEPLOYQT();

    void receiveOutPut();
    void receiveError();

signals:
    void sendExeAddress(QString address);

private slots:
    void on_PB_chooseExe_clicked();


};

#endif // DEPLOYQT_H
