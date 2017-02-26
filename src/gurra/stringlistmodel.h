#ifndef STRINGLISTMODEL_H
#define STRINGLISTMODEL_H

#include <QtCore>

class StringListModel : public QAbstractListModel
{
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_DISABLE_COPY(StringListModel)
    Q_OBJECT

public:
    explicit StringListModel(QObject* parent = 0);
    StringListModel(const QList<QString>& initList, QObject* parent = 0);
    virtual ~StringListModel();

private:
    enum Roles{
        ModelDataRole = Qt::UserRole+1
    };

public:
    int count() const;

public:

    void append(const QString& item);
    void append(const QList<QString>& items);

    void insert(int index, const QString& item);
    void insert(int index, const QList<QString>& items);

    void clear();

    bool removeOne(const QString& item);
    int removeAll(const QString& item);
    void removeAt(int index);
    QList<QString> list() const;

signals:
    void countChanged();

public:
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

private:
    QList<QString> m_data;
};

#endif // STRINGLISTMODEL_H
