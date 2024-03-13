#include "datamodel.h"
#include <QDebug>

DataModel::DataModel(QObject *parent) : QAbstractTableModel(parent),
    m_RowCount(0)
{
    Database::GetInstance().InitDB();
}

int DataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_data.size();
}

int DataModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 2;
}

QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }
    if(role == Qt::DisplayRole)
    {
        switch (index.column()) {
        case 0:
            return m_data.at(index.row()).user;
        case 1:
            return m_data.at(index.row()).age;
        default:
            break;
        }
    }
    return QVariant();
}

void DataModel::ShowDatas(int currpage)
{
    beginRemoveRows(QModelIndex(),0,m_data.size() - 1);
    m_data.clear();
    endRemoveRows();
    Database::GetInstance().SelDatas(currpage,m_data);
    beginInsertRows(QModelIndex(),0,m_data.size() - 1);
    endInsertRows();
}

