#include "myqsqltablemodel.h"

myQsqlTableModel::myQsqlTableModel()
{

}

QVariant myQsqlTableModel::data(const QModelIndex &idx, int role) const
{
    if(!idx.isValid())
        return QVariant();

    QVariant vt=QSqlTableModel::data(idx,role);

    if(QVariant::DateTime==vt.type())
        return vt.toDateTime().toString("yyyy-MM-dd hh:mm:ss");
    return vt;
}
