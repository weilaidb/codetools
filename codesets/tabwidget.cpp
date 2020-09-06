#include "tabwidget.h"
#include "mainwindow.h"
#include "ui_tabwidgets.h"
#include "ui_formcenter.h"

#include <QLabel>
#include <QMdiSubWindow>
#include <QWidget>
#include <cuipub.h>

QT_BEGIN_NAMESPACE
namespace Ui { class TabWidget; }
namespace Ui { class FormCenter; }
QT_END_NAMESPACE


TabWidget::TabWidget(QWidget *parent)
    : QMainWindow(parent)
    , uitab(new Ui::TabWidget)
    , m_tabpos(0)
    , m_deftabcnt(5)
{
    uitab->setupUi(this);
    connect(uitab->actionnew, SIGNAL(triggered()), this, SLOT(actNewTab()));

    initUiSets();

}

void TabWidget::actNewTab()
{
    QWidget *pTabNew = new QWidget();
    Ui::FormCenter *pUiCen = new Ui::FormCenter;
    pUiCen->setupUi(pTabNew);
    CUIPub::addTab(uitab->tabWidget, pTabNew, QString("new %1").arg(++m_tabpos));
}

void TabWidget::initUiSets()
{
    CUIPub::clearTab(uitab->tabWidget);
    quint16 dwLp =  0;;
    for(dwLp = 0;dwLp < m_deftabcnt;dwLp++)
    {
        emit uitab->actionnew->triggered();
    }
}
