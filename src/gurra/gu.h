#ifndef GU_H
#define GU_H

#include <QtQml>
#include "include.h"

namespace Gurra {


class Gu : public QObject
{
    Q_OBJECT

public:
    Gu(){}

    static void registerTypes(){

        qmlRegisterType<Gurra::Rest>("Org.Yasser.Gurra", 1, 0, "Rest");
        qmlRegisterType<Gurra::RestUploader>("Org.Yasser.Gurra", 1, 0, "RestUploader");
        qmlRegisterType<Gurra::RestConsumer>("Org.Yasser.Gurra", 1, 0, "RestConsumer");
        qmlRegisterType<Gurra::RestConsumer2>("Org.Yasser.Gurra", 1, 0, "RestConsumer2");
        qmlRegisterType<Gurra::RestConsumer3>("Org.Yasser.Gurra", 1, 0, "RestConsumer3");
        qmlRegisterType<Gurra::RestConsumer3>("Org.Yasser.Gurra", 1, 0, "RestConsumer3");
        qmlRegisterType<Gurra::FileIO>("Org.Yasser.Gurra", 1, 0, "FileIO");
        qmlRegisterType<Gurra::RestModel>("Org.Yasser.Gurra", 1, 0, "RestModel");
        qmlRegisterType<QStringListModel>("Org.Yasser.Gurra", 1, 0, "QStringListModel");
    }

public slots:

    static QString timeAgo(QString timestamp){
        return timeAgo(QDateTime::fromString(timestamp, "dd/MM/yyyy hh:mm:ss").toMSecsSinceEpoch());
    }
    static QString timeAgo(QDateTime timestamp){
        return timeAgo(timestamp.toMSecsSinceEpoch());
    }

    //https://github.com/minixxie/wpp-qt/blob/master/src/wpp/qt/TimeAgo.cpp
    static QString timeAgo(qint64 timestamp)
    {
        qint64 currentTimestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();

        bool isFuture = false;
        qint64 secDiff = 0;

        if ( timestamp > currentTimestamp )//future
        {
            isFuture = true;
            secDiff = (timestamp - currentTimestamp) / 1000;
        }
        else if ( timestamp < currentTimestamp )//past
        {
            isFuture = false;
            secDiff = (currentTimestamp - timestamp) / 1000;
        }
        else//the same
        {
            return QString(tr("Just now"));
        }

        QString ret;

        if ( secDiff > 365*24*60*60 )//longer than 1 year
        {
            int years = secDiff / (365*24*60*60);
            if ( isFuture )
            {
                ret = tr("%1 years in the future").arg(years);
            }
            else
            {
                ret = tr("%1 years ago").arg(years);
            }
        }
        else if ( secDiff <= 365*24*60*60 && 30*24*60*60 < secDiff )//shorter than 1 year and longer than 1 month
        {
            int months = secDiff / (30*24*60*60);
            if ( isFuture )
            {
                ret = tr("%1 months in the future").arg(months);
            }
            else
            {
                ret = tr("%1 months ago").arg(months);
            }
        }
        else if ( secDiff <= 30*24*60*60 && 24*60*60 < secDiff )//shorter than 1 month and longer than 1 day
        {
            int days = secDiff / (24*60*60);
            if ( isFuture )
            {
                ret = tr("%1 days in the future").arg(days);
            }
            else
            {
                ret = tr("%1 days ago").arg(days);
            }
        }
        else if ( secDiff <= 24*60*60 && 60*60 < secDiff )//shorter than 1 day and longer than 1 hour
        {
            int hours = secDiff / (60*60);
            if ( isFuture )
            {
                ret = tr("%1 hours in the future").arg(hours);
            }
            else
            {
                ret = tr("%1 hours ago").arg(hours);
            }
        }
        else if ( secDiff <= 60*60 && 60 < secDiff )//shorter than 1 hour and longer than 1 minute
        {
            int minutes = secDiff / (60);
            if ( isFuture )
            {
                ret = tr("%1 minutes in the future").arg(minutes);
            }
            else
            {
                ret = tr("%1 minutes ago").arg(minutes);
            }
        }
        else if ( secDiff <= 60 )//shorter than 1 minute
        {
            if ( isFuture )
            {
                ret = tr("less than 1 minute in the future");
            }
            else
            {
                ret = tr("less than 1 minute ago");
            }
        }
        return ret;
    }
};

}

#endif // GU_H
