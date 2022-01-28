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
** 修改内容:
***************************************************************************/

/*****************************头文件****************************************/
#include "cuiextpub.h"

/*****************************宏定义****************************************/

/*****************************结构体或类型定义*******************************/


/*****************************全局变量****************************************/


/*****************************本地变量****************************************/


/*****************************函数或类声明****************************************/


/*****************************函数或类实现****************************************/

CUIExtPub::CUIExtPub()
{

}

QTabWidget *CUIExtPub::newTabWidget()
{
    return new QTabWidget();
}

void CUIExtPub::addTab(QTabWidget *pWidget, QLabel *label, QString text)
{
    pWidget->addTab(label,text);
}

void CUIExtPub::setTabPositionWest(QTabWidget *pWidget)
{
    pWidget->setTabPosition(QTabWidget::West);
}

void CUIExtPub::setTabPositionNorth(QTabWidget *pWidget)
{
    pWidget->setTabPosition(QTabWidget::North);
}

void CUIExtPub::setTabPositionSouth(QTabWidget *pWidget)
{
    pWidget->setTabPosition(QTabWidget::South);
}

void CUIExtPub::setTabPositionEast(QTabWidget *pWidget)
{
    pWidget->setTabPosition(QTabWidget::East);
}















