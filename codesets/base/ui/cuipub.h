#ifndef CUIPUB_H
#define CUIPUB_H

#include "basetypepub.h"
#include <QSettings>
#include <QMap>
#include <QMenu>
#include <QProgressBar>
#include <QTextEdit>
#include <QTextBrowser>
#include <QTimer>
#include <QPushButton>
#include <QTabWidget>

/**
  ** 自定义右键菜单
  **/

#define GEN_MENU_PUB(pWidget, procFun)\
    CUIPub::setMenuPolicyCustom(pWidget);\
    QObject::connect(pWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(procFun(QPoint)));\



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
    static void procAction(QSettings *pSetting, QAction *pAction, QString name, qint8 ucOperType);
    static void procAction(QSettings *pSetting, QAction *pAction, qint8 ucOperType);

    static void clearMenuAll(QMenu **ppMenu);
    static void clearMenuItems(QMenu *pMenu);
    static QMenu *copyMenu(QMenu *pMenu);
    static QAction *copyActionOfMenu(QMenu *pMenu,QString findstr);
    static void addMenu(QMenu *pMenu,QString item);
    static void setMenuPolicyCustom(QWidget *pWidget);

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

    //获取选中文本
    static QString getSelectTextEdit(QTextEdit *pEdit);
    static QString getSelectLineTextEdit(QTextEdit *pEdit);
    static int getSelectLine(QTextEdit *pEdit);
    static QString getTextEdit(QTextEdit *pEdit);
    static int getTextEditLen(QTextEdit *pEdit);
    static void clearTextEdit(QTextEdit *pEdit);
    static void setTextEdit(QTextEdit *pEdit, QString text);
    static void setPlainTextEdit(QTextEdit *pEdit, QString text);
    static void setTextEditOnEmpty(QTextEdit *pEdit, QString text);
    static void setPlainTextEditOnEmpty(QTextEdit *pEdit, QString text);
    static void clearTextBrowser(QTextBrowser *textBrowser);
    static void setTextBrowser(QTextBrowser *textBrowser, QString text);
    static void setPlainTextBrowser(QTextBrowser *textBrowser, QString text);
    static QString getTextBrowser(QTextBrowser *textBrowser);
    static void hideTextEdit(QTextEdit *pEdit);
    static void showTextEdit(QTextEdit *pEdit);
    static void hidePushButton(QPushButton *pBtn);
    static void showPushButton(QPushButton *pBtn);
    static void pushButtonEmitClick(QPushButton *pBtn);

    //打开路径
    static int execCmd(QString path);
    static int explorerPath(QString path);
    static int explorerPathExt(QString path);

    //创建Action，并且设置内容不为空
    static QAction *createActionFull(QString name);
    static QAction *createActionData(QString name,QString data);
    static QAction *createAction(QString name);
    static bool isCheckedQAction(QAction *pAction);
    static void setCheckedQAction(QAction *pAction, bool bflag);
    static bool getCheckedQAction(QAction *pAction);

    //messgebox
    static int showBoxWarning(QString tips);
    static int showBoxInfo(QString tips);
    static bool showBoxInfoIsYes(QString tips);
    static bool showBoxInfoIsNo(QString tips);
    static int showBoxCritical(QString tips);


    //time
    static QTimer *createTimer(int &iTimeout, int value);

    //QTabWidget *tabWidget
    static void setTabName(QTabWidget *tabWidget, int index, const QString &name);
public:
    enum{
        TYPE_READ = 1,
        TYPE_WRITE,
    };


private:
    static QMap<QString,QSettings *> m_settingMap;
};

#endif // CUIPUB_H
