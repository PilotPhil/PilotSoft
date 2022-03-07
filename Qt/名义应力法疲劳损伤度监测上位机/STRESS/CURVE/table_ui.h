#ifndef TABLE_H
#define TABLE_H

#include <QWidget>
#include <QStandardItemModel>
#include <QItemSelectionModel>

namespace Ui {
class Table_UI;
}

class Table_UI : public QWidget
{
    Q_OBJECT

public:
    explicit Table_UI(QWidget *parent = 0);
    ~Table_UI();

public slots:
    void updateTable(QVector<qreal> *AMP, QVector<qreal> *AVG, QVector<qreal> *ultraStress, QVector<qreal> *Modified, QVector<qreal> *Damage);

private:
    Ui::Table_UI *ui;

    QStandardItemModel *theModel;//模型
    QItemSelectionModel *theSelection;//

    QStringList verticalHeader;
};

#endif // TABLE_H
