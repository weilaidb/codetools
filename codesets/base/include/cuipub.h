#ifndef CUIPUB_H
#define CUIPUB_H

#include <QSettings>
#include <QMap>
#include <QMenu>

class CUIPub
{
public:
    CUIPub();
    void Var2Map(QSettings &sets, QString envkey, QMap<QString, QStringList> &outmap);
    QMap<QString, QVariant> Map2Var(QMap<QString, QStringList> &inmap);
    void ReadHistorySettings(QString &organization, const QString &application);
    void WriteCurrentSettings(QString &organization,
                              const QString &application);


    static void clearMenu(QMenu *pMenu);
};

#endif // CUIPUB_H
