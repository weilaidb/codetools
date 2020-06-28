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

    static void readHistorySettings(QString &organization, const QString &application);
    static void writeCurrentSettings(QString &organization,
                              const QString &application);
    static void clearMenu(QMenu *pMenu);
    static void addMenu(QMenu *pMenu,QString item);

    static int deskWidth();
    static int deskHeigth();
    static void widgetXYsetDesktop_center(QWidget *widget, int width, int height);
};

#endif // CUIPUB_H
