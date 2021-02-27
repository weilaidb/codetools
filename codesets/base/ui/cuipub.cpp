#include "cuipub.h"
#include "cexpresspub.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QProgressBar>
#include <QClipboard>
#include <QMimeData>
#include <QTextLayout>
#include <QTextBlock>
#include <QTextBrowser>
#include <QDesktopServices>
#include <QMessageBox>
#include <cfilepub.h>
#include "debugApp.h"
#ifdef WIN32
#include <QTabWidget>
#include <clogpub.h>
#include <csignpub.h>
#include <windows.h>
#endif
#include "cstringpub.h"
#include "ctextcodecpub.h"
#include "clogpub.h"
#include "csignpub.h"

#define MAX_LENGTH (20480)

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

void CUIPub::procAction(QSettings *pSetting, QAction *pAction, QString name, qint8 ucOperType)
{
    switch (ucOperType) {
    case TYPE_READ:
    {
        pAction->setChecked(pSetting->value(name).toBool());
    }
        break;
    case TYPE_WRITE:
    {
        pSetting->setValue(name,pAction->isChecked());
    }
        break;
    default:
        break;
    }
}

void CUIPub::procAction(QSettings *pSetting, QAction *pAction, qint8 ucOperType)
{
    switch (ucOperType) {
    case TYPE_READ:
    {
        pAction->setChecked(pSetting->value(pAction->text()).toBool());
    }
        break;
    case TYPE_WRITE:
    {
        pSetting->setValue(pAction->text(),pAction->isChecked());
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

void CUIPub::clearMenuAll(QMenu **ppMenu)
{
    if(nullptr == *ppMenu)
    {
        return;
    }

    QMenu *pMenu = *ppMenu;
    if(nullptr == pMenu)
    {
        return;
    }
    //先删除当前节点,显示与删除有冲突
    QList<QAction*> listActions = pMenu->actions();
    foreach (QAction *action, listActions) {
        //不删除数据为非空的节点
        if(CExpressPub::isEmpty(action->data().toString()))
        {
            delete action;
        }
    }

//    QObjectList q = pMenu->children();
//    pMenu->addMenu()
//    for(int i=0;i<q.length();i++)
//    {
//        if(!q.at(i)->children().empty())
//        {
//            QMenu* pInMenu = qobject_cast<QMenu*>(q.at(i));
//            clearMenuAll(&pInMenu);
//        }
//        else
//        {
//            QObject* qObject = q.at(i);
//            if(qObject->inherits("QAction"))
//            {
//                QAction* b = qobject_cast<QAction*>(qObject);
//                delete b;
//            }
//        }
//    }

    pMenu->clear();
    delete pMenu;
    pMenu = nullptr;
}

void CUIPub::clearMenuItems(QMenu *pMenu)
{
    if(nullptr == pMenu)
    {
        return;
    }
    //先删除当前节点,显示与删除有冲突
    QList<QAction*> listActions = pMenu->actions();
    foreach (QAction *action, listActions) {
        delete action;
    }
    pMenu->clear();
}

QMenu *CUIPub::copyMenu(QMenu *pMenu)
{
    QMenu *pNewMenu = new QMenu(pMenu->title());
    QList<QAction*> listActions = pMenu->actions();
    foreach (QAction *action, listActions) {
        QAction *pNewAction = new QAction(action->text());
        memcpy((void*)pNewAction, (void*)action, sizeof(*action));
        pNewMenu->addAction(pNewAction);
    }
    return pNewMenu;
}

QAction *CUIPub::copyActionOfMenu(QMenu *pMenu,QString findstr)
{

    QList<QAction*> listActions = pMenu->actions();
    foreach (QAction *action, listActions) {
        if(findstr == action->data().toString())
        {
            QAction *pNewAction = new QAction(action->text());
            //            pNewAction->setData(action->data());
            memcpy((void*)pNewAction, (void*)action, sizeof(*action));
            return pNewAction;
        }
    }

    return nullptr;
}


void CUIPub::addMenu(QMenu *pMenu, QString item)
{
    if(CExpressPub::isNullPtr(pMenu))
    {
        return;
    }
    QAction *pAction = new QAction(item);
    if(CExpressPub::isNullPtr(pAction))
    {
        return;
    }
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


QString CUIPub::getClipBoardText()
{
    QClipboard *clipboard = QApplication::clipboard();
    return  clipboard->text();
}

void CUIPub::setClipBoardText(QString setdata)
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(setdata);
}

void CUIPub::paste()
{
    const QClipboard *clipboard = QApplication::clipboard();
    const QMimeData *mimeData = clipboard->mimeData();

    if (mimeData->hasImage()) {
        //        setPixmap(qvariant_cast<QPixmap>(mimeData->imageData()));
    } else if (mimeData->hasHtml()) {
        //        setText(mimeData->html());
        //        setTextFormat(Qt::RichText);
    } else if (mimeData->hasText()) {
        //        setText(mimeData->text());
        //        setTextFormat(Qt::PlainText);
    } else {
        //        setText(tr("Cannot display data"));
    }
}



void CUIPub::startProgress()
{
    //    QProcess::start()
    //    特点：非阻塞、一体式

    //    void QProcess::start(const QString & program, const QStringList & arguments, OpenMode mode = ReadWrite)

    //    使用这样的启动方式之启动外部程序启动后，它会随着主程序的退出而退出。

    //    QProcess::startDetached()
    //    特点：分离式

    //    void QProcess::startDetached(const QString & program, const QStringList & arguments, const QString & workingDirectory = QString(), qint64 * pid = 0)

    //    外部程序启动后，当主程序退出时并不退出，而是继续运行。

    //    QProcess::execute()
    //    特点：阻塞

    //    获取返回值
    //    int QProcess::execute()
    //    int QProcess::exitCode()






}



QString CUIPub::getSelectTextEdit(QTextEdit *pEdit)
{
    return pEdit->textCursor().selectedText();
}

int CUIPub::getSelectLine(QTextEdit *pTextEdit)
{
    //当前光标
    QTextCursor tc = pTextEdit->textCursor();
    QTextLayout *pLayout = tc.block().layout();
    //当前光标在本BLOCK内的相对位置
    int nCurpos = tc.position() - tc.block().position();
    int nTextline = pLayout->lineForTextPosition(nCurpos).lineNumber() + tc.block().firstLineNumber();
    //    qDebug()<<nTextline<<endl;           //可以看到行号随着光标的改变而改变
    return nTextline;
}

QString CUIPub::getSelectLineTextEdit(QTextEdit *pEdit)
{
    //    debugApp() << "getSelectLine  :" << getSelectLine(pEdit);
    return pEdit->document()->findBlockByLineNumber(getSelectLine(pEdit)).text();
}

QString CUIPub::getTextEdit(QTextEdit *pEdit)
{
    return pEdit->toPlainText();
}

int CUIPub::getTextEditLen(QTextEdit *pEdit)
{
    return pEdit->toPlainText().length();
}

void CUIPub::clearTextEdit(QTextEdit *pEdit)
{
    pEdit->clear();
}

void CUIPub::hideTextEdit(QTextEdit *pEdit)
{
    pEdit->hide();
}

void CUIPub::showTextEdit(QTextEdit *pEdit)
{
    pEdit->show();
}


void CUIPub::setTextEdit(QTextEdit *pEdit, QString text)
{
    pEdit->setText(text);
}

void CUIPub::setPlainTextEdit(QTextEdit *pEdit, QString text)
{
    pEdit->setPlainText(text);
}


void CUIPub::setTextEditOnEmpty(QTextEdit *pEdit, QString text)
{
    if(CExpressPub::isNullPtr(pEdit))
    {
        return;
    }
    if(CExpressPub::isEmpty(pEdit->toPlainText()))
    {
        pEdit->setText(text);
    }
}

void CUIPub::setPlainTextEditOnEmpty(QTextEdit *pEdit, QString text)
{
    if(CExpressPub::isNullPtr(pEdit))
    {
        return;
    }
    if(CExpressPub::isEmpty(pEdit->toPlainText()))
    {
        pEdit->setPlainText(text);
    }
}


void CUIPub::clearTextBrowser(QTextBrowser *textBrowser)
{
    textBrowser->clear();
}

void CUIPub::setTextBrowser(QTextBrowser *textBrowser, QString text)
{
    textBrowser->setText(text);
}

void CUIPub::setPlainTextBrowser(QTextBrowser *textBrowser, QString text)
{
    textBrowser->setPlainText(text);
}

QString CUIPub::getTextBrowser(QTextBrowser *textBrowser)
{
    return textBrowser->toPlainText();
}


int CUIPub::execCmd(QString path)
{
    if(CExpressPub::isZero(CStringPub::strSimLen(path)))
    {
        return -1;
    }
    CLogPub::msgDefault(path);

//#ifndef WIN32
//    LPCSTR filepath2 = NULL;
//    char* puacPathBuf = new char[MAX_LENGTH];
//    memset(puacPathBuf, 0, MAX_LENGTH);
//    filepath2 = CTextCodecPub::convertQString2buf(path, puacPathBuf);
//    ShellExecuteA(NULL, "open", filepath2, NULL, NULL, SW_SHOWNORMAL | SW_NORMAL | SW_SHOW);
//    delete [] puacPathBuf;
//#else
    //QUrl支持中文打开
    CFilePub::openSystemPathOrUrl(path);
//#endif
    return 0;
}

/**
 * @brief CUIPub::explorerPathExt
 * @param path
 * @return
 * @desp 支持多文件处理，指文件中带;号
 */
int CUIPub::explorerPathExt(QString path)
{
    int result = -1;
    if(path.contains(CSignPub::signFenHao()))
    {
        QStringList list = path.split(CSignPub::signFenHao());
        foreach (QString item, list) {
            result |= explorerPath(item);
        }
    }
    else
    {
        result = explorerPath(path);
    }
    return result;
}

int CUIPub::explorerPath(QString path)
{
    if(CExpressPub::isZero(CStringPub::strSimLen(path)))
    {
        return -1;
    }

    //    QString prefix = "explorer ";
    QString prefix = "";
    CLogPub::logDefault(path);
    execCmd(prefix + path);
    return 0;
}

void CUIPub::setMenuPolicyCustom(QWidget *pWidget)
{
    pWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    //    QObject::connect(pWidget, SIGNAL(customContextMenuRequested(QPoint)), parent, SLOT(slot_func(QPoint)));

}

QAction *CUIPub::createActionFull(QString name)
{
    QAction *pAction = new QAction(name);
    pAction->setData(name);
    return pAction;
}

QAction *CUIPub::createActionData(QString name,QString data)
{
    QAction *pAction = new QAction(name);
    pAction->setData(data);
    return pAction;
}


QAction *CUIPub::createAction(QString name)
{
    return  new QAction(name);
}



bool CUIPub::isCheckedQAction(QAction *pAction)
{
    return pAction->isChecked();
}

void CUIPub::setCheckedQAction(QAction *pAction, bool bflag)
{

    pAction->setChecked(bflag);
}

bool CUIPub::getCheckedQAction(QAction *pAction)
{
    return pAction->isChecked();
}

int CUIPub::showBoxWarning(QString tips)
{
    return QMessageBox::warning(NULL, "Title", tips,
                                QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

int CUIPub::showBoxInfo(QString tips)
{
    return QMessageBox::information(NULL, "Title", tips,
                                    QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

int CUIPub::showBoxCritical(QString tips)
{
    return QMessageBox::critical(NULL, "Title", tips,
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

bool CUIPub::showBoxInfoIsYes(QString tips)
{
    return QMessageBox::Yes == QMessageBox::information(NULL, "Title", tips,
                                                        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

bool CUIPub::showBoxInfoIsNo(QString tips)
{
    return QMessageBox::No == QMessageBox::information(NULL, "Title", tips,
                                                       QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

QTimer *CUIPub::createTimer(int &iTimeout, int value)
{
    iTimeout = value;
    QTimer *pTimer = new QTimer();
    pTimer->start(iTimeout);
    return pTimer;
}

void CUIPub::hidePushButton(QPushButton *pBtn)
{
    pBtn->hide();
}

void CUIPub::showPushButton(QPushButton *pBtn)
{
    pBtn->show();
}

void CUIPub::pushButtonEmitClick(QPushButton *pBtn)
{
    if(CExpressPub::isNullPtr(pBtn))
    {
        return;
    }
    emit pBtn->click();
}

void CUIPub::setTabName(QTabWidget *tabWidget, int index, const QString &name)
{
    tabWidget->setTabText(index, name);
}

int CUIPub::addTab(QTabWidget *tabWidget, QWidget *widget, const QString &name)
{
    return tabWidget->addTab(widget, name);
}

void CUIPub::clearTab(QTabWidget *tabWidget)
{
    tabWidget->clear();
}


