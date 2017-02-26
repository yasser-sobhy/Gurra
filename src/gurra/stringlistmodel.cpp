#include "stringlistmodel.h"

StringListModel::StringListModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

StringListModel::StringListModel(const QList<QString> &initList, QObject *parent) :
    QAbstractListModel(parent)
{
    m_data.append(initList);
}

StringListModel::~StringListModel()
{}

int StringListModel::count() const
{
    return m_data.count();
}

void StringListModel::append(const QString &item)
{
    beginInsertRows(QModelIndex(), m_data.count(), m_data.count());
    m_data.append(item);
    endInsertRows();
    emit countChanged();
}

void StringListModel::append(const QList<QString> &items)
{
    if(items.count() == 0) return;

    beginInsertRows(QModelIndex(), m_data.count(), m_data.count()+items.count()-1);
    m_data.append(items);
    endInsertRows();
    emit countChanged();
}

void StringListModel::clear()
{
    beginResetModel();
    m_data.clear();
    endResetModel();
}

void StringListModel::insert(int index, const QString &item)
{
    beginInsertRows(QModelIndex(), index, index+1);
    m_data.insert(index, item);
    endInsertRows();
    emit countChanged();
}

void StringListModel::insert(int index, const QList<QString> &items)
{
    if(items.count() == 0) return;
    index = qMax(0, index);
    Q_ASSERT(index >= m_data.count());

    beginInsertRows(QModelIndex(), index, index+items.count());
    for(int i = 0, k = index; i < items.count(); ++i, ++k)
        m_data.insert(k, items.at(i));
    endInsertRows();
    emit countChanged();
}

bool StringListModel::removeOne(const QString &item)
{
    int row = m_data.indexOf(item);
    if(row < 0) return false;

    beginRemoveRows(QModelIndex(), row, row);
    m_data.removeAt(row);
    endRemoveRows();
    emit countChanged();
    return true;
}

int StringListModel::removeAll(const QString &item)
{
    if(!m_data.contains(item)) return 0;

    beginResetModel();
    int resultado = m_data.removeAll(item);
    endResetModel();
    emit countChanged();

    return resultado;
}

void StringListModel::removeAt(int index)
{
    if(index < 0 || index >= count()) return;

    beginRemoveRows(QModelIndex(), index, index);
    m_data.removeAt(index);
    endRemoveRows();
    emit countChanged();
}

QList<QString> StringListModel::list() const
{
    return QList<QString>(m_data);
}

int StringListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return count();
}

QVariant StringListModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() == false) return QVariant();
    if(index.row() < 0 || index.row() >= count()) return QVariant();

    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        return m_data.at(index.row());
    default:
        return QVariant();
    }
}
