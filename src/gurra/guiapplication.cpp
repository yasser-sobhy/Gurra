#include "guiapplication.h"
#include <QDebug>

using namespace Gurra;

GuApplication::GuApplication(int &argc, char **argv, int) :
    QGuiApplication(argc, argv)
{
}

bool GuApplication::notify(QObject *receiver, QEvent *event)
{
// to intercept android's back button
#ifdef Q_OS_ANDROID
    if(event->type() == QEvent::Close) {
        emit back(event);
        return false;
    }
    else {
        return QGuiApplication::notify(receiver,event);
    }
#else
        return QGuiApplication::notify(receiver,event);
#endif
}
