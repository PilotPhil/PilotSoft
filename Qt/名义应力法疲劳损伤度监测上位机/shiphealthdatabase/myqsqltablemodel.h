#ifndef MYQSQLTABLEMODEL_H
#define MYQSQLTABLEMODEL_H

#include <QSqlTableModel>
#include <QObject>
#include <QDateTime>

class myQsqlTableModel : public QSqlTableModel
{
public:
    myQsqlTableModel();

    QVariant data(const QModelIndex &idx, int role) const;
};

#endif // MYQSQLTABLEMODEL_H
