#include "cmd.h"

CMD::CMD(QObject *parent) : QObject(parent)
{
    cmd=new QProcess();

    connect(cmd,&QProcess::readyReadStandardOutput,this,&CMD::sendCmdOutput);
    connect(cmd,&QProcess::readyReadStandardError,this,&CMD::sendCmdOutput);
}

void CMD::runCommand(QString command)
{
    cmd->start("windeployqt "+command);//启动终端(Windows下改为cmd)
    cmd->waitForStarted();//等待启动完成
    cmd->write("ls\n");//向终端写入“ls”命令，注意尾部的“\n”不可省略
}

QString CMD::cmdOutput()
{
    return cmd->readAllStandardOutput().data();
}

QString CMD::cmdErrors()
{
    return cmd->readAllStandardError().data();
}
