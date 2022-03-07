#ifndef SERIAL_H
#define SERIAL_H

#include <QWidget>
#include <QDebug>
#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>

#include "serialsetting_thread.h"
#include "serialsetting_ui.h"

#include "mychart.h"

namespace Ui {
class serial;
}

class serial : public QWidget
{
    Q_OBJECT

public:
    explicit serial(QWidget *parent = nullptr);
    ~serial();

    void ReceiveSerialData(QString msg);


private:
    Ui::serial *ui;

    SerialSetting_ui *ui_serialSetting;
    SerialSetting_thread *thread_serialSetting;
    QThread *thread1;

    myChart *chart;

signals:
    void sendData(qreal data);

};

#endif // SERIAL_H
