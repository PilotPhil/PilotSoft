#include "deployqt.h"
#include "ui_deployqt.h"

DEPLOYQT::DEPLOYQT(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DEPLOYQT)
{
    ui->setupUi(this);
    this->setWindowTitle("windeployqt ui");

    cmd=new CMD(this);
    //信号转发
    connect(cmd,&CMD::sendCmdOutput,this,&DEPLOYQT::receiveOutPut);
    connect(cmd,&CMD::sendCmdErrors,this,&DEPLOYQT::receiveError);

    //table
    myTable=new MYTABLE();
    QGridLayout * GL=new QGridLayout();
    ui->widget->setLayout(GL);
    GL->addWidget(ui->PB_chooseExe,0,0);
    GL->addWidget(myTable,1,0);
    connect(this,&DEPLOYQT::sendExeAddress,myTable,&MYTABLE::receiveExeAddress);

    connect(myTable,&MYTABLE::sendRecordExeAddress,cmd,&CMD::runCommand);
    connect(myTable,&MYTABLE::sendRecordExeAddress,&MYTABLE::receiveExeAddress);
}

DEPLOYQT::~DEPLOYQT()
{
    delete ui;
}

void DEPLOYQT::receiveOutPut()
{
    ui->TE_output->append(cmd->cmdOutput());
    ui->TE_output->append("DONE!");
}

void DEPLOYQT::receiveError()
{
    ui->TE_errors->append(cmd->cmdErrors());
}

void DEPLOYQT::on_PB_chooseExe_clicked()
{
    QString address = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("可执行文件 (*.exe)"));
    if(address!="")
    {
        sendExeAddress(address);
        cmd->runCommand(address);//不要忘了空格
    }
}
