#include "tabwidget.h"
#include "ui_tabwidgets.h"
#include "formcenter.h"

#include <QLabel>
#include <QMdiSubWindow>
#include <QWidget>
#include <clogpub.h>
#include <cstringpub.h>
#include <ctextcodecpub.h>
#include <cuipub.h>
#include "version.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TabWidget; }
namespace Ui { class FormCenter; }
QT_END_NAMESPACE


TabWidget::TabWidget(char *appexe, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TabWidget)
    , m_tabpos(0)
    , m_deftabcnt(3)
{
    m_apppath = CTextCodecPub::getGBKToUnicode(appexe);
//    CLogPub::logDefault(m_apppath);
    CLogPub::msgDefault(appexe); //发现“副本”这两个字的编码是B8B1 B1BE，为GB2312编码，appexe传递的数据为直接为中文编码
    ui->setupUi(this);
    showVersion();
    initActionSets();
    initCheckBoxSets();
    initVars();
    initUiSets();

}

void TabWidget::showVersion()
{
    ui->statusbar->showMessage(APP_VERSION);
}
void TabWidget::initCheckBoxSets()
{

}

void TabWidget::initUiSets()
{
    connect(ui->actionnew, SIGNAL(triggered()), this, SLOT(actNewTab()));


    CUIPub::clearTab(ui->tabWidget);
    quint16 dwLp =  0;;
    for(dwLp = 0;dwLp < m_deftabcnt;dwLp++)
    {
        emit ui->actionnew->triggered();
    }
}

void TabWidget::initActionSets()
{
    QObject::connect(ui->action_codeFormat_File, SIGNAL(triggered()), this, SLOT(proc_action_codeFormat_File()));
    QObject::connect(ui->action_codeFormat_Directory, SIGNAL(triggered()), this, SLOT(proc_action_codeFormat_Directory()));
    QObject::connect(ui->action_codeFormat_Edit_Config, SIGNAL(triggered()), this, SLOT(proc_action_codeFormat_Edit_Config()));
    QObject::connect(ui->action_codeFormat_Save_Config, SIGNAL(triggered()), this, SLOT(proc_action_codeFormat_Save_Config()));
    QObject::connect(ui->action_codeFormat_Del_Config, SIGNAL(triggered()), this, SLOT(proc_action_codeFormat_Del_Config()));
    QObject::connect(ui->menu_codeFormat_Recent, SIGNAL(triggered(QAction *)), this, SLOT(proc_menu_codeFormat_Recent(QAction *)));
    //about
    QObject::connect(ui->action_about, SIGNAL(triggered()), this, SLOT(proc_action_about()));
    QObject::connect(ui->action_attention, SIGNAL(triggered()), this, SLOT(proc_action_attention()));
    //mysql
    QObject::connect(ui->action_mysql_testdatabase, SIGNAL(triggered()), this, SLOT(proc_action_mysql_testdatabase()));


    //office
    QObject::connect(ui->action_office_open, SIGNAL(triggered()), this, SLOT(proc_action_office_open()));
    QObject::connect(ui->action_office_search_file, SIGNAL(triggered()), this, SLOT(proc_action_office_search_file()));
    QObject::connect(ui->action_office_search_dir, SIGNAL(triggered()), this, SLOT(proc_action_office_search_dir()));
    QObject::connect(ui->menu_document_open_recent, SIGNAL(triggered(QAction *)), this, SLOT(proc_menu_document_open_recent(QAction *)));
    QObject::connect(ui->menu_document_search_recent, SIGNAL(triggered(QAction *)), this, SLOT(proc_menu_document_search_recent(QAction *)));

    //net
    QObject::connect(ui->action_net_server, SIGNAL(triggered()), this, SLOT(proc_action_net_server()));
    QObject::connect(ui->action_net_client, SIGNAL(triggered()), this, SLOT(proc_action_net_client()));
    QObject::connect(ui->action_net_publish, SIGNAL(triggered()), this, SLOT(proc_action_net_publish()));
    QObject::connect(ui->action_net_subscribe, SIGNAL(triggered()), this, SLOT(proc_action_net_subscribe()));

    //edit config
    QObject::connect(ui->action_EditCfgFile, SIGNAL(triggered(bool)), this, SLOT(proc_action_EditCfgFile(bool)));
    QObject::connect(ui->action_TryAgain, SIGNAL(triggered()), this, SLOT(proc_action_TryAgain()));
    QObject::connect(ui->action_DeleteCfgFile, SIGNAL(triggered(bool)), this, SLOT(proc_action_DeleteCfgFile(bool)));

//    //text edit
//    QObject::connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(proc_textEdit_textChanged()));

    //clipboard change


    //check no exist path
//    QObject::connect(ui->action_checknoexistpath, SIGNAL(triggered(bool)), this, SLOT(proc_action_checknoexistpath(bool)));

    //background update
    //由于SSD硬盘和机械硬盘检索的差异，反复右键可能在机械硬盘上反应极慢
    QObject::connect(ui->action_background_update, SIGNAL(triggered(bool)), this, SLOT(proc_action_background_update(bool)));
    QObject::connect(ui->action_update, SIGNAL(triggered(bool)), this, SLOT(proc_action_update(bool)));


}


void TabWidget::initVars()
{
    openDirPathRecent = "/";
    openFilePathRecent = "/";
    openWordFilePathRecent = "/";
    logAstyleName = "astyle.log";
    cfgAstyleName = "astyle.conf";
    cfgAstyleNameOrg = cfgAstyleName + ".org";
    CStringPub::clearStringList(nameFilters);
    CStringPub::clearStringList(recentfiles_codeformat);
    CStringPub::clearStringList(recentfiles_document);
    m_organization = "weilaidb";
    m_application = "codesets";
    m_pSettings = nullptr;
    m_thread_server = nullptr;
    m_thread_client = nullptr;
    m_thread_publish = nullptr;
    m_thread_subscribe = nullptr;

    CStringPub::clearString(m_EditConfig);
}

void TabWidget::actNewTab()
{
    QWidget *pTabNew = new QWidget();
    FormCenter *uiCen = new FormCenter(pTabNew);
    Q_UNUSED(uiCen);
    CUIPub::addTab(ui->tabWidget, pTabNew, QString("new %1").arg(++m_tabpos));
}

