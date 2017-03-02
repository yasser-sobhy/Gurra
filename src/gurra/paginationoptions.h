#ifndef PAGINATIONOPTIONS_H
#define PAGINATIONOPTIONS_H
#include <QJsonObject>

struct PaginationOptions
{
    PaginationOptions(){}

    PaginationOptions(QJsonObject &obj){

        QJsonObject o = obj.value("pagination").toObject();
        if(o.isEmpty()) return;

        since = o.value("since").toDouble();
        limit = o.value("limit").toInt();
        page = o.value("page").toInt();
        before = o.value("before").toString();
        after = o.value("after").toString();
    }

    QString write(){
        return "since=" + QString::number(since)
                + ",limit=" + QString::number(limit)
                + ",page=" + QString::number(page)
                + ",before=" + before
                + ",after=" + after;
    }

    qint64 since; // last record timestamp
    int limit;
    int page;
    QString before; // puul-to-refresh
    QString after; // fetch more
};

#endif // PAGINATIONOPTIONS_H
