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
    , m_tabpos(2)
{
    uitab->setupUi(this);
    initUiSets();

    connect(uitab->actionnew, SIGNAL(triggered()), this, SLOT(actNewTab()));
}

void TabWidget::actNewTab()
{
    QWidget *pTabNew = new QWidget();
    Ui::FormCenter *pUiCen = new Ui::FormCenter;
    pUiCen->setupUi(pTabNew);
    uitab->tabWidget->addTab(pTabNew, QString("new %1").arg(++m_tabpos));
}

void TabWidget::initUiSets()
{
    CUIPub::setTabName(uitab->tabWidget, 0, "new 1");
    CUIPub::setTabName(uitab->tabWidget, 1, "new 2");
}
