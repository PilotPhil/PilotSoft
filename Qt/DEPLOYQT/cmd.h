#ifndef CMD_H
#define CMD_H

#include <QObject>
#include <QProcess>

class CMD : public QObject
{
    Q_OBJECT

private:
    QProcess * cmd;

public:
    explicit CMD(QObject *parent = nullptr);

signals:
    //信号转发
    void sendCmdOutput();//发送输出信号
    void sendCmdErrors();//发送错误信号

public slots:
    void runCommand(QString command);//运行命令
    QString cmdOutput();//获取运行命令后输出
    QString cmdErrors();//获取运行命令可能出现的错误
};

#endif // CMD_H
