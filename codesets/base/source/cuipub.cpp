#include "cuipub.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QProgressBar>

QMap<QString,QSettings *> CUIPub::m_settingMap;

CUIPub::CUIPub()
{

}



void CUIPub::Var2Map(QSettings *pSets, QString envkey, QMap<QString, QStringList> &outmap)
{
    QMap<QString, QVariant> maptmp = pSets->value(envkey).toMap();

    //map_showcmd
    QMapIterator<QString, QVariant> i(maptmp);
    while (i.hasNext()) {
        i.next();
        QString key = i.key();
        QVariant val = i.value();
        outmap.insert(key, val.toStringList());
    }
}

void CUIPub::Map2Var(QSettings *pSetting,QString envkey,  QMap<QString, QStringList> &inmap)
{
    QMap<QString, QVariant> maptmp;
    maptmp.clear();
    QMapIterator<QString, QStringList> i(inmap);
    while (i.hasNext()) {
        i.next();
        QString key = i.key();
        QVariant val = i.value();
        maptmp.insert(key, val);
    }

    pSetting->setValue(envkey, maptmp);
}



QString CUIPub::bindKey(QString &organization,
                                 const QString &application)
{
    return organization + application;
}

void CUIPub::procStringList(QSettings *pSetting, QString name, QStringList &list, qint8 ucOperType)
{
    switch (ucOperType) {
    case TYPE_READ:
    {
        list = pSetting->value(name).toStringList();
    }
        break;
    case TYPE_WRITE:
    {
        pSetting->setValue(name,list);
    }
        break;
    default:
        break;
    }
}

void CUIPub::procString(QSettings *pSetting, QString name, QString &str, qint8 ucOperType)
{
    switch (ucOperType) {
    case TYPE_READ:
    {
        str = pSetting->value(name).toString();
    }
        break;
    case TYPE_WRITE:
    {
        pSetting->setValue(name,str);
    }
        break;
    default:
        break;
    }
}

void CUIPub::procMap(QSettings *pSetting, QString name, QMap<QString, QStringList> &map, qint8 ucOperType)
{
    switch (ucOperType) {
    case TYPE_READ:
    {
        Var2Map(pSetting, name, map);
    }
        break;
    case TYPE_WRITE:
    {
        Map2Var(pSetting, name, map);
    }
        break;
    default:
        break;
    }
}


/**
 * @brief CUIPub::ReadHistorySettings
 */
QSettings * CUIPub::readHistorySettings(QString &organization,
                                 const QString &application)
{
    auto find_index = m_settingMap.find(bindKey(organization, application));
    if(find_index == m_settingMap.end())
    {
        QSettings *pSettings = new QSettings(organization, application);
        m_settingMap.insert(bindKey(organization, application), pSettings);
        return pSettings;
    }
    return find_index.value();
}

/**
 * @brief CUIPub::WriteCurrentSettings
 */
QSettings * CUIPub::writeCurrentSettings(QString &organization,
                                  const QString &application)
{
    auto find_index = m_settingMap.find(bindKey(organization, application));
    if(find_index == m_settingMap.end())
    {
        QSettings *pSettings = new QSettings(organization, application);
        m_settingMap.insert(bindKey(organization, application), pSettings);
        return pSettings;
    }
    return find_index.value();
}

void CUIPub::clearMenu(QMenu *pMenu)
{
    //先删除当前节点
    QList<QAction*> listActions = pMenu->actions();
    foreach (QAction *action, listActions) {
        delete action;
    }
    pMenu->clear();
}

void CUIPub::addMenu(QMenu *pMenu, QString item)
{
    QAction *pAction = new QAction(item);
    pMenu->addAction(pAction);
}


int CUIPub::deskWidth()
{
    QDesktopWidget *desk=QApplication::desktop();
    int wd=desk->width();
//    int ht=desk->height();
    return wd;
}

int CUIPub::deskHeigth()
{
    QDesktopWidget *desk=QApplication::desktop();
//    int wd=desk->width();
    int ht=desk->height();
    return ht;
}

void CUIPub::widgetXYsetDesktop_center(QWidget *widget, int width, int height)
{
    QDesktopWidget *desk=QApplication::desktop();
    int wd=desk->width();
    int ht=desk->height();
    widget->move((wd - width/2)/2,(ht-height/2)/2);
}

void CUIPub::progressBar(QProgressBar *pProgressBar, int current, int max)
{
    pProgressBar->setOrientation(Qt::Horizontal);  // 水平方向
    pProgressBar->setMinimum(0);  // 最小值
    pProgressBar->setMaximum(100);  // 最大值
    pProgressBar->setValue(current*100/max);  // 当前进度
    pProgressBar->show();
}

