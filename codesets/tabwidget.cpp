#include "tabwidget.h"
#include "mainwindow.h"
#include "ui_tabwidgets.h"
#include "formcenter.h"

#include <QLabel>
#include <QMdiSubWindow>
#include <QWidget>
#include <clogpub.h>
#include <ctextcodecpub.h>
#include <cuipub.h>

QT_BEGIN_NAMESPACE
namespace Ui { class TabWidget; }
namespace Ui { class FormCenter; }
QT_END_NAMESPACE


TabWidget::TabWidget(char *appexe, QWidget *parent)
    : QMainWindow(parent)
    , uitab(new Ui::TabWidget)
    , m_tabpos(0)
    , m_deftabcnt(3)
{
    m_apppath = CTextCodecPub::getGBKToUnicode(appexe);
//    CLogPub::logDefault(m_apppath);
    CLogPub::msgDefault(appexe); //发现“副本”这两个字的编码是B8B1 B1BE，为GB2312编码，appexe传递的数据为直接为中文编码
    uitab->setupUi(this);
    showVersion();
    initUiSets();

}

void TabWidget::showVersion()
{
    uitab->statusbar->showMessage(APP_VERSION);
}
void TabWidget::initUiSets()
{
    connect(uitab->actionnew, SIGNAL(triggered()), this, SLOT(actNewTab()));


    CUIPub::clearTab(uitab->tabWidget);
    quint16 dwLp =  0;;
    for(dwLp = 0;dwLp < m_deftabcnt;dwLp++)
    {
        emit uitab->actionnew->triggered();
    }
}

void TabWidget::actNewTab()
{
    QWidget *pTabNew = new QWidget();
    FormCenter *uiCen = new FormCenter(pTabNew);
    UNUSED(uiCen);
    CUIPub::addTab(uitab->tabWidget, pTabNew, QString("new %1").arg(++m_tabpos));
}

