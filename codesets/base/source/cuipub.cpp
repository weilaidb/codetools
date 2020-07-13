#include "cuipub.h"
#include "cexpresspub.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QProgressBar>
#include <QClipboard>
#include <QMimeData>
#include <QTextLayout>
#include <QTextBlock>
#include "debugApp.h"

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

void CUIPub::clearMenuAll(QMenu **ppMenu)
{
    if(nullptr == *ppMenu)
    {
        return;
    }

    QMenu *pMenu = *ppMenu;
    //先删除当前节点,显示与删除有冲突
    QList<QAction*> listActions = pMenu->actions();
    foreach (QAction *action, listActions) {
        delete action;
    }
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
        memcpy_s(pNewAction, sizeof(*action), action, sizeof(*action));
        pNewMenu->addAction(pNewAction);
    }
    return pNewMenu;
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

void CUIPub::clearTextEdit(QTextEdit *pEdit)
{
    pEdit->clear();
}


void CUIPub::setTextEdit(QTextEdit *pEdit, QString text)
{
    pEdit->setText(text);
}
























