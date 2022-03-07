#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "RainFlowCount.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    RainFlowCount rf;
};

#endif // WIDGET_H
