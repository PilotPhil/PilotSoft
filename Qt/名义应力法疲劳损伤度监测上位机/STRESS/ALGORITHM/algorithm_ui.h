#ifndef ALGORITHM_UI_H
#define ALGORITHM_UI_H

#include <QWidget>
#include <QDebug>
#include <QtMath>

namespace Ui {
class Algorithm_UI;
}

class Algorithm_UI : public QWidget
{
    Q_OBJECT

public:
    explicit Algorithm_UI(QWidget *parent = 0);
    ~Algorithm_UI();

public slots:
    void getAlgorithmParam();

private:
    Ui::Algorithm_UI *ui;

    qreal AD;
    qreal Bridge;
    qreal K;
    qreal Vref;
    qreal Gain;
    qreal yangs;
    qreal loadNum;
    qreal ultraStress;
    qreal S_N;
    qreal V2S;

    QList<qreal> allParam;

signals:
    void sendAlgorithm(QList<qreal>);

};

#endif // ALGORITHM_UI_H
