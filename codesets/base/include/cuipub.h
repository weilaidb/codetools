#ifndef CUIPUB_H
#define CUIPUB_H

#include "basetypepub.h"
#include <QSettings>
#include <QMap>
#include <QMenu>
#include <QProgressBar>

class CUIPub
{
public:
    CUIPub();
    static void Var2Map(QSettings *pSets, QString envkey, QMap<QString, QStringList> &outmap);
    static void Map2Var(QSettings *pSetting, QString envkey, QMap<QString, QStringList> &inmap);

    static QString bindKey(QString &organization, const QString &application);
    static QSettings *readHistorySettings(QString &organization, const QString &application);
    static QSettings *writeCurrentSettings(QString &organization,
                                           const QString &application);
    static void procStringList(QSettings *pSetting, QString name, QStringList &list, qint8 ucOperType);
    static void procString(QSettings *pSetting, QString name, QString &str, qint8 ucOperType);
    static void procMap(QSettings *pSetting, QString name, QMap<QString, QStringList> &map, qint8 ucOperType);

    static void clearMenu(QMenu *pMenu);
    static void addMenu(QMenu *pMenu,QString item);

    static int deskWidth();
    static int deskHeigth();
    static void widgetXYsetDesktop_center(QWidget *widget, int width, int height);
    static void progressBar(QProgressBar *pProgressBar, int current, int max);

    //剪切板
    static QString getClipBoardText();
    static void setClipBoardText(QString setdata);
    static void paste();

    //进程
    static void startProgress();

public:
    enum{
        TYPE_READ = 1,
        TYPE_WRITE,
    };


private:
    static QMap<QString,QSettings *> m_settingMap;
};

#endif // CUIPUB_H
