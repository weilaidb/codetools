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
#include <QListWidget>
#include <QLabel>
#include <QStatusBar>
#include <QLineEdit>
#include <QCheckBox>
#include <QSplitter>
#include <QComboBox>
#include <QToolBar>
#include <QtWidgets>

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
    static QSettings *read_HistorySettings(QString &organization, const QString &application);
    static QSettings *writeCurrentSettings(QString &organization,
                                           const QString &application);
    static void procStringList(QSettings *pSetting, QString name, QStringList &list, qint8 ucOperType);
    static void procString(QSettings *pSetting, QString name, QString &str, qint8 ucOperType);
    static void procMap(QSettings *pSetting, QString name, QMap<QString, QStringList> &map, qint8 ucOperType);
    static void procAction(QSettings *pSetting, QAction *pAction, QString name, qint8 ucOperType);
    static void procAction(QSettings *pSetting, QAction *pAction, qint8 ucOperType);
    static void procCheckBox(QSettings *pSetting, QCheckBox *pCheckBox, qint8 ucOperType);
    static void procLineEdit(QSettings *pSetting, QLineEdit *pLineEdit, qint8 ucOperType);
    static void procComboBox(QSettings *pSetting, QComboBox *pComboBox, qint8 ucOperType);

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
    static QTextEdit *newTextEdit();
    static QString getLabelEdit(QLabel *pLabel);
    static QString getSelectTextEdit(QTextEdit *pEdit);
    static QString getSelectTextEditEnter(QTextEdit *pEdit);
    static QString getSelectTextBrowser(QTextBrowser *pBrowser);
    static QString getSelectLineTextEdit(QTextEdit *pEdit);
    static int getSelectLine(QTextEdit *pEdit);
    static int duplicateSelectLine(QTextEdit *pTextEdit);
    static QString getTextEdit(QTextEdit *pEdit);
    static bool findTextEdit(QTextEdit *pEdit,QString findtext, QTextDocument::FindFlags options);
    static void setLineEdit(QLineEdit *pLineEdit, QString text);
    static void setLineEditFocus(QLineEdit *pLineEdit);
    static QString getLineEdit(QLineEdit *pLineEdit);
    static bool isLineEditEmpty(QLineEdit *pLineEdit);
    static QString getComBox(QComboBox *pcomboBox);
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
    static void hideListWidget(QListWidget *pWdt);
    static void showListWidget(QListWidget *pWdt);
    static void clearListWidget(QListWidget *pWdt);
    static void clearHideListWidget(QListWidget *pWdt);
    static QListWidgetItem *getListWidgetCurrentItem(QListWidget *pWdt);
    static QList<QListWidgetItem*> getListWidgetSelectedItems(QListWidget *pWdt);
    static int getListWidgetRow(QListWidget *pWdt, QListWidgetItem *pItem);
    static int getListWidgetCurrentRow(QListWidget *pWdt);
    static QListWidgetItem *getListWidgetTakeItem(QListWidget *pWdt, int curIndex);
    static QListWidgetItem *getListWidgetTakeItem(QListWidget *pWdt, QListWidgetItem *pItem);
    static QString getListWidgetItemText(QListWidget *pWdt, int Index);

    static void hidePushButton(QPushButton *pBtn);
    static void showPushButton(QPushButton *pBtn);
    static void hidePushButtons(QVector<QPushButton *> &vec);
    static void showPushButtons(QVector<QPushButton *> &vec);
    static void pushButtonEmitClick(QPushButton *pBtn);
    static void setBtnMenu(QPushButton *pBtn, QMenu *pMenu);

    static void setTextEditFocus(QTextEdit *pEdit);
    static void setTextEditmoveCursorEnd(QTextEdit *pEdit);
    static void setTextEditmoveCursorHead(QTextEdit *pEdit);
    static void setComBoxFocus(QComboBox *pComboBox);
    static void clearComBoxFocus(QComboBox *pComboBox);
    static void setComBoxModel(QComboBox *pComboBox, QAbstractItemModel *pModel);
    static void setComBoxView(QComboBox *pComboBox, QAbstractItemView *pV);
    static void appendTextMoveCursorEnd(QPlainTextEdit *pEdit, QString str);
    static void insertPlainText(QPlainTextEdit *pEdit, QString str);
    static void moveCursorEnd(QPlainTextEdit *pEdit);

    //打开路径
    static int execCmd(QString path);
    static int explorerPath(QString path);
    static int explorerPathExt(QString path);
    /** with current Path **/
    static int explorerPathCurrent(QString path);

    //创建Action，并且设置内容不为空
    static QAction *createActionFull(QString name);
    static QAction *createActionData(QString name,QString data);
    static QAction *createAction(QString name);
    static bool isCheckedQAction(QAction *pAction);
    static bool noCheckedQAction(QAction *pAction);
    static void setCheckedQAction(QAction *pAction, bool bflag);
    static bool getCheckedQAction(QAction *pAction);
    static QString getQActionText(QAction *pAction);
    //checkbox
    static bool isCheckedQCheckBox(QCheckBox *pCheckBox);

    //messgebox
    static int showBoxWarning(QString tips);
    static int showBoxInfo(QString tips);
    static bool showBoxInfoIsYes(QString tips);
    static bool showBoxInfoIsNo(QString tips);
    static int showBoxCritical(QString tips);
    //shortcut
    static void setShortcut(QAction *pAction, QString shortcut);

    //font
    static void setFontDefault(QWidget *pwidget);
    static void setFont(QWidget *pwidget, QString fontname, int fontsize);
    //view
    static void setSizeDefault(QWidget *pWidget);
    static void setSize(QWidget *pWidget, int w, int h);
    static void setWindowTitle(QWidget *pWidget, QString str);
    static void setLayoutDirectionDefault(QWidget *pWidget);
    static void setLayoutDirection(QWidget *pWidget, Qt::LayoutDirection direction);
    static void showMaximized(QWidget *pWidget);
    static void showMinimized(QWidget *pWidget);
    //tab widget
    static void setTabShape(QTabWidget *pWidget, QTabWidget::TabShape shape);
    //time
    static QTimer *createTimer(int &iTimeout, int value);
    //QListWidget
    static void addListWidgetItems(QListWidget *pWidget, QStringList list);
    static void addListWidgetItemsAndShow(QListWidget *pWidget, QStringList list);
    static void clearAddListWidgetItemsAndShow(QListWidget *pWidget, QStringList list);
    static void addListWidgetItems_ClearFirst(QListWidget *pWidget, QStringList list);
    static void addListWidgetItem(QListWidget *pWidget, QString item);
    //QLabel
    static QLabel *newLabel(QString text);
    static void setLabelText(QLabel *pLabel, QString text);
    //StatusBar
    static void showStatusBar(QStatusBar *statusbar, QString msg);
    static void showStatusBarTimerBoth(QStatusBar *statusbar, QString msg);
    static void showStatusBarTimerOnly(QString msg);
    //QSplitter
    //分割比例
    static void setSpliterFactor(QSplitter *pSpliter, int index, int stretch);
    static void addWidget2StatusBar(QStatusBar *statusbar, QWidget *pWidget);
    static void addWidget2ToolBar(QToolBar *toolbar, QWidget *pWidget);

    //路径
    static QString desktopPath();

    //icon
    static QIcon icon(QString file);

    static void setFocus(QComboBox *cbBox);
    static void clear(QComboBox *cbBox);
    static void clear(QPlainTextEdit *pEdit);


public:
    enum{
        TYPE_READ = 1,
        TYPE_WRITE,
    };


private:
    static QMap<QString,QSettings *> m_settingMap;
};

#endif // CUIPUB_H
