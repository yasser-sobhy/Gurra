#ifndef STRINGLISTMODEL_H
#define STRINGLISTMODEL_H

#include <QAbstractListModel>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QString>
#include <QStringListModel>

class StringListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit StringListModel(QObject* parent = 0);
    StringListModel(const QList<QString>& initList, QObject* parent = 0);
    virtual ~StringListModel();

    void append(const QString item);
    void append(const QList<QString>& items);

    void insert(int index, const QString& item);
    void insert(int index, const QList<QString>& items);

    void clear();

    bool removeOne(const QString& item);
    int removeAll(const QString& item);
    void removeAt(int index);
    QStringList list() const;

    virtual QHash<int, QByteArray> roleNames() const override
    {
        return roles;
    }

    Qt::ItemFlags flags(const QModelIndex &index) const
    {
        if (!index.isValid())
            return Qt::ItemIsEnabled;

        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    }

    QVariant headerData(int section, Qt::Orientation orientation,
                                         int role) const
    {
        if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal)
            return QString("Column %1").arg(section);
        else
            return QString("Row %1").arg(section);
    }


    virtual int rowCount(const QModelIndex &) const;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

    bool setData(const QModelIndex &index, const QVariant &value,
                  int role = Qt::EditRole);
private:
    QHash<int, QByteArray> roles;

    QStringList m_data;
};

#endif // STRINGLISTMODEL_H
