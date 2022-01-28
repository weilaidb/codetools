/***************************************************************************
** 版权所有:  WeiLai Copyright (c) 2020-2030  ******************************
** 文件名称:  test.c
** 当前版本:  v1.0
** 作    者:
** 完成日期: 2022-01-28_07_39_01
** 修改记录:
** 修改记录:
** 修改日期:
** 版本号  :
** 修改人  :
** 修改内容:UI扩展
***************************************************************************/

#ifndef CUIEXTPUB_H
#define CUIEXTPUB_H

/*****************************头文件****************************************/
#include <QtWidgets>
#include <QDebug>
#include <QTabWidget>
#include <QStackedWidget>
/*****************************宏定义****************************************/

/*****************************结构体或类型定义*******************************/


/*****************************全局变量****************************************/


/*****************************本地变量****************************************/


/*****************************函数或类声明****************************************/


/*****************************函数或类实现****************************************/


/**
 * @brief The CUIExtPub class
 * 扩展UI
 */

class CUIExtPub
{
public:
    CUIExtPub();

    static QTabWidget *newTabWidget();
    static void addTab(QTabWidget *pWidget, QLabel *label, QString text);
    static void setTabPositionWest(QTabWidget *pWidget);
    static void setTabPositionNorth(QTabWidget *pWidget);
    static void setTabPositionSouth(QTabWidget *pWidget);
    static void setTabPositionEast(QTabWidget *pWidget);
};

#endif // CUIEXTPUB_H