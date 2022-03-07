#ifndef TABLE_UI_H
#define TABLE_UI_H

#include <QWidget>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QFont>

namespace Ui {
class Table_UI;
}

class Table_UI : public QWidget
{
    Q_OBJECT

public:
    explicit Table_UI(QWidget *parent = 0);
    ~Table_UI();

    void updateTable(QVector<qreal> *AMP, QVector<qreal> *AVG, QVector<qreal> *ultraStress, QVector<qreal> *Modified, QVector<qreal> *Damage);

private:
    Ui::Table_UI *ui;

    QStandardItemModel *theModel;//模型
    QItemSelectionModel *theSelection;//
    QStringList verticalHeader;//垂直表头

    QStandardItem *aItem;


};

#endif // TABLE_UI_H
