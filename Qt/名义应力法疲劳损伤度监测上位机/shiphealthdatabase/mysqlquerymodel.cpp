#include "mysqlquerymodel.h"

mySqlQueryModel::mySqlQueryModel()
{

}

QVariant mySqlQueryModel::data(const QModelIndex &item, int role) const
{
    if(!item.isValid())
        return QVariant();

    QVariant vt=QSqlQueryModel::data(item,role);

    if(QVariant::DateTime==vt.type())
        return vt.toDate()
}
