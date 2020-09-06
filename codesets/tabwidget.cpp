#include "tabwidget.h"
#include "mainwindow.h"
#include "ui_tabwidgets.h"
#include "formcenter.h"

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
    , m_deftabcnt(3)
{
    uitab->setupUi(this);

    initUiSets();

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

