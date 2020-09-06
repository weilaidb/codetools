#include "tabwidget.h"
#include "mainwindow.h"
#include "ui_tabwidgets.h"
#include "ui_formcenter.h"

#include <QLabel>
#include <QMdiSubWindow>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class TabWidget; }
namespace Ui { class FormCenter; }
QT_END_NAMESPACE


TabWidget::TabWidget(QWidget *parent)
    : QMainWindow(parent)
    , uitab(new Ui::TabWidget)
{
    uitab->setupUi(this);
    initUiSets();

//    //Create a MDI Area
//    m_mdiArea = new QMdiArea;
//    this->setCentralWidget(m_mdiArea);

    connect(uitab->actionnew, SIGNAL(triggered()), this, SLOT(actNewTab()));
    actNewTab();

}

void TabWidget::actNewWindow()
{
    QLabel *label = new QLabel(tr("MDI SubWindow!"));
    QMdiSubWindow *subWin = new QMdiSubWindow;
    subWin->setWidget(label);
    subWin->setAttribute(Qt::WA_DeleteOnClose);
    m_mdiArea->addSubWindow(subWin);
    subWin->show();
}
void TabWidget::actNewTab()
{
    QWidget *pTabNew = new QWidget();
    Ui::FormCenter *pUiCen = new Ui::FormCenter;
    pUiCen->setupUi(pTabNew);
    uitab->tabWidget->addTab(pTabNew, "Center");
}

void TabWidget::initUiSets()
{
//    QLabel *label = new QLabel(tr("MDI SubWindow!"));
//    ui->tab->setLayout(label);

//    uitab->tab->setLayout();
}
