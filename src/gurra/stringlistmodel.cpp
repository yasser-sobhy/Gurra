#include "stringlistmodel.h"

StringListModel::StringListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    roles.insert(555, "text");
}

StringListModel::StringListModel(const QList<QString> &initList, QObject *parent) :
    QAbstractListModel(parent)
{
    m_data.append(initList);
}

StringListModel::~StringListModel()
{}

void StringListModel::append(const QString item)
{
    int row = m_data.count();

    qDebug() << row;
    beginInsertRows(QModelIndex(), row, row);
    m_data.append(item);
    qDebug() << "end" << row;
    endInsertRows();
}

void StringListModel::append(const QList<QString> &items)
{
    if(items.count() == 0) return;

    beginInsertRows(QModelIndex(), m_data.count(), m_data.count()+items.count()-1);
    m_data.append(items);
    endInsertRows();
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
}

bool StringListModel::removeOne(const QString &item)
{
    int row = m_data.indexOf(item);
    if(row < 0) return false;

    beginRemoveRows(QModelIndex(), row, row);
    m_data.removeAt(row);
    endRemoveRows();
    return true;
}

int StringListModel::removeAll(const QString &item)
{
    if(!m_data.contains(item)) return 0;

    beginResetModel();
    int resultado = m_data.removeAll(item);
    endResetModel();

    return resultado;
}

void StringListModel::removeAt(int index)
{
    if(index < 0 || index >= m_data.count()) return;

    beginRemoveRows(QModelIndex(), index, index);
    m_data.removeAt(index);
    endRemoveRows();
}

QStringList StringListModel::list() const
{
    return m_data;
}

int StringListModel::rowCount(const QModelIndex &) const
{
    qDebug() << "rowCount" << m_data.count();;
    return m_data.count();
}

QVariant StringListModel::data(const QModelIndex &index, int role) const
{
    qDebug() << "f data";

    if(!index.isValid()) return QVariant();
    if(index.row() < 0 || index.row() >= m_data.count()) return QVariant();

    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        return m_data.at(index.row());
    default:
        return QVariant();
    }
}


bool StringListModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    qDebug() << "insertRows";
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        m_data.insert(position, "");
    }

    endInsertRows();
    return true;
}

 bool StringListModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        m_data.removeAt(position);
    }

    endRemoveRows();
    return true;
}

 bool StringListModel::setData(const QModelIndex &index,
                               const QVariant &value, int role)
 {
     if (index.isValid() && role == Qt::EditRole) {

         m_data.replace(index.row(), value.toString());
         emit dataChanged(index, index);
         return true;
     }
     return false;
 }
