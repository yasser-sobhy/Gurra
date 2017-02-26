#ifndef GUDEVICE_H
#define GUDEVICE_H

#include <QQmlApplicationEngine>
#include <QtGui/QGuiApplication>

#include <QObject>
#include <QScreen>
#include <qqmlcontext.h>
#include <QDebug>
#include <QFile>
#include <QStandardPaths>

namespace Gurra {


class Device : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal aspectRatio READ getAspectRatio NOTIFY aspectRatioChanged)
    Q_PROPERTY(qreal fontAspectRatio READ getFontAspectRatio NOTIFY fontAspectRatioChanged)
    Q_PROPERTY(bool noDBAvailble READ getNoDBAvailble NOTIFY noDBAvailbleChanged)
    Q_PROPERTY(bool isRightToLeft READ getIsRightToLeft WRITE setIsRightToLeft NOTIFY isRightToLeftChanged)

    qreal m_ratio;
    qreal m_ratioFont;
    bool m_noDBAvailble;
    bool m_isRightToLeft;

signals:
    void aspectRatioChanged();
    void fontAspectRatioChanged();
    void noDBAvailbleChanged();
    void isRightToLeftChanged();

public:
    Device(){

        calcAspectRatio();
    }

    // if running on a desktop return the same aspect ratio
    // to keep width and height unchanged
    //    width: 320
    //    height: 480
    qreal getAspectRatio(){
#ifdef __ANDROID_API__
        return m_ratio;
#else
        return m_ratio;
#endif
    }

    qreal getFontAspectRatio(){
#ifdef __ANDROID_API__
        return 1; //m_ratioFont;
#else
        return 1; //m_ratioFont;
#endif
    }


    Q_INVOKABLE void calcAspectRatio()
    {
        qreal refDpi = 160;
        qreal refHeight = 480.;
        qreal refWidth = 320.;


#ifdef __ANDROID_API__
        QRect rect = qApp->primaryScreen()->geometry();
        qreal dpi = qApp->primaryScreen()->logicalDotsPerInch();

#else
        QRect rect (0,0,320,480);
        qreal dpi = 96.0;
#endif

        qreal height = qMax(rect.width(), rect.height());
        qreal width = qMin(rect.width(), rect.height());

        m_ratio = qMin(height/refHeight, width/refWidth);
        m_ratioFont = qMin(height*refDpi/(dpi*refHeight), width*refDpi/(dpi*refWidth));

        aspectRatioChanged();
        fontAspectRatioChanged();
    }

    bool getNoDBAvailble(){
        return m_noDBAvailble;
    }
    bool getIsRightToLeft(){
        return m_isRightToLeft;
    }
    void setIsRightToLeft(bool isrtl){
        m_isRightToLeft = isrtl;
        isRightToLeftChanged();
    }


};
}
#endif // GUDEVICE_H
