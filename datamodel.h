#ifndef DATAMODEL_H
#define DATAMODEL_H
#include "database.h"
#include <QObject>
#include <QAbstractTableModel>
#include <QString>
#include <vector>


class DataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DataModel(QObject *parent = 0);
public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void ShowDatas(int currpage);
private:
    std::vector<Info_t> m_data;
    int m_RowCount;
};

#endif // DATAMODEL_H
