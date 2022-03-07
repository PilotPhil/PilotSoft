#ifndef MYSQLQUERYMODEL_H
#define MYSQLQUERYMODEL_H

#include <QObject>
#include <QSqlModel>

class mySqlQueryModel : public QSqlQueryModel
{
public:
    mySqlQueryModel();

    QVariant data(const QModelIndex &item, int role) const;
};

#endif // MYSQLQUERYMODEL_H
