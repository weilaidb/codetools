/***************************************************************************
** 版权所有:  WeiLai Copyright (c) 2020-2030  ******************************
** 文件名称:  cvecpub.cpp
** 当前版本:  v1.0
** 作    者:
** 完成日期: 2022-01-28_08_47_41
** 修改记录:
** 修改记录:
** 修改日期:
** 版本号  :
** 修改人  :
** 修改内容:
***************************************************************************/


/*****************************头文件****************************************/
#include "cvecpub.h"

/*****************************宏定义****************************************/

/*****************************结构体或类型定义*******************************/


/*****************************全局变量****************************************/


/*****************************本地变量****************************************/


/*****************************函数或类声明****************************************/


/*****************************函数或类实现****************************************/




CVecPub::CVecPub()
{

}

void CVecPub::insertVec(QVector<QLabel *> &vec, QLabel *label)
{
    vec.push_back(label);
}

void CVecPub::insertVec(QVector<QPushButton *> &vec, QPushButton *button)
{
    vec.push_back(button);
}

void CVecPub::insertVec(QVector<QTextEdit *> &vec, QTextEdit *textedit)
{
    vec.push_back(textedit);
}

void CVecPub::deleteVec(QVector<QLabel *> &vec)
{
    foreach (QLabel *label, vec) {
        delete label;
    }
    vec.clear();
}

void CVecPub::deleteVec(QVector<QPushButton *> &vec)
{
    foreach (QPushButton *button, vec) {
        delete button;
    }
    vec.clear();
}

void CVecPub::deleteVec(QVector<QTextEdit *> &vec)
{
    foreach (QTextEdit *textedit, vec) {
        delete textedit;
    }
    vec.clear();
}




