#ifndef STRESS_H
#define STRESS_H

#include <QMainWindow>
#include <QThread>

#include "COM/serial_ui.h"
#include "COM/serialread_thread.h"

#include "UserInterface/linechart_ui.h"
#include "UserInterface/table_ui.h"
#include "QCustomPlot/qcustomplot.h"

#include "ALGORITHM/algorithm_ui.h"
#include "ALGORITHM/algorithm_thread.h"



namespace Ui {
class STRESS;
}

class STRESS : public QMainWindow
{
    Q_OBJECT

public:
    explicit STRESS(QWidget *parent = 0);
    ~STRESS();

private slots:
    void on_action_triggered();

    void on_action_2_triggered();

    void on_pushButton_clicked();

    void on_refresh_continous_clicked();

    void on_refresh_repete_clicked();

private:
    Ui::STRESS *ui;

    Serial_UI *serial_ui;
    SerialRead_Thread *serialRead_thread;
    QThread *thread1;

    LineChart_UI *lineChart;

    Algorithm_UI *algorithm_ui;
    Algorithm_Thread *algorithm_thread;
    QThread *thread2;

    Table_UI *table_ui;

signals:
    void sendLineChartAxisParam(int xMin,int xMax,int yMin,int yMax);
    void sendLineChartRefreshMode(int mode);
};

#endif // STRESS_H
