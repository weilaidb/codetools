#ifndef CUIPUB_H
#define CUIPUB_H

#include "basetypepub.h"
#include <QSettings>
#include <QMap>
#include <QMenu>

class CUIPub
{
public:
    CUIPub();
    static void Var2Map(QSettings &sets, QString envkey, QMap<QString, QStringList> &outmap);
    static QMap<QString, QVariant> Map2Var(QMap<QString, QStringList> &inmap);

    static QString bindKey(QString &organization, const QString &application);
    static QSettings *readHistorySettings(QString &organization, const QString &application);
    static QSettings *writeCurrentSettings(QString &organization,
                              const QString &application);
    static void clearMenu(QMenu *pMenu);
    static void addMenu(QMenu *pMenu,QString item);

    static int deskWidth();
    static int deskHeigth();
    static void widgetXYsetDesktop_center(QWidget *widget, int width, int height);

private:
    static QMap<QString,QSettings *> m_settingMap;
};

#endif // CUIPUB_H
