#include <unistd.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_cdialogasktext.h"
#include "ui_supertest.h"
#include "supertest.h"
#include "cdialogsearch.h"
#include "cdialognewnode.h"
#include "astyle_main.h"
#include "debugApp.h"
#include "basetypepub.h"
#include "basedefinepub.h"
#include "csignpub.h"
#include "cprintpub.h"
#include "cstringpub.h"
#include "cnumpub.h"
#include "cfilepub.h"
#include "cmsgtips.h"
#include "looppub.h"
#include "cuipub.h"
#include "csqlpub.h"
#ifdef WIN32
#include "cofficepub.h"
#include "cexcelpub.h"
#include <windows.h>
#endif
#include "cdialogpub.h"
#include "cnetworkpub.h"
#include "cregexppub.h"
#include "cexpresspub.h"
#include "cprintpub.h"
#include "ctreepub.h"
#include "cmappub.h"
#include "calgorithmpub.h"
#include "clogpub.h"
#include "ctextcodecpub.h"
#include <QCheckBox>
#include <QDebug>
#include <QDesktopServices>
#include <QException>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QProgressBar>
#include <csignpub.h>
#include "cdialogabout.h"
#include "cnetdiaglog.h"
#include "ctcpserverwindow.h"
#include "ctcpclientwindow.h"
#include "cudpwindow.h"
#include "cudpmcastwindow.h"
#include "chttpwindow.h"
#include "caudioplayer.h"
#include "csystempub.h"
#include "ccmdwindow.h"
#include "cdatetime.h"

/**
  **处理内容最大值
  **/
#define MANYCONTENTMAX    500

/**
  ** Action 名称
  **/
#define STR_PROC_PKG_TO_LINE ("报文成一行")


extern int AyStyleMain(int argc, char** argv);


MainWindow::MainWindow(char *appexe, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    m_apppath = CTextCodecPub::getGBKToUnicode(appexe);
    //    CLogPub::logDefault(m_apppath);
    CLogPub::msgDefault(appexe); //发现“副本”这两个字的编码是B8B1 B1BE，为GB2312编码，appexe传递的数据为直接为中文编码

    ui->setupUi(this);
    show_Version();
    iniUiOther();
    init_ActionSets();
    init_CheckBoxSets();
    init_PushButtonSets();
    init_Vars();
    init_UiSets();
    InstallEventFilterSets();

    read_Setting();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_Dialog()
{
    //模态对话框，动态创建，用过后删除
    pDialog =  new QDialog(this);
    uiDialog = new Ui::CDialogAskText();
    uiDialog->setupUi(pDialog);
    connect(uiDialog->pushButton_clear, SIGNAL(clicked()),this, SLOT(clearDialogText()));
    connect(uiDialog->pushButton_paste, SIGNAL(clicked()),this, SLOT(pasteDialogText()));
    Qt::WindowFlags flags=pDialog->windowFlags();
    pDialog->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
}

void MainWindow::show_Version()
{
    ui->statusbar->showMessage(APP_VERSION);
}

void MainWindow::init_CheckBoxSets()
{

}


void MainWindow::hide_PushButtonSets()
{
    QVector<QPushButton *> vecPushBtns;
    vecPushBtns.append(ui->pushButton_left_clear  );
    vecPushBtns.append(ui->pushButton_left_paste  );
    vecPushBtns.append(ui->pushButton_tryagain    );
    vecPushBtns.append(ui->pushButton_right_clear );
    vecPushBtns.append(ui->pushButton_right_copy  );
    vecPushBtns.append(ui->pushButton_clearTryAgainExt  );

    if(CUIPub::isCheckedQAction(ui->action_hidebuttonswitch))
    {
        CUIPub::hidePushButtons(vecPushBtns);
        return;
    }

    CUIPub::showPushButtons(vecPushBtns);
}

void MainWindow::init_PushButtonSets()
{
    QObject::connect(ui->pushButton_left_clear, SIGNAL(clicked()), this, SLOT(proc_pushButton_left_clear()));
    QObject::connect(ui->pushButton_left_paste, SIGNAL(clicked()), this, SLOT(proc_pushButton_left_paste()));
    QObject::connect(ui->pushButton_tryagain, SIGNAL(clicked()), this, SLOT(proc_pushButton_tryagain()));
    QObject::connect(ui->pushButton_right_clear, SIGNAL(clicked()), this, SLOT(proc_pushButton_right_clear()));
    QObject::connect(ui->pushButton_right_copy, SIGNAL(clicked()), this, SLOT(proc_pushButton_right_copy()));


    QObject::connect(ui->action_hidebuttonswitch, SIGNAL(triggered()), this, SLOT(hide_PushButtonSets()));
}

void MainWindow::InstallEventFilterSets()
{
    ui->textEdit->installEventFilter(this);
    ui->textEdit_cfgTips->installEventFilter(this);
}

void MainWindow::init_ActionSets()
{
    QObject::connect(ui->action_codeFormat_File, SIGNAL(triggered()), this, SLOT(proc_action_codeFormat_File()));
    QObject::connect(ui->action_codeFormat_Directory, SIGNAL(triggered()), this, SLOT(proc_action_codeFormat_Directory()));
    QObject::connect(ui->action_codeFormat_Edit_Config, SIGNAL(triggered()), this, SLOT(proc_action_codeFormat_Edit_Config()));
    QObject::connect(ui->action_codeFormat_Save_Config, SIGNAL(triggered()), this, SLOT(proc_action_codeFormat_Save_Config()));
    QObject::connect(ui->action_codeFormat_Del_Config, SIGNAL(triggered()), this, SLOT(proc_action_codeFormat_Del_Config()));
    QObject::connect(ui->menu_codeFormat_Recent, SIGNAL(triggered(QAction *)), this, SLOT(proc_menu_codeFormat_Recent(QAction *)));
    //about
    QObject::connect(ui->action_about, SIGNAL(triggered()), this, SLOT(proc_action_about()));
    QObject::connect(ui->action_attention, SIGNAL(triggered()), this, SLOT(proc_action_attentionnew()));

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

    //text edit
    QObject::connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(proc_textEdit_textChanged()));

    //clipboard change


    //check no exist path
    //    QObject::connect(ui->action_checknoexistpath, SIGNAL(triggered(bool)), this, SLOT(proc_action_checknoexistpath(bool)));

    //background update
    //由于SSD硬盘和机械硬盘检索的差异，反复右键可能在机械硬盘上反应极慢
    QObject::connect(ui->action_background_update, SIGNAL(triggered(bool)), this, SLOT(proc_action_background_update(bool)));
    QObject::connect(ui->action_update, SIGNAL(triggered(bool)), this, SLOT(proc_action_update(bool)));

    //test for
    QObject::connect(ui->action_scan_test_dir, SIGNAL(triggered(bool)), this, SLOT(proc_action_scan_test_dir(bool)));
    //ascii <--> string
    QObject::connect(ui->actionascii_to_string, SIGNAL(triggered(bool)), this, SLOT(proc_actionascii_to_string()));
    QObject::connect(ui->actionascii_to_string_10, SIGNAL(triggered(bool)), this, SLOT(proc_actionascii_to_string_10()));
    QObject::connect(ui->actionstring_to_ascii, SIGNAL(triggered(bool)), this, SLOT(proc_actionstring_to_ascii()));
    QObject::connect(ui->actionstring_to_ascii_10, SIGNAL(triggered(bool)), this, SLOT(proc_actionstring_to_ascii_10()));

    //new node name
    QObject::connect(ui->action_newstandnode, SIGNAL(triggered(bool)), this, SLOT(proc_action_newstandnode()));
    QObject::connect(ui->action_newusernode, SIGNAL(triggered(bool)), this, SLOT(proc_action_newusernode()));

    //tools
    QObject::connect(ui->action_delspace, SIGNAL(triggered(bool)), this, SLOT(proc_action_delspace()));
    QObject::connect(ui->action_dellastspacesort, SIGNAL(triggered(bool)), this, SLOT(proc_action_dellastspacesort()));
    QObject::connect(ui->action_del_BCompare_xml, SIGNAL(triggered(bool)), this, SLOT(proc_action_del_BCompare_xml()));

    //最近搜索的key
    QObject::connect(ui->action_recentopen, SIGNAL(triggered(bool)), this, SLOT(proc_action_recentopen(bool)));

    //进程重启
    QObject::connect(ui->action_procreboot, SIGNAL(triggered(bool)), this, SLOT(proc_action_procreboot(bool)));

    //生成正则文本序号
    QObject::connect(ui->action_GenRegExpTextSeq, SIGNAL(triggered()), this, SLOT(proc_action_GenRegExpTextSeq()));

    //listwidget searchresult rename
    ui->listWidget_searchresult->setContextMenuPolicy(Qt::CustomContextMenu);


    //自定义
    QObject::connect(spinFontSize, SIGNAL(valueChanged(int)),this, SLOT(on_spinBoxFontSize_valueChanged(int)));
    QObject::connect(comboFont, SIGNAL(currentIndexChanged(const QString &)),this, SLOT(on_combFont_currentIndexChanged(const QString &)));


    //Thread
    connect(&threadMonitor,SIGNAL(started()),this,SLOT(onthreadM_started()));
    connect(&threadMonitor,SIGNAL(finished()),this,SLOT(onthreadM_finished()));
    connect(&threadMonitor,SIGNAL(newValue(int,int)),this,SLOT(onthreadM_newValue(int,int)));
    //    connect(&threadMonitor,SIGNAL(newValue(int,int)),this,SLOT(onthreadM_newValue(int,int)), Qt::DirectConnection);
    //    connect(&threadMonitor,SIGNAL(newValue(int,int)),this,SLOT(onthreadM_newValue(int,int)), Qt::QueuedConnection);
    //    connect(&threadMonitor,SIGNAL(newValue(int,int)),this,SLOT(onthreadM_newValue(int,int)), Qt::BlockingQueuedConnection);

}


void MainWindow::init_Vars()
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
    pMulWinTest = nullptr;

    CStringPub::clearString(m_EditConfig);
}




void MainWindow::init_UiSets()
{
    pRightMouse_L = nullptr;
    pRightMouse_R = nullptr;
    m_lstRightMouse.clear();
    //QTextEdit 右键菜单
    GEN_MENU_PUB(ui->textEdit, proc_generate_menu_left);
    GEN_MENU_PUB(ui->textBrowser, proc_generate_menu_right);
    GEN_MENU_PUB(ui->textEdit_cfgAfter, proc_generate_menu_cfgAfter);

    //自定义菜单，从文件读取
    pMenuCustom = nullptr;
    m_FileNameMenu_stand = "reg/selfmenu.txt";
    m_FileNameMenu_user  = "reg/selfmenu_user.txt";
    CFilePub::createFileEmptyNoExistAndVar(m_FileNameMenu, m_FileNameMenu_stand + ";" + m_FileNameMenu_user);
    /**
      ** 模式：
      ** 单行 多处理
      ** 单行 单处理
      ** 多行 单处理
      ** 多行 多处理
      **/
    CFilePub::createFileEmptyNoExistAndVar(m_FileMode_AllL_ExecMulti, "reg/selfmode_allline_execmulti.txt");
    CFilePub::createFileEmptyNoExistAndVar(m_FileMode_SingleL_ExecMulti, "reg/selfmode_singleline_execmulti.txt");
    CFilePub::createFileEmptyNoExistAndVar(m_FileMode_SingleL_ExecSingle, "reg/selfmode_singleline_execsingle.txt");

    //配置默认关闭
    emit ui->action_EditCfgFile->triggered(false);

    //    pCheckLeftTimer = CUIPub::createTimer(iTimeout, 600);
    //    connect(pCheckLeftTimer, SIGNAL(timeout()), this, SLOT(proc_textEdit_textChanged()));

    //    pClipBoardTimer = CUIPub::createTimer(iClipBoardTimeout, 600);
    //    connect(pClipBoardTimer, SIGNAL(timeout()), this, SLOT(proc_clipBoard_textChanged()));

    //    //后台数据更新频率，暂定为1分钟
    //    pTimerBackgroundUpdate = CUIPub::createTimer(iTimeoutBackgroundUpdate, 1000 * 60 * 1);
    //    connect(pTimerBackgroundUpdate, SIGNAL(timeout()), this, SLOT(proc_TimerBackgroundUpdate()));

    CFilePub::createFileEmptyNoExistAndVar(m_FileNameFreqUseMax, "reg/freqmax.txt");
    m_ActualFreqUseCnt = CFilePub::getNumFirstFromFileLimitMin(m_FileNameFreqUseMax, 15);
    debugApp() << "m_ActualFreqUseCnt:" << m_ActualFreqUseCnt;
    read_FreqUseFile();
    CFilePub::createFileEmptyNoExistAndVar(m_FileNameRecentOpen, "reg/recentopen.txt");
    m_ListRecentOpen = CFilePub::readFileAllFilterEmptyUnique(m_FileNameRecentOpen);
    CFilePub::createFileEmptyNoExistAndVar(m_AttentionFile, "reg/attention.txt");
    CFilePub::createFileEmptyNoExistAndVar(m_FileNameContentMax, "reg/contentmax.txt");

    //打开常用文件列表
    CFilePub::createFileEmptyNoExistAndVar(m_ListOpenFile, "reg/normalfiles.txt");

    CFilePub::createFileEmptyNoExistAndVar(m_ListNetSearchFile, "reg/netsearch.txt");
    m_NetSearchList = CFilePub::readFileAllFilterEmptyUnique(m_ListNetSearchFile);


    //search result list widget, default hide
    CUIPub::hideListWidget(ui->listWidget_searchresult);

    //整体 分割比例
    CUIPub::setSpliterFactor(ui->splitter_5, 0, 3);
    CUIPub::setSpliterFactor(ui->splitter_5, 1, 7);
    //中间水平 三栏 分割比例
    CUIPub::setSpliterFactor(ui->splitter_2, 0, 4);
    CUIPub::setSpliterFactor(ui->splitter_2, 1, 2);
    CUIPub::setSpliterFactor(ui->splitter_2, 2, 4);

    //右侧垂直 三栏 分割比例
    procRightSplitter();


    //右上两栏
    CUIPub::setSpliterFactor(ui->splitter,0,5);
    CUIPub::setSpliterFactor(ui->splitter,1,5);

    //自定义点ME弹出菜单
    pPopMenu = new QMenu;
    nodes_menu_find(pPopMenu);
    nodes_menu_other(pPopMenu);
    nodes_menu_leftbottom(pPopMenu);
    nodes_menu_left_little(pPopMenu);

    CUIPub::setBtnMenu(ui->pushButton_PopMenuClickMe, pPopMenu);

}

void MainWindow::read_CfgFile2List(QStringList &list, QString &filenamevar, QString filename)
{
    list = CFilePub::readFileAllFilterEmptyUniqueNoExistAndVar(filenamevar, filename);
}

void MainWindow::read_FreqUseFile()
{
    read_CfgFile2List(m_ListFreqUse, m_FileNameMenuListFreqUse, "reg/frequse.txt");
}

void MainWindow::update_generate_menu_left()
{
    QMutexLocker update_locker(&m_lock);
    ////debugApp() << "update_generate_menu_left!!";
    //此处删除会异常，正在显示的内容突然被删除
    CUIPub::clearMenuAll(&pRightMouse_L);

    pRightMouse_L = new QMenu(this);
    //可能与此处有关，因为ui->menuGenerate不能释放掉，一直在用，所以此处应该用拷贝
    //    pRightMouse_L->addMenu(CUIPub::copyMenu(ui->menuGenerate));

    pMenuCustom = proc_fromfile_menu(m_FileNameMenu);
    if(pMenuCustom)
    {
        pRightMouse_L->addMenu((pMenuCustom));
    }
    nodes_menu_other(pRightMouse_L);
    nodes_menu_left(pRightMouse_L);
    nodes_menu_leftbottom(pRightMouse_L);
}

/**
 * @brief MainWindow::proc_generate_menu_left
 * @param pos
 * 左边显示生成的菜单
 */
void MainWindow::proc_generate_menu_left(QPoint pos)
{
    Q_UNUSED(pos)
    ////debugApp() << "right mouse clicked!!";
    QCursor cur=this->cursor();
    if((CExpressPub::isFalse(CUIPub::isCheckedQAction(ui->action_background_update)))
            || (CExpressPub::isNullPtr(pRightMouse_L)))
    {
        update_generate_menu_left();
    }
    if(nullptr == pRightMouse_L)
    {
        return;
    }
    pRightMouse_L->exec(cur.pos()); //关联到光标
}

/**
 * @brief MainWindow::proc_generate_menu_right
 * @param pos
 * 右边显示生成的菜单
 */
void MainWindow::proc_generate_menu_right(QPoint pos)
{
    Q_UNUSED(pos)
    CUIPub::clearMenuAll(&pRightMouse_R);

    QCursor cur=this->cursor();
    QMenu *pTempRightMouse_L = new QMenu(this);
    nodes_menu_forwardright(pTempRightMouse_L);
    nodes_menu_right(pTempRightMouse_L);
    nodes_menu_rightbottom(pTempRightMouse_L);
    pTempRightMouse_L->exec(cur.pos()); //关联到光标
}

void MainWindow::proc_generate_menu_cfgAfter(QPoint pos)
{
    Q_UNUSED(pos)
    //    CUIPub::clearMenuAll(&pRightMouse_L);

    QCursor cur=this->cursor();
    QMenu *pTempRightMouse_L = new QMenu(this);
    nodes_menu_cfgAfter(pTempRightMouse_L);
    pTempRightMouse_L->exec(cur.pos()); //关联到光标
}

void MainWindow::proc_generate_menu_leftbottom(QPoint pos)
{
    Q_UNUSED(pos)
    CUIPub::clearMenuAll(&pRightMouse_L);

    QCursor cur=this->cursor();
    pRightMouse_L = new QMenu(this);
    nodes_menu_leftbottom(pRightMouse_L);
    pRightMouse_L->exec(cur.pos()); //关联到光标
}


QMenu *MainWindow::proc_fromfile_menu(QString filename)
{
    QStringList list = CFilePub::readFileAllFilterEmptyUniqueMulti(filename);
    list.sort();
    //    CStringPub::printStringList(list);

    QStringList modelist_alll_execmulti = CFilePub::readFileAllFilterEmptyUniqueMulti(m_FileMode_AllL_ExecMulti);
    QStringList modelist_singl_execmulti = CFilePub::readFileAllFilterEmptyUniqueMulti(m_FileMode_SingleL_ExecMulti);
    QStringList modelist_singl_execsingle = CFilePub::readFileAllFilterEmptyUniqueMulti(m_FileMode_SingleL_ExecSingle);

    if(CExpressPub::isZero(list.length()))
    {
        return nullptr;
    }

    //-------Mode Data begin --------
    foreach (QString item, modelist_singl_execmulti) {
        CMapPub::insertMapFileMode(item, STR_MODE_SINGLELINE_EXECMULTI);
    }
    foreach (QString item, modelist_alll_execmulti) {
        CMapPub::insertMapFileMode(item, STR_MODE_ALALLINE_EXECMULTI);
    }
    foreach (QString item, modelist_singl_execsingle) {
        CMapPub::insertMapFileMode(item, STR_MODE_SINGLELINE_EXECSINGLE);
    }
    //-------Mode Data end  --------

    QMenu *pMenu = nullptr;
    CTreePub::freeTreeMenu();
    foreach (QString item, list) {
        CTreePub::procSubNode(item);
    }
    pMenu = CTreePub::getTreeMenu(CStringPub::stringSelfMenu());
    if(pMenu)
    {
        QObject::disconnect(pMenu, SIGNAL(triggered(QAction *)), this, SLOT(proc_action_gen_custom_action(QAction *)));
        QObject::connect(pMenu, SIGNAL(triggered(QAction *)), this, SLOT(proc_action_gen_custom_action(QAction *)));
    }

    return pMenu;
}


void MainWindow::nodes_menu_left(QMenu *pMenu)
{
    if(CExpressPub::isNullPtr(pMenu))
    {
        return;
    }


    QAction *pActionClearLeft     = CUIPub::createAction("清空");
    QAction *pActionPaste         = CUIPub::createAction("粘贴");
    QAction *pActionSelectCopy = CUIPub::createAction("复制");
    QAction *pActionSelectAllCopy = CUIPub::createAction("全选复制");
    QAction *pActionOpenCfgDir    = CUIPub::createAction("打开配置文件夹");
    QAction *pActionOpenCfgMenu   = CUIPub::createAction("打开配置总表");
    QAction *pActionReload        = CUIPub::createAction("重新加载");
    QAction *pActionLinePacket        = CUIPub::createAction(STR_PROC_PKG_TO_LINE);
    QObject::connect(pActionClearLeft, SIGNAL(triggered()), this, SLOT(proc_actionClearLeft()));
    QObject::connect(pActionPaste, SIGNAL(triggered()), this, SLOT(proc_actionPasteLeft()));
    QObject::connect(pActionSelectCopy, SIGNAL(triggered()), this, SLOT(proc_actionSelectCopy()));
    QObject::connect(pActionSelectAllCopy, SIGNAL(triggered()), this, SLOT(proc_actionSelectAllCopyLeft()));
    QObject::connect(pActionOpenCfgDir, SIGNAL(triggered()), this, SLOT(proc_actionOpenConfigBaseDir()));
    QObject::connect(pActionOpenCfgMenu, SIGNAL(triggered()), this, SLOT(proc_actionOpenCfgMenu()));
    QObject::connect(pActionReload, SIGNAL(triggered()), this, SLOT(proc_actionReload()));
    QObject::connect(pActionLinePacket, SIGNAL(triggered()), this, SLOT(proc_LinePacket()));

    pMenu->addMenu(proc_frequse_menu());
    pMenu->addAction(pActionOpenCfgDir);
    pMenu->addAction(pActionOpenCfgMenu);
    pMenu->addMenu(proc_openfilelist_menu());
    pMenu->addMenu(proc_netsearch_menu());
    pMenu->addAction(pActionClearLeft);
    pMenu->addAction(pActionSelectCopy);
    pMenu->addAction(pActionPaste);
    pMenu->addAction(pActionSelectAllCopy);
    pMenu->addAction(pActionReload);
    pMenu->addAction(pActionLinePacket);

}

//
void MainWindow::nodes_menu_left_little(QMenu *pMenu)
{
    if(CExpressPub::isNullPtr(pMenu))
    {
        return;
    }

    QAction *pActionOpenCfgDir    = CUIPub::createAction("打开配置文件夹");
    QAction *pActionOpenCfgMenu   = CUIPub::createAction("打开配置总表");
    QAction *pActionLinePacket        = CUIPub::createAction(STR_PROC_PKG_TO_LINE);
    QObject::connect(pActionOpenCfgDir, SIGNAL(triggered()), this, SLOT(proc_actionOpenConfigBaseDir()));
    QObject::connect(pActionOpenCfgMenu, SIGNAL(triggered()), this, SLOT(proc_actionOpenCfgMenu()));
    QObject::connect(pActionLinePacket, SIGNAL(triggered()), this, SLOT(proc_LinePacket()));

    pActionLinePacket->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+E", nullptr));

    pMenu->addAction(pActionOpenCfgDir);
    pMenu->addAction(pActionOpenCfgMenu);
    pMenu->addAction(pActionLinePacket);

}

QMenu *MainWindow::proc_frequse_menu()
{
    QMenu *pFreqUse = new QMenu("常用配置列表");
    read_FreqUseFile();
    //更新频繁使用列表
    updateListWidgetFrequse();
    updateListWidgetRecentOpen();
    ////debugApp() << m_ListFreqUse.count();
    foreach (QString item, m_ListFreqUse) {
        QAction *pTmpAction = CUIPub::createActionFull(item);
        pFreqUse->addAction(pTmpAction);
    }

    if(pFreqUse)
    {
        QObject::disconnect(pFreqUse, SIGNAL(triggered(QAction *)), this, SLOT(proc_action_gen_custom_action(QAction *)));
        QObject::connect(pFreqUse, SIGNAL(triggered(QAction *)), this, SLOT(proc_action_gen_custom_action(QAction *)));
    }

    return pFreqUse;
}


QMenu *MainWindow::proc_netsearch_menu()
{
    QMenu *pNetSearch = new QMenu("搜索");
    WORD32 dwLp =  0;
    foreach (QString item, m_NetSearchList) {
        debugApp() << ++dwLp << ":" << item;
        //        printf("No:%-03u -- %-03s\n", ++dwLp, item.toLocal8Bit().data());
        QStringList items = CStringPub::stringSplit(item,';');
        if(item.length() < 2)
        {
            debugApp() << "item split by ; count least at 2:" << item;
            continue;
        }
        QString name = items.at(0);
        QString http = items.at(1);
        QAction *pTmpAction = CUIPub::createActionFull(name);
        pTmpAction->setData(http);
        pNetSearch->addAction(pTmpAction);
    }

    if(pNetSearch)
    {
        QObject::disconnect(pNetSearch, SIGNAL(triggered(QAction *)), this, SLOT(proc_action_netsearch_custom_action(QAction *)));
        QObject::connect(pNetSearch, SIGNAL(triggered(QAction *)), this, SLOT(proc_action_netsearch_custom_action(QAction *)));
    }

    return pNetSearch;
}

QMenu *MainWindow::proc_openfilelist_menu()
{
    QMenu *pOpenFile = new QMenu("文件列表");
    m_listNormalUse = CFilePub::readFileAllFilterEmptyUniqueSort(m_ListOpenFile);
    //定义排序算法，按长度大小 +字符大小
    //想去除特殊符号后排序
    qSort(m_listNormalUse.begin(), m_listNormalUse.end(), [](const QString& s1, const QString& s2)
    {
        QString s1temp = CStringPub::replaceRegLRKuohao2Empty(s1);
        QString s2temp = CStringPub::replaceRegLRKuohao2Empty(s2);
        if(s1temp.length() < s2temp.length())
        {
            return true;
        }
        return s1temp.toInt() < s2temp.toInt();
    });
    foreach (QString item, m_listNormalUse) {
        if(CUIPub::getCheckedQAction(ui->action_checknoexistpath)
                &&CStringPub::contain(CStringPub::replaceRegLRKuohao2Empty(item), "^\\w:"))
        {
            if(CFilePub::pathNoExist(CStringPub::replaceRegLRKuohao2Empty(item)))
            {
                continue;
            }
        }
        QAction *pTmpAction = CUIPub::createActionFull(item);
        pOpenFile->addAction(pTmpAction);
    }

    if(pOpenFile)
    {
        QObject::connect(pOpenFile, SIGNAL(triggered(QAction *)), this, SLOT(proc_action_openfilelist(QAction *)));
    }

    return pOpenFile;
}


void MainWindow::nodes_menu_right(QMenu *pMenu)
{
    if(CExpressPub::isNullPtr(pMenu))
    {
        return;
    }
    QAction *pActionClearRight     = CUIPub::createAction("清空");
    QAction *pActionPaste          = CUIPub::createAction("粘贴");
    QAction *pActionSelectCopy = CUIPub::createAction("复制");
    QAction *pActionSelectAllCopy  = CUIPub::createAction("全选复制");
    QAction *pActionClearEmpty     = CUIPub::createAction("清除空行");
    QObject::connect(pActionClearRight, SIGNAL(triggered()), this, SLOT(proc_actionClearRight()));
    QObject::connect(pActionPaste, SIGNAL(triggered()), this, SLOT(proc_actionPasteRight()));
    QObject::connect(pActionSelectCopy, SIGNAL(triggered()), this, SLOT(proc_actionSelectCopy()));
    QObject::connect(pActionSelectAllCopy, SIGNAL(triggered()), this, SLOT(proc_actionSelectAllCopyRight()));
    QObject::connect(pActionClearEmpty, SIGNAL(triggered()), this, SLOT(proc_actionClearEmpty()));

    pMenu->addAction(pActionClearRight);
    pMenu->addAction(pActionSelectCopy);
    pMenu->addAction(pActionPaste);
    pMenu->addAction(pActionSelectAllCopy);
    pMenu->addAction(pActionClearEmpty);

}

void MainWindow::nodes_menu_cfgAfter(QMenu *pMenu)
{
    if(CExpressPub::isNullPtr(pMenu))
    {
        return;
    }

    QAction *pActionCovertOneLine      = CUIPub::createAction("转一行");
    QAction *pActionCovertMulLine      = CUIPub::createAction("转多行");

    QObject::connect(pActionCovertOneLine, SIGNAL(triggered()), this, SLOT(proc_actionCovertOneLine()));
    QObject::connect(pActionCovertMulLine, SIGNAL(triggered()), this, SLOT(proc_actionCovertMulLine()));

    pMenu->addAction(pActionCovertOneLine);
    pMenu->addAction(pActionCovertMulLine);

}


void MainWindow::nodes_menu_leftbottom(QMenu *pMenu)
{
    if(CExpressPub::isNullPtr(pMenu))
    {
        return;
    }
    QAction *pActionOpenCfgFile    = CUIPub::createAction("打开当前配置文件");
    QAction *pActionOpenCfgDir    = CUIPub::createAction("打开当前配置文件夹");
    QAction *pActionOpenSelectDir    = CUIPub::createAction("打开选中路径");
    QObject::connect(pActionOpenCfgFile, SIGNAL(triggered()), this, SLOT(proc_actionOpenConfigFile()));
    QObject::connect(pActionOpenCfgDir, SIGNAL(triggered()), this, SLOT(proc_actionOpenConfigDir()));
    QObject::connect(pActionOpenSelectDir, SIGNAL(triggered()), this, SLOT(proc_pActionOpenSelectDir()));

    pActionOpenCfgFile->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));

    pMenu->addAction(pActionOpenCfgFile);
    pMenu->addAction(pActionOpenCfgDir);
    pMenu->addAction(pActionOpenSelectDir);
}

void MainWindow::nodes_menu_rightbottom(QMenu *pMenu)
{
    if(CExpressPub::isNullPtr(pMenu))
    {
        return;
    }
    QAction *pActionOpenCfgFile    = CUIPub::createAction("打开当前配置文件");
    QAction *pActionOpenCfgDir    = CUIPub::createAction("打开当前配置文件夹");
    QObject::connect(pActionOpenCfgFile, SIGNAL(triggered()), this, SLOT(proc_actionOpenConfigFileR()));
    QObject::connect(pActionOpenCfgDir, SIGNAL(triggered()), this, SLOT(proc_actionOpenConfigDirR()));

    pMenu->addAction(pActionOpenCfgFile);
    pMenu->addAction(pActionOpenCfgDir);
}

void MainWindow::nodes_menu_find(QMenu *pMenu)
{
    if(CExpressPub::isNullPtr(pMenu))
    {
        return;
    }
    QAction *pActionReSearchResult    = CUIPub::createAction("重查结果");
    QObject::connect(pActionReSearchResult, SIGNAL(triggered()), this, SLOT(on_action_researchresult_triggered()));
    pActionReSearchResult->setShortcut(QCoreApplication::translate("MainWindow", "ALT+R", nullptr));

    QAction *pActionFind    = CUIPub::createAction("查找");
    QObject::connect(pActionFind, SIGNAL(triggered()), this, SLOT(on_action_search_triggered()));

    pMenu->addAction(pActionReSearchResult);
    pMenu->addAction(pActionFind);
}

void MainWindow::nodes_menu_other(QMenu *pMenu)
{
    if(CExpressPub::isNullPtr(pMenu))
    {
        return;
    }
    QAction *pActionForward   = CUIPub::createAction("转到");

    QObject::connect(pActionForward, SIGNAL(triggered()), this, SLOT(proc_ActionForward()));

    pMenu->addAction(pActionForward);
}

void MainWindow::nodes_menu_forwardright(QMenu *pMenu)
{
    if(CExpressPub::isNullPtr(pMenu))
    {
        return;
    }
    QAction *pActionForward   = CUIPub::createAction("转到");

    QObject::connect(pActionForward, SIGNAL(triggered()), this, SLOT(proc_ActionForwardRight()));

    pMenu->addAction(pActionForward);
}


void MainWindow::read_Setting()
{
    read_HistorySetting();
    add_MenuCodeFormatRecent();
    add_MenuDocumentOpenRecent();
    add_MenuDocumentSearchRecent();
    hide_PushButtonSets();
}

void MainWindow::proc_HistorySetting(int type)
{
    quint8 ucType = type;
    m_pSettings = CUIPub::read_HistorySettings(m_organization,m_application);
    CUIPub::procStringList(m_pSettings, BINDSTRWORDS(recentfiles_codeformat), ucType);
    CUIPub::procStringList(m_pSettings, BINDSTRWORDS(recentfiles_document), ucType);
    CUIPub::procString(m_pSettings, BINDSTRWORDS(openFilePathRecent), ucType);
    CUIPub::procString(m_pSettings, BINDSTRWORDS(openDirPathRecent), ucType);
    CUIPub::procString(m_pSettings, BINDSTRWORDS(openWordFilePathRecent), ucType);
    CUIPub::procAction(m_pSettings, ui->action_SwitchClearLeftText, ucType);
    CUIPub::procAction(m_pSettings, ui->action_ClipBoarChange, ucType);
    CUIPub::procAction(m_pSettings, ui->action_checknoexistpath, ucType);
    CUIPub::procAction(m_pSettings, ui->action_background_update, ucType);
    CUIPub::procAction(m_pSettings, ui->action_hidebuttonswitch, ucType);
    CUIPub::procAction(m_pSettings, ui->action_manycontent_proc, ucType);
    CUIPub::procAction(m_pSettings, ui->action_autoconvertaf, ucType);
    CUIPub::procAction(m_pSettings, ui->action_recentopen, ucType);
    CUIPub::procAction(m_pSettings, ui->actionA_B_multiline_multiproc, ucType);
}

void MainWindow::read_HistorySetting()
{
    proc_HistorySetting(CUIPub::TYPE_READ);
}


void MainWindow::write_HistorySetting()
{
    proc_HistorySetting(CUIPub::TYPE_WRITE);
}


void MainWindow::proc_menu_codeFormat_Recent(QAction *action)
{
    QStringList autolist = CStringPub::actionNameList(action);
    CHECKSIZEZERORETURN(autolist);
    proc_action_codeFormat_Pub(TYPE_AUTO,autolist);
}
/**
 * @brief MainWindow::proc_action_codeFormat_Directory
 * 代码格式化，如何处理呢
 * 指定一个文件夹或文件来格式化吗
 */
void MainWindow::proc_action_codeFormat_Directory()
{
    QStringList autolist;
    //    ////debugApp() << "proc_action_codeFormat_Directory";
    proc_action_codeFormat_Pub(TYPE_DIR,autolist);
}

/**
 * @brief MainWindow::proc_action_codeFormat_File
 * 指定一个文件
 */
void MainWindow::proc_action_codeFormat_File()
{
    QStringList autolist;
    //    ////debugApp() << "proc_action_codeFormat_File";
    proc_action_codeFormat_Pub(TYPE_FILES,autolist);
}

void MainWindow::proc_action_codeFormat_Edit_Config()
{
    ui->textEdit->setText(CFilePub::readFileAll(cfgAstyleName));
    show_Status("编译Asytle配置....");
}

void MainWindow::proc_action_codeFormat_Save_Config()
{
    QString result = ui->textEdit->toPlainText();
    if(result.trimmed().isEmpty())
    {
        show_Status("内容为空，不允许!!");
        return;
    }
    CFilePub::writeFileOnlly(cfgAstyleName, result);
    show_Status("保存Asytle配置成功");
}
void MainWindow::proc_action_codeFormat_Del_Config()
{
    CFilePub::deleteFile(cfgAstyleName);
    show_Status("删除Asytle配置成功");
}

void MainWindow::proc_action_about()
{
    ////debugApp() << CAlgorithmPub::getMd5SumOfFile(m_apppath);
    //    ////debugApp() << CStringPub::getCurrentExePath();
    CLogPub::logDefault(m_apppath);
    show_Status(QString("当前版本是:") + APP_VERSION
                + CSignPub::signEnter()
                + CStringPub::getDateTime()
                + CSignPub::signEnter()
                + CAlgorithmPub::getMd5SumOfFile(m_apppath)
                );
}

void MainWindow::proc_action_attention()
{
    CUIPub::showBoxInfoIsNo(CFilePub::readFileAll(m_AttentionFile));
}

void MainWindow::proc_action_attentionnew()
{
    //    CUIPub::showBoxInfoIsNo(CFilePub::readFileAll(m_AttentionFile));
    QString showtext = CFilePub::readFileAll(m_AttentionFile);
    CDialogAbout *pDiaglogAbout = new CDialogAbout();
    pDiaglogAbout->setText(showtext);
    pDiaglogAbout->exec();
    delete pDiaglogAbout;
}


void MainWindow::proc_action_codeFormat_Pub(int openType,QStringList autolist)
{
    ////debugApp() << "proc_action_codeFormat_Pub";
    get_NameFilter();

    switch (openType) {
    case TYPE_FILES:
    {
        /*打开一个dialog对话框，选择一个文件*/
        QStringList openfiles = QFileDialog::getOpenFileNames(nullptr, "请选择格式化的文件"
                                                              , openFilePathRecent
                                                              , CStringPub::getOpenFileNamesFilter(nameFilters, SIGNFENHAO) + SIGNFENHAO + "*.*");
        if(openfiles.isEmpty())
        {
            return;
        }
        ////debugApp() << "Open Files:" << openfiles;
        openFilePathRecent = openfiles.at(0);
        recentfiles_codeformat.append(openfiles);
        proc_AstyleInstance(openfiles);

    }
        break;
    case TYPE_FILES_NOUI:
    {
        /*打开一个dialog对话框，选择一个文件*/
        ////debugApp() << "Open Files:" << autolist;
        proc_AstyleInstance(autolist);
        recentfiles_codeformat.append(autolist);
    }
        break;
    case TYPE_DIR:
    {
        /*打开一个dialog对话框，选择一个文件夹*/
        //文件夹路径
        QStringList openfiles =CFilePub::getExistDirAllFiles("请选择格式化的文件夹",
                                                             openDirPathRecent,
                                                             recentfiles_codeformat,
                                                             nameFilters
                                                             );
        proc_AstyleInstance(openfiles);
    }
        break;
    case TYPE_DIR_NOUI:
    {
        if(autolist.size() == 0)
        {
            return;
        }
        //文件夹路径
        QString openDirPath = autolist.at(0);
        if (openDirPath.isEmpty())
        {
            return;
        }
        ////debugApp() << "Open Dir:" << openDirPath;
        recentfiles_codeformat.append(openDirPath);
        QStringList openfiles = CFilePub::getFileAllAbsoluteNames(nameFilters, openDirPath);
        proc_AstyleInstance(openfiles);
    }
        break;
    case TYPE_AUTO:
    {
        recentfiles_codeformat.append(autolist);
        foreach (QString item, autolist) {
            if(true == CFilePub::isFile(item))
            {
                proc_action_codeFormat_Pub(TYPE_FILES_NOUI, autolist);
            }
            else if(true == CFilePub::isDir(item))
            {
                proc_action_codeFormat_Pub(TYPE_DIR_NOUI, autolist);
            }
        }
    }
        break;
    default:
        break;
    }
}



WORD32 MainWindow::get_AstyleFmt(QStringList filelist)
{
    get_AstyleConfig();
    listAstyleArgv << (filelist);
    m_argvp = new char*[listAstyleArgv.size()];
    int i = 0;
    foreach (QString item, listAstyleArgv) {
        WORD32 dwLen = strlen(item.toUtf8().data());
        char *p = new char[dwLen + 1];
        memset(p,0,dwLen + 1);
        strcpy(p, item.toUtf8().data());
        m_argvp[i++] = p;
    }

    //    CPrintPub::printArray((char **)m_argvp, listAstyleArgv.size());
    add_MenuCodeFormatRecent();

    return listAstyleArgv.size();
}

void MainWindow::free_Argv()
{
    WORD32 i = 0;
    for (i = 0; i < dwArgc;i++) {
        delete m_argvp[i];
        m_argvp[i] = nullptr;
    }
}


void MainWindow::proc_AstyleInstance(QStringList filelist)
{
    if(0 == filelist.size())
    {
        show_Status("文件数量为空，不处理");
        return;
    }

    if(filelist.size() > ASTYLE_PROC_FILES_MAX)
    {
        show_Status("文件数量较多，建议不处理");
        int result = QMessageBox::warning(nullptr, "warning", QString("文件数量较多 %1，是否继续处理?").arg(filelist.size()), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        switch (result)
        {
        case QMessageBox::Yes:
            break;
        case QMessageBox::No:
            return;
            break;
        default:
            return;
            break;
        }
    }

    CPrintPub::printToFile(logAstyleName);

    dwArgc = get_AstyleFmt(filelist);
    AyStyleMain(dwArgc, m_argvp);
    ////debugApp() << "Astyle done:" << filelist;
    free_Argv();
    CPrintPub::canclePrintToFile();

    show_Status("deal done! etc" + filelist.at(0));
    show_TextBrower("Astyle following files deal done!" SIGNENTER + CStringPub::stringList2String(listAstyleArgv,SIGNENTER));
}


void MainWindow::show_Status(QString msg)
{
    ui->statusbar->showMessage(msg);
    if(1)
    {
        show_StatusTimer(msg);
    }
}

void MainWindow::show_StatusOnly(QString msg)
{
    ui->statusbar->showMessage(msg);
}

void MainWindow::show_StatusTimer(QString msg)
{
#if 0
    /**
     * @brief EXECLOOP 测试内存泄漏
     */
    EXECLOOP(ShowTipsInfoWithShowTime(msg, 2000), 100);
#else
    ShowTipsInfoWithShowTime(msg, 2000);
#endif
}

void MainWindow::show_StatusTimerWindowTitle(QString msg)
{
    show_StatusTimer(msg);
    setWindowTitle(msg);
}

void MainWindow::show_TextBrower(QString msg)
{
    ui->textBrowser->setText(msg);
}

void MainWindow::show_TextBrowerAppend(QString msg)
{
    ui->textBrowser->append(msg);
}


void MainWindow::get_AstyleConfig()
{
    QFile file(cfgAstyleName);
    if(file.exists())
    {
        if(!file.open(QIODevice::ReadOnly))
        {
            return;
        }
        listAstyleArgv = CStringPub::toStringList(file.readAll().split(SIGNENTERS));
        file.close();
        /**
  ** 内容为空时，无法正常工作，使用原始配置
  **/
        if(0 == listAstyleArgv.size())
        {
            listAstyleArgv = CStringPub::toStringList(CFilePub::readFileAll(cfgAstyleNameOrg).toUtf8().split(SIGNENTERS));
        }
    }
    else
    {
        QString result("");
        get_AstyleOrgConfig();
        foreach (QString item, listAstyleArgv) {
            result += item + SIGNENTER;
        }
        CFilePub::writeFileOnlly(cfgAstyleNameOrg,result);
        CFilePub::writeFileOnlly(cfgAstyleName,result);
    }
}

void MainWindow::get_AstyleOrgConfig()
{
    listAstyleArgv.clear();
    listAstyleArgv << ("app.exe");
    listAstyleArgv << ("--style=allman");
    listAstyleArgv << ("--style=ansi");
    listAstyleArgv << ("--style=bsd");
    listAstyleArgv << ("--style=break");
    listAstyleArgv << ("-A1");
    listAstyleArgv << ("-s4");
    listAstyleArgv << ("-S");
    listAstyleArgv << ("-N");
    listAstyleArgv << ("-L");
    listAstyleArgv << ("-m0");
    listAstyleArgv << ("-M40");
    listAstyleArgv << ("--convert-tabs");
    listAstyleArgv << ("--suffix=.pre");
    listAstyleArgv << ("--indent-switches");
    listAstyleArgv << ("--pad-return-type");
    listAstyleArgv << ("-xq");
    listAstyleArgv << ("--keep-one-line-statements");
    listAstyleArgv << ("--indent-preproc-block");
    //        listAstyleArgv << ("-xW ");
    //char *argv[] = {" --style=allman  --style=ansi  --style=bsd  --style=break  -A1  --indent-switches  -S  --pad-return-type  -xq  --keep-one-line-statements  -o  --add-braces  -j  --max-continuation-indent=#  /  -M#  --indent-continuation=#  /  -xt#  --indent-preproc-block  -xW ", item.toUtf8().data()};

}

void MainWindow::get_NameFilter()
{
    nameFilters.clear();
    nameFilters << "*.c";
    nameFilters << "*.cpp";
    nameFilters << "*.cxx";
    nameFilters << "*.h";
    nameFilters << "*.hpp";
    nameFilters << "*.java";
}

void MainWindow::add_MenuRecent(QStringList recent, QMenu *pMenu)
{
    recent = CStringPub::stringUniqueSortReverse(recent);

    //先删除当前节点
    CUIPub::clearMenuItems(pMenu);

    WORD32 dwLp = 0;
    foreach (QString item, recent) {
        if(dwLp > FILES_ASTYLE_RECENT_MAX)
        {
            break;
        }

        if(CFilePub::fileExist(item))
        {
            CUIPub::addMenu(pMenu, item);
            dwLp++;
        }
    }
}


void MainWindow::add_MenuCodeFormatRecent()
{
    add_MenuRecent(recentfiles_codeformat, ui->menu_codeFormat_Recent);
}

void MainWindow::add_MenuDocumentOpenRecent()
{
    add_MenuRecent(recentfiles_document, ui->menu_document_open_recent);
}

void MainWindow::add_MenuDocumentSearchRecent()
{
    add_MenuRecent(recentfiles_document, ui->menu_document_search_recent);
}

void MainWindow::set_LeftTextEdit(QString str)
{
    //    ui->textEdit->setText(str);
    ui->textEdit->setPlainText(str);
}

void MainWindow::clear_LeftTextEdit()
{
    ui->textEdit->setText("");
}

void MainWindow::set_RightTextEdit(QString str)
{
    //    ui->textBrowser->setText(str);
    ui->textBrowser->setPlainText(str);
}

void MainWindow::clear_RightTextEdit()
{
    ui->textBrowser->setText("");
}

QStringList MainWindow::proc_action_office_auto_pub(QString filter, QStringList filterlist, QString &openRecent, QStringList &recentfiles, quint8 openDiagFlag, QStringList openfilelist)
{
    QStringList list;
    switch (openDiagFlag) {
    case OPENTYPE_YES_FILE:
    {
        list = CFilePub::getOpenDiagFilesRecent(openRecent,filter);
        if(list.size() == 0)
        {
            return CStringPub::emptyStringList();
        }
        recentfiles.append(list.at(0));
    }
        break;

    case OPENTYPE_YES_DIR:
    {
        list = CFilePub::getExistDirAllFiles(STRING_PLEASE_SELECT_DIR, openRecent, recentfiles, filterlist);
    }
        break;
    case OPENTYPE_NO_FILE:
    {
        list.append(openfilelist);
        recentfiles.append(openfilelist);
    }
        break;
    case OPENTYPE_NO_DIR:
    {
        //        list.append(openfilelist);
        //        CHECKSIZEZERORETURN(openfilelist);
        list = CFilePub::getFileAllAbsoluteNames(filterlist, openfilelist.at(0));
        //        recentfiles.append(openfilelist);
    }
        break;
    default:
        break;
    }
    return list;
}



void MainWindow::proc_action_office_action_pub(quint8 ucActionType, QStringList list,QString findtext)
{

#ifdef WIN32
    QString filename;
    int ret =0;
    switch (ucActionType) {
    case ACTIONTYPE_OPEN:
    {
        filename = list.at(0);

        ret = CFilePub::isFile(filename);
        CHECKFALSE_TIPS_RETURN(ret, show_Status, STRING_TIPS_DIR_NO_SUPPORT);

        ret = CFilePub::fileExist(filename);
        CHECKFALSE_TIPS_RETURN(ret, show_Status, STRING_TIPS_FILE_NO_EXIST);

        COfficePub *pObjOffice = new COfficePub();
        set_RightTextEdit(pObjOffice->readWord(filename));
        show_Status("打开文档成功!" + filename);
    }
        break;
    case ACTIONTYPE_SEARCH:
    {
        filename = list.at(0);

        ret = CFilePub::fileExist(filename);
        CHECKFALSE_TIPS_RETURN(ret, show_Status, STRING_TIPS_FILE_NO_EXIST);

        COfficePub *pObjOffice = new COfficePub(findtext);
        set_RightTextEdit(pObjOffice->readWordFindText(filename));
        set_LeftTextEdit(findtext);
        show_Status("查找文档结束!" + filename);
    }
        break;
    case ACTIONTYPE_SEARCH_ALLFILES:
    {
        QProgressBar *pProgressBar = new QProgressBar(this);
        QString result("");
        COfficePub *pObjOffice = new COfficePub(findtext);
        int cur = 0;
        QString singres("");
        foreach (QString item, list) {
            qApp->processEvents();
            singres = pObjOffice->readWordFindText(item);
            if(singres.trimmed().isEmpty())
            {
                continue;
            }
            ////debugApp() << "[OpenFile]" + item ;
            result+="[OpenFile]" + item + SIGNENTER;
            result+=singres + SIGNENTER;
            cur++;
            CUIPub::progressBar(pProgressBar,cur, list.size());
        }
        delete  pProgressBar;
        set_RightTextEdit(result);
        set_LeftTextEdit(findtext);
        show_Status("查找文档结束!" + list.at(0));
    }
        break;
    default:
        break;
    }
    update_Recent(recentfiles_document,  ui->menu_document_search_recent);
    update_Recent(recentfiles_document,  ui->menu_document_open_recent);
#else
    Q_UNUSED(ucActionType)
    Q_UNUSED(list)
    Q_UNUSED(findtext)
#endif
}

/**
 * @brief MainWindow::proc_action_office_open_pub
 * @param filter
 * @param openRecent
 * @param openDiagFlag 是否打开对话框
 * @param openfilelist
 */
void MainWindow::proc_action_office_open_pub(QString filter,QStringList filterlist,  QString &openRecent,quint8 openDiagFlag, QStringList openfilelist)
{
    QStringList list = proc_action_office_auto_pub(filter, filterlist, openRecent, recentfiles_document, openDiagFlag, openfilelist);
    CHECKSIZEZERORETURN(list);
    proc_action_office_action_pub(ACTIONTYPE_OPEN, list, CStringPub::emptyString());
}


void MainWindow::proc_action_office_search_file_pub(QString filter,QStringList filterlist, QString openRecent, quint8 openDiagFlag, QStringList openfilelist)
{
    QString findtext;
    CHECKFALSERETURN(get_DialogFindText(findtext));
    QStringList list = proc_action_office_auto_pub(filter, filterlist, openRecent, recentfiles_document, openDiagFlag, openfilelist);
    CHECKSIZEZERORETURN(list);
    proc_action_office_action_pub(ACTIONTYPE_SEARCH, list, findtext);
}

void MainWindow::proc_action_office_search_dir_pub(QString filter,QStringList filterlist, QString openRecent, quint8 openDiagFlag, QStringList openfilelist)
{
    QString findtext;
    CHECKFALSERETURN(get_DialogFindText(findtext));
    CHECKEMPTY_TIPS_RETURN(findtext,show_Status, STRING_INPUT_FIND_KEY_EMPTY);
    QStringList list = proc_action_office_auto_pub(filter, filterlist, openRecent, recentfiles_document, openDiagFlag, openfilelist);
    CHECKSIZEZERO_TIPS_RETURN(list,show_Status, STRING_RES_FIND_FILES_EMPTY);
    proc_action_office_action_pub(ACTIONTYPE_SEARCH_ALLFILES, list, findtext);
}


void MainWindow::proc_action_office_search_file()
{
    proc_action_office_search_file_pub(FILTERWORD, CStringPub::emptyStringList(),  openWordFilePathRecent, OPENTYPE_YES_FILE, CStringPub::emptyStringList());
}

void MainWindow::proc_action_office_search_dir()
{
    proc_action_office_search_dir_pub(FILTERWORD, CStringPub::wordNameFilter(), openWordFilePathRecent, OPENTYPE_YES_DIR, CStringPub::emptyStringList());
}



quint8 MainWindow::get_DialogFindText(QString &findtext)
{
    quint8 ucresult = false;
    QString result("");

    init_Dialog();
    int ret=pDialog->exec () ;// 以模态方式显示对话框
    if (ret==QDialog::Accepted)
    { //OK按钮被按下，获取对话框上的输入，设置行数和列数
        findtext = uiDialog->textEdit->toPlainText();
        ucresult = true;
    }
    delete pDialog;
    delete uiDialog;

    ////debugApp() << "Word Find Text:" << findtext;
    set_LeftTextEdit("Word Find Text:" + findtext);

    return ucresult;
}




void MainWindow::update_Recent(QStringList &list, QMenu *pMenu)
{
    add_MenuRecent(list,pMenu);
}

void MainWindow::update_RecentAppend(QStringList &list, QString name, QMenu *pMenu)
{
    list.append(name);
    add_MenuRecent(list,pMenu);
}


void MainWindow::proc_action_office_open()
{
    proc_action_office_open_pub(FILTERWORD, CStringPub::emptyStringList(), openWordFilePathRecent, OPENTYPE_YES_FILE, CStringPub::emptyStringList());
}

void MainWindow::proc_menu_document_open_recent(QAction *action)
{
    QStringList autolist = CStringPub::actionNameList(action);
    CHECKSIZEZERORETURN(autolist);
    proc_action_office_open_pub(FILTERWORD, CStringPub::emptyStringList(), openWordFilePathRecent, OPENTYPE_NO_FILE, autolist);
}

void MainWindow::proc_menu_document_search_recent(QAction *action)
{
    QStringList autolist = CStringPub::actionNameList(action);
    CHECKSIZEZERORETURN(autolist);

    if(CFilePub::isDir(action->iconText()))
    {
        proc_action_office_search_dir_pub(FILTERWORD, CStringPub::wordNameFilter(), openWordFilePathRecent, OPENTYPE_NO_DIR, autolist);
    }
    else
    {
        proc_action_office_search_file_pub(FILTERWORD,CStringPub::emptyStringList(),  openWordFilePathRecent, OPENTYPE_NO_FILE, autolist);
    }
}



void MainWindow::closeEvent(QCloseEvent *event)
{
    ////debugApp() << "closeEvent";
    write_HistorySetting();
    //窗口关闭事件，必须结束线程
    if (threadMonitor.isRunning())
    {
        threadMonitor.stopThread();
        threadMonitor.wait();
    }
    event->accept();
}


bool MainWindow::eventFilter_ui_textEdit(QObject *target, QEvent *event)
{
    //    qDebug("eventFilter_ui_textEdit");

    if (target == ui->textEdit)
    {
        //        //双击出现listView界面
        //        if (event->type() == QEvent::MouseButtonDblClick) {
        //            return true;
        //        }
        //        //单击隐藏listView界面
        //        if (event->type() == QEvent::MouseButtonPress) {
        //            return true;
        //        }
        //按键处理
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            Qt::KeyboardModifiers modifiers = keyEvent->modifiers();
            int key = keyEvent->key();

            // 应该写成
            if(modifiers == Qt::ControlModifier || modifiers & Qt::ControlModifier)
            {
                // 再判断按键
                // 这里需要判断小键盘的情况
                if(key == Qt::Key_J)  // 这里有两种触发形式直接按end键、或者shift+小键盘1--小键盘也可能不响应
                {
                    qDebug()<<"Ctrl+J";
                    duplicate_current_line_ui_textEdit();
                }
            }

        }
    }
    return QObject::eventFilter(target, event);
}

bool MainWindow::eventFilter_ui_textEdit_Tips(QObject *target, QEvent *event)
{
    if (target == ui->textEdit_cfgTips)
    {
        //按键处理
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            Qt::KeyboardModifiers modifiers = keyEvent->modifiers();
            int key = keyEvent->key();

            // 应该写成
            if(modifiers == Qt::ControlModifier || modifiers & Qt::ControlModifier)
            {
                // 再判断按键
                // 这里需要判断小键盘的情况
                if(key == Qt::Key_J)  // 这里有两种触发形式直接按end键、或者shift+小键盘1--小键盘也可能不响应
                {
                    qDebug()<<"Ctrl+J";
                    duplicate_current_line_ui_textEdit_Tips();
                }
            }

        }
    }
    return QObject::eventFilter(target, event);
}

bool MainWindow::duplicate_current_line_ui_textEdit()
{
    return CUIPub::duplicateSelectLine(ui->textEdit);
}

bool MainWindow::duplicate_current_line_ui_textEdit_Tips()
{
    return CUIPub::duplicateSelectLine(ui->textEdit_cfgTips);
}


bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    eventFilter_ui_textEdit(target, event);
    eventFilter_ui_textEdit_Tips(target, event);

    return QObject::eventFilter(target, event);
}


void MainWindow::clearDialogText()
{
    uiDialog->textEdit->clear();
}

void MainWindow::pasteDialogText()
{
    uiDialog->textEdit->setText(CUIPub::getClipBoardText());
}

void MainWindow::create_thread_network(CNetThreadPub *&pTthread, handler_retint_nopara hander, qint8 checkrunning = true)
{
    if(checkrunning && pTthread && pTthread->isRunning())
    {
        show_Status("正在运行中...");
        return;
    }

    show_Status("开始运行");
    CHECKNEWMEMRETURN(pTthread = new CNetThreadPub(hander));
    pTthread->start();

    connect(pTthread,&CNetThreadPub::message
            ,this,&MainWindow::proc_threadmessage);
    connect(pTthread,&CNetThreadPub::progress
            ,this,&MainWindow::proc_threadprogress);
    connect(pTthread,&CNetThreadPub::finished
            ,this,&MainWindow::proc_threadfinished);
    connect(pTthread, SIGNAL(finished()), pTthread, SLOT(deleteLater())); //线程释放自己
}


void MainWindow::proc_action_net_server()
{
    //#if UT_TESTCASE
    //    EXECLOOP(create_thread_network(m_thread_server, CNetWorkPub::startServer),100);
    //#else
    //    EXECLOOP(create_thread_network(m_thread_server, CNetWorkPub::startServer),1)
    //        #endif
}

void MainWindow::proc_threadmessage(const QString& info)
{
    UNUSED(info);
    ////debugApp() << "recv message:" << info;
}

void MainWindow::proc_threadprogress(int progress)
{
    UNUSED(progress);
    ////debugApp() << "progress:" << progress;
}

void MainWindow::proc_threadfinished()
{
    ////debugApp() << "threadfinished:" ;
}




void MainWindow::proc_action_net_client()
{
    //#if UT_TESTCASE
    //    EXECLOOP(create_thread_network(m_thread_client,CNetWorkPub::startClient),100);
    //#else
    //    EXECLOOP(create_thread_network(m_thread_client,CNetWorkPub::startClient),1);
    //#endif
}

void MainWindow::proc_action_net_publish()
{
    //#if UT_TESTCASE
    //    EXECLOOP(create_thread_network(m_thread_client,CNetWorkPub::startPublish),100);
    //#else
    //    EXECLOOP(create_thread_network(m_thread_publish,CNetWorkPub::startPublish),1);
    //#endif
}


void MainWindow::proc_action_net_subscribe()
{
    //#if UT_TESTCASE
    //    EXECLOOP(create_thread_network(m_thread_client,CNetWorkPub::startSubscribe),100);
    //#else
    //    EXECLOOP(create_thread_network(m_thread_subscribe,CNetWorkPub::startSubscribe,false),1);
    //#endif
}

void MainWindow::proc_mode_AB_multiline_multiproc(T_RegExpParas &tPara)
{
    if(CUIPub::getCheckedQAction(ui->actionA_B_multiline_multiproc))
    {
        tPara.ucMultLineMultiProcMode = A_MODE_MULTILINE_MULTIPROC;
    }
    else
    {
        tPara.ucMultLineMultiProcMode = B_MODE_MULTILINE_MULTIPROC;
    }
}



void MainWindow::proc_action_gen_pub(QString configfilename, int type)
{
    QString keyword   = CUIPub::getSelectTextEdit(ui->textEdit);
    QString linewords = CUIPub::getSelectLineTextEdit(ui->textEdit);
    QString lefttext  = CUIPub::getTextEdit(ui->textEdit);
    QString proctext  = CStringPub::emptyString();
    T_RegExpParas tPara;

    ////debugApp() << "keyword:" << keyword;
    ////debugApp() << "linewords:" << linewords;

    if(CExpressPub::isZero(CStringPub::strSimLen(keyword)) && CExpressPub::isZero(CStringPub::strSimLen(lefttext)))
    {
        CUIPub::setPlainTextEditOnEmpty(ui->textEdit, CRegExpPub::handlerTip(configfilename, type, CRegExpPub::FILE_TIPS));
        set_RightTextEdit(CStringPub::emptyString());
        //如果提示不为空时，则重新调用接口
        if(CExpressPub::isFull(CUIPub::getTextEditLen(ui->textEdit)))
        {
            proc_action_gen_pub(configfilename, type);
        }
        return;
    }
    else if(CExpressPub::isFull(CStringPub::strSimLen(keyword)))
    {
        proctext = linewords;
    }
    else
    {
        proctext = lefttext;
    }

    ////debugApp() << "proctext:" << proctext;
    quint32 dwContentMax = MANYCONTENTMAX;

    if(false == CUIPub::isCheckedQAction(ui->action_manycontent_proc))
    {
        dwContentMax = CFilePub::getNumFirstFromFileLimitMin(m_FileNameContentMax, MANYCONTENTMAX);
        if(CStringPub::strSimLen(proctext) >= dwContentMax)
        {
            show_StatusTimer(QString("内容超过处理范围%1").arg(dwContentMax));
            set_RightTextEdit(proctext);
            return;
        }
    }

    tPara.classconfig = configfilename;
    tPara.dwClasstype = type;
    tPara.text = proctext;
    proc_mode_AB_multiline_multiproc(tPara);

    set_RightTextEdit(CRegExpPub::procTextByRegExpList(tPara));
}

void MainWindow::proc_action_edit_pub(QString configfilename, int type)
{
    QString proctext  = CStringPub::emptyString();

    ////debugApp() << "configfilename:" << configfilename;
    ////debugApp() << "type          :" << type;
    CUIPub::setPlainTextEdit(ui->textEdit_cfgTips, CRegExpPub::handlerTip(configfilename, type,CRegExpPub::FILE_TIPS));
    CUIPub::setPlainTextEdit(ui->textEdit_cfgBefore, CRegExpPub::handlerTip(configfilename, type, CRegExpPub::FILE_BEFORE));
    CUIPub::setPlainTextEdit(ui->textEdit_cfgAfter, CRegExpPub::handlerTip(configfilename, type, CRegExpPub::FILE_AFTER));
    if(proc_action_edit_convertline_pub(configfilename))
    {
        proc_actionCovertMulLine();
    }
}

bool MainWindow::proc_action_edit_convertline_pub(QString configfilename)
{
    if(false == CUIPub::getCheckedQAction(ui->action_autoconvertaf))
    {
        return false;
    }
    QStringList modelist_alll_execmulti = CFilePub::readFileAllFilterEmptyUniqueMulti(m_FileMode_AllL_ExecMulti);


    foreach (QString item, modelist_alll_execmulti) {
        if(configfilename == item)
        {
            return false;
        }
    }
    return true;
}



void MainWindow::proc_action_editinginfo(QString configfilename, int type)
{
    Q_UNUSED(type)
    proc_action_edit_pub(configfilename, EUM_CLASSTYPE::EDIT_CFGFILE_OPERATIONS);
    CStringPub::setString(m_EditConfig, configfilename);
    show_StatusTimerWindowTitle(QString("编译配置文件中【%1】").arg(m_EditConfig));
}

void MainWindow::proc_action_deleteinfo(QString configfilename, int type)
{
    Q_UNUSED(type)

    if(CUIPub::showBoxInfoIsNo(QString("确认删除配置文件%1").arg(configfilename)))
    {
        return;
    }
    show_StatusTimerWindowTitle(QString("删除配置文件【%1】").arg(configfilename));

    CFilePub::deleteFile(CRegExpPub::getRegExpFileNameBefore(CRegExpPub::getFileNameByClassCfgType(configfilename, type)));
    CFilePub::deleteFile(CRegExpPub::getRegExpFileNameAfter(CRegExpPub::getFileNameByClassCfgType(configfilename, type)));
    CFilePub::deleteFile(CRegExpPub::getRegExpFileNameTips(CRegExpPub::getFileNameByClassCfgType(configfilename, type)));

    CFilePub::deleteFileSameLineExt(m_FileNameMenu, configfilename);
    CFilePub::deleteFileSameLineExt(m_FileNameMenuListFreqUse, configfilename);
    CStringPub::deleteListItem(m_ListFreqUse,configfilename);

    //更新列表
    //重新执行查找过程
    on_action_search_triggered_handle(0);
    //更新左侧列表
    updateListWidgetFrequse();
}


/**
 * @brief MainWindow::proc_action_gen_custom_action
 * @param pAction
 * 自定义菜单，右键
 */
void MainWindow::proc_action_gen_custom_action(QAction *pAction)
{
    ////debugApp() << "custom action:" << pAction->text();
    ////debugApp() << "custom data  :" << pAction->data();

    QString totalstr = pAction->data().toString();
    QStringList actlist = CStringPub::stringSplit(totalstr, CSignPub::signFenHaoC());
    QString cfgFirst = CStringPub::emptyString();
    QString cfgMode = CStringPub::emptyString();
    if(CExpressPub::isFull(actlist.count()))
    {
        cfgFirst = actlist.at(0);
    }

    if(actlist.count() > 1)
    {
        cfgMode  = actlist.at(1);
    }

    if(CUIPub::isCheckedQAction(ui->action_SwitchClearLeftText))
    {
        CUIPub::clearTextEdit(ui->textEdit);
    }

    //编辑配置文件模式
    if(CUIPub::isCheckedQAction(ui->action_EditCfgFile))
    {
        proc_action_editinginfo(cfgFirst,0);
        return;
    }

    //删除配置文件模式
    if(CUIPub::isCheckedQAction(ui->action_DeleteCfgFile))
    {
        proc_action_deleteinfo(cfgFirst,0);
        return;
    }


    CStringPub::setString(m_EditConfig, cfgFirst);
    proc_action_gen_pub(cfgFirst, EUM_CLASSTYPE::COMMON_OPERATIONS);
    setWindowTitle(QString("生成代码【%1】").arg(m_EditConfig));
    proc_frequse_config(cfgFirst);

}

void MainWindow::proc_action_netsearch_custom_action(QAction *pAction)
{
    ////debugApp() << "custom action:" << pAction->text();
    ////debugApp() << "custom data  :" << pAction->data();

    QString searchText = CUIPub::getSelectTextEdit(ui->textEdit);
    QString prefix = pAction->data().toString();
    //    debugApp() << "searchText:" << searchText;
    //    debugApp() << "action name:" << prefix;

    if(0 == CStringPub::strSimLen(searchText))
    {
        show_StatusTimer("请选中查询字段");
        return;
    }

    CUIPub::execCmd(CStringPub::getHttpStr(prefix,searchText));
}

//编辑配置文件
/**
 * @brief MainWindow::proc_action_EditCfgFile
 * @param checked
 * 选中表示编辑
 * 未选中表示退出编辑
 */
void MainWindow::proc_action_EditCfgFile(bool checked)
{
    if(CExpressPub::isFalse(checked))
    {
        if(CExpressPub::isFull(m_EditConfig))
        {
            if(proc_action_edit_convertline_pub(m_EditConfig))
            {
                proc_actionCovertOneLine();
            }
            debugApp() << "save config :" << m_EditConfig;

            CRegExpPub::handlerTipSave(m_EditConfig, 0, CUIPub::getTextEdit(ui->textEdit_cfgTips)   , CRegExpPub::FILE_TIPS  );
            CRegExpPub::handlerTipSave(m_EditConfig, 0, CUIPub::getTextEdit(ui->textEdit_cfgBefore) , CRegExpPub::FILE_BEFORE);
            CRegExpPub::handlerTipSave(m_EditConfig, 0, CUIPub::getTextEdit(ui->textEdit_cfgAfter)  , CRegExpPub::FILE_AFTER );
            show_StatusTimerWindowTitle(QString("保存配置文件成功:%1").arg(m_EditConfig));
        }
        CUIPub::hideTextEdit(ui->textEdit_cfgTips);
        CUIPub::hideTextEdit(ui->textEdit_cfgBefore);
        CUIPub::hideTextEdit(ui->textEdit_cfgAfter);
        procRightSplitter();
    }
    else
    {
        if(CExpressPub::isFull(m_EditConfig))
        {
            proc_action_editinginfo(m_EditConfig, 0);
        }
        else
        {
            show_StatusTimerWindowTitle(QString("进入编辑配置文件模式"));
        }
        procRightSplitter();

        CUIPub::showTextEdit(ui->textEdit_cfgTips);
        CUIPub::showTextEdit(ui->textEdit_cfgBefore);
        CUIPub::showTextEdit(ui->textEdit_cfgAfter);

        CUIPub::setCheckedQAction(ui->action_DeleteCfgFile, false);
    }
}


void MainWindow::proc_action_DeleteCfgFile(bool checked)
{
    if(CExpressPub::isFalse(checked))
    {
        show_StatusTimerWindowTitle(QString("退出删除配置文件模式"));
        return;
    }
    show_StatusTimerWindowTitle(QString("进入删除配置文件模式"));
    proc_action_EditCfgFileMutex();
}

void MainWindow::proc_action_EditCfgFileMutex()
{
    if(CExpressPub::isFalse(CUIPub::getCheckedQAction(ui->action_EditCfgFile)))
    {
        return;
    }
    emit ui->action_EditCfgFile->triggered(false);
    CUIPub::setCheckedQAction(ui->action_EditCfgFile, false);
}


void MainWindow::proc_actionClearLeft()
{
    CUIPub::clearTextEdit(ui->textEdit);
}

void MainWindow::proc_actionPasteLeft()
{
    CUIPub::setPlainTextEdit(ui->textEdit, CUIPub::getClipBoardText());
}

void MainWindow::proc_actionSelectCopy()
{
    CUIPub::setClipBoardText(CUIPub::getSelectTextEdit(ui->textEdit));
}

void MainWindow::proc_actionSelectAllCopyLeft()
{
    CUIPub::setClipBoardText(CUIPub::getTextEdit(ui->textEdit));
}


void MainWindow::proc_actionOpenConfigBaseDir()
{
    CUIPub::explorerPathExt(CRegExpPub::getConfigBase());
}

void MainWindow::proc_actionOpenConfigFile()
{
    CUIPub::explorerPathCurrent(CRegExpPub::getRegExpFileNameTips(m_EditConfig));
}

void MainWindow::proc_actionOpenConfigDir()
{
    QString dirPath = CFilePub::parentDir(CRegExpPub::getRegExpFileNameTips(m_EditConfig));
    CUIPub::explorerPathExt(dirPath);
}

void MainWindow::proc_pActionOpenSelectDir()
{
    QString selectPath = CUIPub::getSelectTextEdit(ui->textEdit);
    if(CFilePub::isFile(selectPath))
    {
         selectPath = CFilePub::parentDir(selectPath);
    }
    CUIPub::explorerPathExt(selectPath);
}



void MainWindow::proc_actionOpenConfigFileR()
{
    CUIPub::explorerPathExt(CRegExpPub::getRegExpFileNameAfter(m_EditConfig));
}

void MainWindow::proc_actionOpenConfigDirR()
{
    QString dirPath = CFilePub::parentDir(CRegExpPub::getRegExpFileNameAfter(m_EditConfig));
    CUIPub::explorerPathExt(dirPath);
}


void MainWindow::proc_actionOpenCfgMenu()
{
    QStringList list  = CStringPub::emptyStringList();
    list.append(m_ListOpenFile);
    list.append(m_FileMode_AllL_ExecMulti);
    list.append(m_FileMode_SingleL_ExecMulti);
    list.append(m_FileMode_SingleL_ExecSingle);
    list.append(m_FileNameMenu);
    int seq = 0;
    foreach (QString item, list) {
        CUIPub::explorerPathCurrent((item));
        if(0 == seq++){
#if defined(Q_OS_WIN32)
            _sleep(1500);
#else
            sleep(2);
#endif
        }
    }
}

void MainWindow::proc_actionReload()
{
    CUIPub::clearTextEdit(ui->textEdit);
    CUIPub::pushButtonEmitClick(ui->pushButton_tryagain);
}

void MainWindow::proc_LinePacket()
{
    //指定处理规则
    QString configfilename = "PACKET Parse/报文处理成一行规则";
    QString lefttext  = CUIPub::getTextEdit(ui->textEdit);
    T_RegExpParas tPara;

    tPara.classconfig = configfilename;
    tPara.dwClasstype = EUM_CLASSTYPE::COMMON_OPERATIONS;
    tPara.text = lefttext;
    proc_mode_AB_multiline_multiproc(tPara);
    set_LeftTextEdit(CRegExpPub::procTextByRegExpList(tPara));
    lefttext  = CStringPub::strSim(CUIPub::getTextEdit(ui->textEdit));
    CUIPub::showStatusBarTimerBoth(ui->statusbar, QString("%1 共%2/2=%3字节").arg(configfilename).arg(lefttext.count()).arg(lefttext.count()/2) );
}

void MainWindow::proc_ActionForward()
{

    QString selectText = CUIPub::getSelectTextEdit(ui->textEdit).simplified();
    if(CStringPub::strSimLen(selectText) == 0 )
    {
        return;
    }
    CUIPub::explorerPathExt(CStringPub::strSim(selectText));
    CUIPub::showStatusBarTimerBoth(ui->statusbar, QString("打开%1").arg(selectText));
}

void MainWindow::proc_ActionForwardRight()
{

    QString selectText = CUIPub::getSelectTextBrowser(ui->textBrowser).simplified();
    if(CStringPub::strSimLen(selectText) == 0 )
    {
        return;
    }
    CUIPub::explorerPathExt(CStringPub::strSim(selectText));
    CUIPub::showStatusBarTimerBoth(ui->statusbar, QString("打开%1").arg(selectText));
}


void MainWindow::proc_actionEditCfgFile()
{
    CUIPub::explorerPathExt(CRegExpPub::getConfigBefore());
}

void MainWindow::proc_actionSaveCfgFile()
{
    CUIPub::explorerPathExt(CRegExpPub::getConfigBefore());
}


void MainWindow::proc_actionClearRight()
{
    CUIPub::clearTextBrowser(ui->textBrowser);
}

void MainWindow::proc_actionPasteRight()
{
    CUIPub::setPlainTextBrowser(ui->textBrowser, CUIPub::getClipBoardText());
}

void MainWindow::proc_actionSelectAllCopyRight()
{
    CUIPub::setClipBoardText(CUIPub::getTextBrowser(ui->textBrowser));
}

void MainWindow::proc_actionClearEmpty()
{
    CUIPub::setPlainTextBrowser(ui->textBrowser, CStringPub::stringFilterEmpty(CUIPub::getTextBrowser(ui->textBrowser)));
}

void MainWindow::proc_actionCovertOneLine()
{
    QString text = CUIPub::getTextEdit(ui->textEdit_cfgAfter);
    CUIPub::setPlainTextEdit(ui->textEdit_cfgAfter,text.replace("\n", SIGN_CUSTOM_NL));
}

void MainWindow::proc_actionCovertMulLine()
{
    QString text = CUIPub::getTextEdit(ui->textEdit_cfgAfter);
    CUIPub::setPlainTextEdit(ui->textEdit_cfgAfter,text.replace(SIGN_CUSTOM_NL, "\n"));
}


void MainWindow::proc_action_TryAgain_Thread()
{
    //编辑配置文件模式
    if(CUIPub::isCheckedQAction(ui->action_EditCfgFile)
            || CExpressPub::isEmpty(m_EditConfig))
    {
        return;
    }

    setWindowTitle(QString("生成代码【%1】").arg(m_EditConfig));
    proc_action_gen_pub(m_EditConfig, EUM_CLASSTYPE::COMMON_OPERATIONS);

    on_ThreadM_Stop();
}

void MainWindow::proc_action_TryAgain()
{
    on_ThreadM_Start();

    //    //编辑配置文件模式
    //    if(CUIPub::isCheckedQAction(ui->action_EditCfgFile)
    //            || CExpressPub::isEmpty(m_EditConfig))
    //    {
    //        return;
    //    }

    //    setWindowTitle(QString("生成代码【%1】").arg(m_EditConfig));
    //    proc_action_gen_pub(m_EditConfig, EUM_CLASSTYPE::COMMON_OPERATIONS);

}

void MainWindow::proc_textEdit_textChanged()
{
    //    if(CUIPub::getCheckedQAction(ui->action_EditCfgFile)
    //            ||CUIPub::getCheckedQAction(ui->action_DeleteCfgFile))
    //    {
    //        return;
    //    }


    //    static QString oldText = CStringPub::emptyString();
    //    static QString curText = CStringPub::emptyString();

    //    curText = CUIPub::getTextEdit(ui->textEdit);
    //    if(CExpressPub::isEmpty(curText))
    //    {
    //        pCheckLeftTimer->stop();
    //        oldText = curText;
    //        return;
    //    }

    //    if(curText != oldText)
    //    {
    //        pCheckLeftTimer->start(iTimeout);
    //        oldText = curText;
    //        return;
    //    }

    //    oldText = curText;
    //    //    proc_action_TryAgain();
    //    pCheckLeftTimer->stop();

}

void MainWindow::proc_clipBoard_textChanged()
{
    if(CExpressPub::isFalse(CUIPub::getCheckedQAction(ui->action_ClipBoarChange)))
    {
        return;
    }

    static QString oldText = CUIPub::getClipBoardText();
    static QString curText = CUIPub::getClipBoardText();

    curText = CUIPub::getClipBoardText();
    if(curText != oldText)
    {
        CUIPub::setPlainTextEdit(ui->textEdit, curText);
        proc_action_TryAgain();
        oldText = curText;
        return;
    }

    oldText = curText;
}

//具体选中的配置信息记录
void MainWindow::proc_frequse_config(QString configfilename)
{
    CLogPub::logDefault("[proc_frequse_config]add config:" + configfilename);
    CStringPub::addStringHeaderUniqueMax(m_ListFreqUse, configfilename, m_ActualFreqUseCnt);
    //    CLogPub::logDefault("[proc_frequse_config]m_FileNameMenuListFreqUse:" + configfilename);
    //    CLogPub::logDefault("[proc_frequse_config]m_ListFreqUse:" + CStringPub::stringList2StringEnter(m_ListFreqUse));
    CFilePub::writeFileWOnly(m_FileNameMenuListFreqUse, m_ListFreqUse);
}

void MainWindow::proc_frequse_findkey(QString findKey)
{
    CStringPub::addStringUniqueSortMax(m_ListRecentOpen, findKey, m_ActualFreqUseCnt);
    CFilePub::writeFileWOnly(m_FileNameRecentOpen, m_ListRecentOpen);
}

void MainWindow::proc_action_openfilelist(QAction *pAction)
{
    if(CExpressPub::isTrue(CUIPub::getCheckedQAction(ui->action_EditCfgFile)))
    {
        show_StatusTimerWindowTitle("编译常用列表模式");
        CUIPub::explorerPathExt(m_ListOpenFile);
        return;
    }
    QString openPathAll = pAction->text();
    QString openPathReal = CStringPub::replaceRegLRKuohao2Empty(openPathAll);

    show_StatusTimerWindowTitle("打开配置文件" + openPathAll);
    CUIPub::explorerPathExt(openPathReal);
}

void MainWindow::proc_action_background_update(bool bFlag)
{
    Q_UNUSED(bFlag);
    ////debugApp() << "bFlag:" << bFlag;
}

void MainWindow::proc_action_update(bool bFlag)
{
    Q_UNUSED(bFlag);
    ////debugApp() << "bFlag:" << bFlag;
    update_generate_menu_left();
}

void MainWindow::proc_action_scan_test_dir(bool bFlag)
{
    Q_UNUSED(bFlag);
    ////debugApp() << "bFlag:" << bFlag;
    //支持创建多个界面
    pMulWinTest = new SuperTest();
    pMulWinTest->setAttribute(Qt::WA_DeleteOnClose, true);
    pMulWinTest->show();
}


void MainWindow::proc_TimerBackgroundUpdate()
{
    update_generate_menu_left();
}


void MainWindow::proc_pushButton_left_clear()
{
    CUIPub::clearTextEdit(ui->textEdit);
}

void MainWindow::proc_pushButton_left_paste()
{
    CUIPub::setTextEdit(ui->textEdit, CUIPub::getClipBoardText());
    //连续处理模式
    proc_action_MulProcMode();
}

void MainWindow::proc_action_MulProcMode()
{
    //连续处理模式
    if(CUIPub::getCheckedQAction(ui->action_MulProcMode))
    {
        emit ui->pushButton_tryagain->clicked();
        emit ui->pushButton_right_copy->click();
    }
}


void MainWindow::proc_pushButton_tryagain()
{
    on_ThreadM_Start();
    //    proc_action_TryAgain();
}

void MainWindow::proc_pushButton_right_clear()
{
    CUIPub::clearTextBrowser(ui->textBrowser);
}

void MainWindow::proc_pushButton_right_copy()
{
    if(CStringPub::strSimLen(CUIPub::getSelectTextEdit(ui->textBrowser)))
    {
        CUIPub::setClipBoardText(CUIPub::getSelectTextEdit(ui->textBrowser));
        return;
    }
    CUIPub::setClipBoardText(CUIPub::getTextBrowser(ui->textBrowser));
}


void MainWindow::on_pushButton_clearTryAgainExt_clicked()
{
    CUIPub::clearTextEdit(ui->textEdit);
    emit ui->pushButton_tryagain->clicked();

}

void MainWindow::proc_search_filecontent(QStringList menuList, Qt::CaseSensitivity cs, QString findKey,QStringList &resultlist)
{
    foreach (QString item, menuList) {
        QString filename = CRegExpPub::getRegExpFileNameTips(item);
        QString filenameAfter = CRegExpPub::getRegExpFileNameAfter(item);
        QString filenameBefore = CRegExpPub::getRegExpFileNameBefore(item);
        if(CStringPub::filterKeySpaceInclude(findKey, item, cs)
                || CStringPub::filterKeySpaceInclude(findKey, CFilePub::readFileAll(filename), cs)
                || CStringPub::filterKeySpaceInclude(findKey, CFilePub::readFileAll(filenameAfter), cs)
                || CStringPub::filterKeySpaceInclude(findKey, CFilePub::readFileAll(filenameBefore), cs)
                )
        {
            resultlist.append(item);
        }
    }
}
//判断查找的key在菜单中是否存在
bool MainWindow::check_findKey_exist(QString findKey)
{
    QStringList menuList = CStringPub::emptyStringList();
    QStringList resultlist = CStringPub::emptyStringList();
    menuList = CFilePub::readFileAllFilterEmptyUniqueMulti(m_FileNameMenu);
    resultlist = CStringPub::SameListInclude(findKey, menuList);

    if(CExpressPub::isZero(resultlist.size()))
    {
        goto ENDLABEL;
    }

    return true;

ENDLABEL:
    return false;
}

//处理查找列表
void MainWindow::on_action_search_triggered_handle_quick(QString findKey)
{
    CDialogSearch *pDiagSearch = new CDialogSearch();
    //文件中的菜单列表
    QStringList menuList = CStringPub::emptyStringList();
    QStringList resultlist = CStringPub::emptyStringList();
    Qt::CaseSensitivity cs = pDiagSearch->getCaseSentived();


    if(CExpressPub::isZero(CStringPub::strSimLen(findKey)))
    {
        findKey = pDiagSearch->getKey();
    }

    menuList = CFilePub::readFileAllFilterEmptyUniqueMulti(m_FileNameMenu);
    //查看文件内容是否查找，文件名和内容都查找
    if(pDiagSearch && pDiagSearch->getFileContented())
    {
        proc_search_filecontent(menuList,cs,findKey,resultlist);
    }
    else
    {
        resultlist = CStringPub::filterFileListInclude(findKey, menuList, cs);
    }
    debugApp() << "resultlist size:" << resultlist.size();

    if(CExpressPub::isZero(resultlist.size()))
    {
        CUIPub::showStatusBarTimerOnly(QString("未找到"));
        //说明关键字已经失效，删除
        CStringPub::deleteListItem(m_ListRecentOpen, findKey);
        updateListWidgetRecentOpen();
        goto ENDLABEL;
    }
    //排序
    resultlist.sort(Qt::CaseSensitive);

    QObject::disconnect(ui->listWidget_searchresult, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(proc_listWidget_searchresult_ItemClicked(QListWidgetItem *)));
    CUIPub::clearAddListWidgetItemsAndShow(ui->listWidget_searchresult, resultlist);
    QObject::connect(ui->listWidget_searchresult, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(proc_listWidget_searchresult_ItemClicked(QListWidgetItem *)));

    delete pDiagSearch;
    return;

ENDLABEL:
    QObject::disconnect(ui->listWidget_searchresult, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(proc_listWidget_searchresult_ItemClicked(QListWidgetItem *)));
    CUIPub::clearHideListWidget(ui->listWidget_searchresult);
    delete pDiagSearch;
}
void MainWindow::on_action_search_triggered_handle(int flag)
{
    SHOWCURFUNC;
    CDialogSearch *pDiaglogKey = new CDialogSearch();
    //文件中的菜单列表
    QStringList menuList = CStringPub::emptyStringList();
    Qt::CaseSensitivity cs;
    QStringList resultlist = CStringPub::emptyStringList();
    QString findKey = CStringPub::emptyString();


    if(flag > 0 && QDialog::Rejected == pDiaglogKey->exec())
    {
        goto ENDLABEL;
    }
    ////debugApp() << pDiaglogKey->getKey();
    findKey = pDiaglogKey->getKey();
    cs = pDiaglogKey->getCaseSentived();
    if(0 == CStringPub::strSimLen(findKey))
    {
        CUIPub::showStatusBarTimerOnly(QString("请输入关键字"));
        goto ENDLABEL;
    }

    menuList = CFilePub::readFileAllFilterEmptyUniqueMulti(m_FileNameMenu);
    //查看文件内容是否查找，文件名和内容都查找
    if(pDiaglogKey->getFileContented())
    {
        proc_search_filecontent(menuList,cs,findKey,resultlist);
    }
    else
    {
        resultlist = CStringPub::filterFileListInclude(findKey, menuList, cs);
    }

    if(CExpressPub::isZero(resultlist.size()))
    {
        CUIPub::showStatusBarTimerOnly(QString("未找到"));
        goto ENDLABEL;
    }
    //排序
    resultlist.sort(Qt::CaseSensitive);
    //显示列表(查找出来的数据）
    QObject::disconnect(ui->listWidget_searchresult, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(proc_listWidget_searchresult_ItemClicked(QListWidgetItem *)));
    CUIPub::clearAddListWidgetItemsAndShow(ui->listWidget_searchresult, resultlist);
    QObject::connect(ui->listWidget_searchresult, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(proc_listWidget_searchresult_ItemClicked(QListWidgetItem *)));

    //更新左侧常用列表（选中的项或查询的关键字列表）
    updateListWidgetFrequse();
    updateListRecentOpenKey(findKey);
    updateListWidgetRecentOpen();

    delete pDiaglogKey;
    return;

ENDLABEL:
    CUIPub::clearHideListWidget(ui->listWidget_searchresult);
    delete pDiaglogKey;
}

void MainWindow::on_action_search_triggered()
{
    on_action_search_triggered_handle(1);
}
void MainWindow::on_action_researchresult_triggered()
{
    on_action_search_triggered_handle_quick(CStringPub::emptyString());
}

void MainWindow::proc_listWidget_searchresult_ItemClicked(QListWidgetItem *item)
{
    QStringList menuList = CStringPub::emptyStringList();
    Qt::CaseSensitivity cs = Qt::CaseInsensitive;
    QStringList resultlist = CStringPub::emptyStringList();
    QString findKey = item->text();

    menuList = CFilePub::readFileAllFilterEmptyUniqueMulti(m_FileNameMenu);
    resultlist = CStringPub::filterFileListInclude(findKey, menuList, cs);

    if(CExpressPub::isZero(resultlist.size()))
    {
        CUIPub::showStatusBarTimerOnly(QString("节点不存在[%1]").arg(findKey));
        CStringPub::removeAll(m_ListFreqUse, findKey);
        CFilePub::writeFileWOnly(m_FileNameMenuListFreqUse, m_ListFreqUse);
        updateListWidgetFrequse();
        return;
    }

    QAction *tempAction = CUIPub::createActionData("tempAction", item->text());
    proc_action_gen_custom_action(tempAction);
    debugApp() << "proc_listWidget_searchresult_ItemClicked";
    delete tempAction;
}

void MainWindow::proc_listWidget_findkey_ItemClicked(QListWidgetItem *item)
{
    debugApp() << "proc_listWidget_findkey_ItemClicked";
    debugApp() << "item text:" << item->text();
    on_action_search_triggered_handle_quick(item->text());
}

void MainWindow::updateListWidgetRecentOpen()
{
    QObject::disconnect(ui->listWidget_frequse, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(proc_listWidget_findkey_ItemClicked(QListWidgetItem *)));
    if(CUIPub::isCheckedQAction(ui->action_recentopen))
    {
        CUIPub::clearAddListWidgetItemsAndShow(ui->listWidget_frequse, m_ListRecentOpen);
        QObject::connect(ui->listWidget_frequse, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(proc_listWidget_findkey_ItemClicked(QListWidgetItem *)));
    }
}

void MainWindow::updateListWidgetFrequse()
{
    QObject::disconnect(ui->listWidget_frequse, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(proc_listWidget_searchresult_ItemClicked(QListWidgetItem *)));
    if(CUIPub::noCheckedQAction(ui->action_recentopen))
    {
        CUIPub::clearAddListWidgetItemsAndShow(ui->listWidget_frequse, m_ListFreqUse);
        QObject::connect(ui->listWidget_frequse, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(proc_listWidget_searchresult_ItemClicked(QListWidgetItem *)));
    }
}



void MainWindow::on_pushButton_left_clear_clicked()
{
    CUIPub::setTextEditFocus(ui->textEdit);
}

void MainWindow::on_actionclearTry_triggered()
{
    on_pushButton_clearTryAgainExt_clicked();
}

void MainWindow::proc_character_trim_pub(const QString &pattern)
{
    QString result = CStringPub::emptyString();
    QStringList lstStr = CStringPub::stringSplitbyNewLine(CUIPub::getTextEdit(ui->textEdit));
    foreach (QString item, lstStr) {
        result.append(item.remove(QRegExp(pattern)));
        result.append(CSignPub::signEnter());
    }
    CUIPub::setTextBrowser(ui->textBrowser, result);
}

void MainWindow::on_action_trim_line_firstspace_triggered()
{
    proc_character_trim_pub("^ +\\s*");
}

void MainWindow::on_action_trim_line_endspace_triggered()
{
    proc_character_trim_pub("\\s* +$");
}

void MainWindow::on_action_trim_line_space_triggered()
{
    QString result = CStringPub::emptyString();
    QStringList lstStr = CStringPub::stringSplitbyNewLine(CUIPub::getTextEdit(ui->textEdit));
    foreach (QString item, lstStr) {
        result.append(item.trimmed());
        result.append(CSignPub::signEnter());
    }
    CUIPub::setTextBrowser(ui->textBrowser, result);
}

void MainWindow::on_action_clear_allspace_triggered()
{
    proc_character_trim_pub("\\s");
}

void MainWindow::procRightSplitter()
{

}

void MainWindow::iniUiOther()
{
    //在状态栏上添加组件
    fLabCurFile = new QLabel;
    fLabCurFile->setMaximumWidth(150);
    fLabCurFile->setText("当前文件:");
    //无法显示是因为状态栏有其它信息显示
    CUIPub::addWidget2StatusBar(ui->statusbar, fLabCurFile);

    progressBar1 = new QProgressBar;
    progressBar1->setMaximumWidth(200);
    progressBar1->setMinimum(5);
    progressBar1->setValue(ui->textEdit->font().pointSize());
    CUIPub::addWidget2StatusBar(ui->statusbar, progressBar1);
    //工具栏上添加组件
    spinFontSize = new QSpinBox;//文字大小SpinBox
    spinFontSize->setValue(ui->textEdit->font().pointSize());
    spinFontSize->setMinimumWidth(30);
    spinFontSize->setMaximumWidth(150);
    CUIPub::addWidget2ToolBar(ui->toolBar, new QLabel("字体大小"));
    CUIPub::addWidget2ToolBar(ui->toolBar, spinFontSize);

    ui->toolBar->addSeparator();
    CUIPub::addWidget2ToolBar(ui->toolBar, new QLabel("字体"));
    comboFont = new QFontComboBox;
    comboFont->setMinimumWidth(100);
    comboFont->setMaximumWidth(150);
    CUIPub::addWidget2ToolBar(ui->toolBar, comboFont);


}


void MainWindow::on_pushButton_mainfind_clicked()
{
    if (CUIPub::isLineEditEmpty(ui->lineEdit_mainsearch))
    {
        ShowTipsInfo(QString::fromLocal8Bit("search text null!"));
        return;
    }

    on_pushButton_mainfind_clicked_pub(0);
}




void MainWindow::on_pushButton_mainfindreverse_clicked()
{
    if (CUIPub::isLineEditEmpty(ui->lineEdit_mainsearch))
    {
        ShowTipsInfo(QString::fromLocal8Bit("search text null!"));
        return;
    }

    on_pushButton_mainfind_clicked_pub(1);
}

void MainWindow::on_pushButton_mainfind_clicked_pub(int reverse)
{
    QString findtext = CUIPub::getLineEdit(ui->lineEdit_mainsearch);
    QString text = CUIPub::getTextEdit(ui->textEdit).trimmed();

    //    ui->textEdit->setFocus();

    QTextDocument::FindFlags options = 0;
    //精确查找
    if (CUIPub::isCheckedQCheckBox(ui->checkBox_preciousfind))
    {
        options |= QTextDocument::FindCaseSensitively;
    }
    //全字匹配
    if (CUIPub::isCheckedQCheckBox(ui->checkBox_wholeword))
    {
        options |= QTextDocument::FindWholeWords;
    }

    //反向查找
    if(reverse > 0)
    {
        options |= QTextDocument::FindBackward;
    }

    if(!CUIPub::findTextEdit(ui->textEdit, findtext,options))
    {
        ShowTipsInfo(QString::fromLocal8Bit("到过界限 \"%1\"").arg(findtext));
    }

}

void MainWindow::on_lineEdit_mainsearch_returnPressed()
{
    ENTERTIPS;
    on_pushButton_mainfind_clicked();
}

//ASCII转字符串
int ascii_to_str(char *dst, int *src, int len)
{
    unsigned int dwLp =  0;
    for(dwLp = 0;dwLp < len;dwLp++)
    {
        dst[dwLp] = src[dwLp];
    }

    return 0;
}

void MainWindow::proc_actionascii_to_string_pub(int hexflag)
{

    QString result("");
    QString input_string = CUIPub::getTextEdit(ui->textEdit);
    debugApp() << "input_string:" << input_string << "input_string lenth:" << input_string.length();

    //字符串为奇数时前面补0
    if(0 != input_string.length() %2)
    {
        input_string = "0" + input_string;
    }

    char buf[3];
    WORD32 dwLp =  0;
    int iStrLen = input_string.length();
    for(dwLp = 0; dwLp < iStrLen; dwLp+=2)
    {
        memset(buf, 0, sizeof(buf));
        buf[dwLp%2] = input_string.at(dwLp).toLatin1();
        buf[(dwLp + 1)%2] = input_string.at(dwLp + 1).toLatin1();
        buf[2] = '\0';
        //        debugApp() << "buf:" << buf ;
        int num = 0;
        if(16 == hexflag)
        {
            num = strtol(buf, NULL, 16);
        }
        else
        {
            num = strtol(buf, NULL, 10);
        }
        memset(buf, 0, sizeof(buf));
        ascii_to_str(buf, &num, 1);
        debugApp() << "num:" << num << ", buf:" << buf ;
        result.append(buf);
    }

    CUIPub::setTextBrowser(ui->textBrowser, result);
}

void MainWindow::proc_actionascii_to_string_10()
{
    proc_actionascii_to_string_pub(10);
}

void MainWindow::proc_actionascii_to_string()
{
    proc_actionascii_to_string_pub(16);
}

void MainWindow::proc_actionstring_to_asciipub(int hexflag)
{
    QString input_string = CUIPub::getTextEdit(ui->textEdit);
    QByteArray byte = input_string.toUtf8();
    unsigned char *pBuffer = (unsigned char *)malloc(input_string.size());
    if(NULL == pBuffer)
    {
        return;
    }
    memset((void *)pBuffer,0,input_string.size());

    for(int i = 0; i < input_string.size(); i++)

    {
        //        qDebug() << int(byte.at(i));
        pBuffer[i] = int(byte.at(i));
    }

    CUIPub::setTextBrowser(ui->textBrowser, CStringPub::getStringOfData(pBuffer, input_string.size(), hexflag));

    if(NULL != pBuffer)
    {
        free(pBuffer);
        pBuffer = NULL;
    }

}

void MainWindow::proc_actionstring_to_ascii()
{
    proc_actionstring_to_asciipub(16);
}

void MainWindow::proc_actionstring_to_ascii_10()
{
    proc_actionstring_to_asciipub(10);
}


void MainWindow::proc_action_newstandnode()
{
    CDialogNewNode *pDiaglog = new CDialogNewNode();
    pDiaglog->setType(CDialogNewNode::NEWSTANDMODE);

    if(QDialog::Rejected == pDiaglog->exec())
    {
        return;
    }
    proc_newnode_more(pDiaglog);
    delete pDiaglog;
}

void MainWindow::proc_action_newusernode()
{

    CDialogNewNode *pDiaglog = new CDialogNewNode();
    pDiaglog->setType(CDialogNewNode::NEWUSERMODE);

    if(QDialog::Rejected == pDiaglog->exec())
    {
        return;
    }
    proc_newnode_more(pDiaglog);

    delete pDiaglog;
}

void MainWindow::proc_newnode_more(CDialogNewNode *pDiaglog)
{
    QString newNodeName = pDiaglog->getName();
    debugApp() << newNodeName;
    QString newNodeNameFromCopy = pDiaglog->getNameFromCopy();
    debugApp() << newNodeNameFromCopy;
    if(CStringPub::strSimLenZero(newNodeName))
    {
        CUIPub::showStatusBarTimerOnly("请输入内容");
        return;
    }

    //检测节点是否存在
    switch (pDiaglog->getType()) {
    case CDialogNewNode::NEWSTANDMODE:
    {
        if(proc_newnode_check(pDiaglog))
        {
            return;
        }
        QStringList filelines = CFilePub::readFileAllFilterEmptyUniqueSort(m_FileNameMenu_stand);
        filelines.append(newNodeName);
        filelines.sort();
        if(CStringPub::strSimLen(CFilePub::writeFileWOnly(m_FileNameMenu_stand,filelines)))
        {
            CUIPub::showStatusBarTimerOnly(QString("成功[标准] %1").arg(newNodeName));
        }
        else
        {
            CUIPub::showStatusBarTimerOnly(QString("失败[标准] %1").arg(newNodeName));
            return;
        }
    }
        break;
    case CDialogNewNode::NEWUSERMODE:
    {
        if(proc_newnode_check(pDiaglog))
        {
            return;
        }
        QStringList filelines = CFilePub::readFileAllFilterEmptyUniqueSort(m_FileNameMenu_user);
        filelines.append(newNodeName);
        filelines.sort();
        if(CStringPub::strSimLen(CFilePub::writeFileWOnly(m_FileNameMenu_user,filelines)))
        {
            CUIPub::showStatusBarTimerOnly(QString("成功[用户] %1").arg(newNodeName));
        }
        else
        {
            CUIPub::showStatusBarTimerOnly(QString("失败[用户] %1").arg(newNodeName));
            return;
        }
    }
        break;
    default:
        CUIPub::showStatusBarTimerOnly("非法模式，请确认");
        return;
        break;
    }

    //从已经存在的配置拷贝数据
    proc_newnode_copy(pDiaglog);

    pDiaglog->write_HistorySetting();
    //重新执行查找过程
    on_action_search_triggered_handle(0);

}

//拷贝节点
void MainWindow::proc_newnode_copy(CDialogNewNode *pDiaglog)
{
    QString newNodeName = pDiaglog->getName();
    debugApp() << newNodeName;
    QString newNodeNameFromCopy = pDiaglog->getNameFromCopy();
    debugApp() << newNodeNameFromCopy;

    if(false == pDiaglog->isChkedBoxfromCopy())
    {
        return;
    }

    if(CExpressPub::isZero(CStringPub::strSimLen(newNodeNameFromCopy)))
    {
        CUIPub::showStatusBarTimerOnly(QString("源节点名称为空"));
        return;
    }

    if(CExpressPub::isFalse(proc_configexist_check(newNodeNameFromCopy)))
    {
        CUIPub::showStatusBarTimerOnly(QString("源节点配置不存在"));
        return;
    }

    //源节点
    QString filenameSrc = CRegExpPub::getRegExpFileNameTips(newNodeNameFromCopy);
    QString filenameAfterSrc = CRegExpPub::getRegExpFileNameAfter(newNodeNameFromCopy);
    QString filenameBeforeSrc = CRegExpPub::getRegExpFileNameBefore(newNodeNameFromCopy);

    //目的节点
    QString filename = CRegExpPub::getRegExpFileNameTips(newNodeName);
    QString filenameAfter = CRegExpPub::getRegExpFileNameAfter(newNodeName);
    QString filenameBefore = CRegExpPub::getRegExpFileNameBefore(newNodeName);

    CFilePub::copyFile(filenameSrc,filename);
    CFilePub::copyFile(filenameAfterSrc, filenameAfter);
    CFilePub::copyFile(filenameBeforeSrc, filenameBefore);
    CUIPub::showStatusBarTimerOnly(QString("模板创建文件%1成功,模板%2").arg(newNodeName).arg(newNodeNameFromCopy));

}

//重命名节点
void MainWindow::proc_newnode_rename(QString preNodeName, QString toNamedNodeName)
{
    debugApp() << toNamedNodeName;
    debugApp() << preNodeName;

    if(CExpressPub::isZero(CStringPub::strSimLen(preNodeName)))
    {
        CUIPub::showStatusBarTimerOnly(QString("源节点名称为空"));
        return;
    }

    if(CExpressPub::isFalse(proc_configexist_check(preNodeName)))
    {
        CUIPub::showStatusBarTimerOnly(QString("源节点配置不存在"));
        return;
    }

    //源节点
    QString filenameSrc = CRegExpPub::getRegExpFileNameTips(preNodeName);
    QString filenameAfterSrc = CRegExpPub::getRegExpFileNameAfter(preNodeName);
    QString filenameBeforeSrc = CRegExpPub::getRegExpFileNameBefore(preNodeName);

    //目的节点
    QString filename = CRegExpPub::getRegExpFileNameTips(toNamedNodeName);
    QString filenameAfter = CRegExpPub::getRegExpFileNameAfter(toNamedNodeName);
    QString filenameBefore = CRegExpPub::getRegExpFileNameBefore(toNamedNodeName);

    CFilePub::renameFile(filenameSrc,filename);
    CFilePub::renameFile(filenameAfterSrc, filenameAfter);
    CFilePub::renameFile(filenameBeforeSrc, filenameBefore);
    //如果源文件夹没有内容则删除
    CFilePub::deleteDirIfNoFiles(CFilePub::dirName(filenameSrc));
    CFilePub::deleteDirIfNoFiles(CFilePub::dirName(filenameAfterSrc));
    CFilePub::deleteDirIfNoFiles(CFilePub::dirName(filenameBeforeSrc));

    CUIPub::showStatusBarTimerOnly(QString("模板重命名文件%1-->%2成功").arg(preNodeName).arg(toNamedNodeName));

}

void MainWindow::update_menulist_byitem(QString m_FileName, QString preNodeName, QString newNodeName)
{
    CFilePub::deleteFileSameLine(m_FileName, preNodeName);
    QStringList filelines = CFilePub::readFileAllFilterEmptyUniqueSort(m_FileName);
    filelines.append(newNodeName);
    filelines.sort();
    if(CStringPub::strSimLen(CFilePub::writeFileWOnly(m_FileName,filelines)))
    {
        CUIPub::showStatusBarTimerOnly(QString("成功[标准] %1").arg(newNodeName));
    }
    else
    {
        CUIPub::showStatusBarTimerOnly(QString("失败[标准] %1").arg(newNodeName));
    }

}

//重命名节点更新配置文件
void MainWindow::proc_newnode_rename_update_menulist(QString preNodeName, QString toNamedNodeName)
{
    debugApp() << toNamedNodeName;
    debugApp() << preNodeName;

    if(CFilePub::checkFileExistLine(m_FileNameMenu_stand, preNodeName))
    {
        update_menulist_byitem(m_FileNameMenu_stand, preNodeName, toNamedNodeName);
    }

    if(CFilePub::checkFileExistLine(m_FileNameMenu_user, preNodeName))
    {
        update_menulist_byitem(m_FileNameMenu_user, preNodeName, toNamedNodeName);
    }

    CUIPub::showStatusBarTimerOnly(QString("模板重命名文件%1-->%2成功").arg(preNodeName).arg(toNamedNodeName));

}

bool MainWindow::proc_newnode_check(CDialogNewNode *pDiaglog)
{
    QString newNodeName = pDiaglog->getName();
    if(CFilePub::checkFileExistLine(m_FileNameMenu_stand, newNodeName))
    {
        CUIPub::showStatusBarTimerOnly(QString("节点已存在 %1 [标准]").arg(newNodeName));
        return true;
    }

    if(CFilePub::checkFileExistLine(m_FileNameMenu_user, newNodeName))
    {
        CUIPub::showStatusBarTimerOnly(QString("节点已存在 %1 [用户]").arg(newNodeName));
        return true;
    }

    return false;
}
//检测配置是否存在
bool MainWindow::proc_configexist_check(QString newNodeName)
{
    if(CFilePub::checkFileExistLine(m_FileNameMenu_stand, newNodeName))
    {
        return true;
    }

    if(CFilePub::checkFileExistLine(m_FileNameMenu_user, newNodeName))
    {
        return true;
    }

    return false;
}


void MainWindow::proc_action_delspace()
{
    QString result("");

    QString input_string = CUIPub::getTextEdit(ui->textEdit);
    QStringList list = CStringPub::stringSplitbyNewLineTrimAll(input_string);

    result = CStringPub::stringList2StringEnter(list);
    CUIPub::setTextBrowser(ui->textBrowser, result);
}

void MainWindow::proc_action_dellastspacesort()
{
    QString result("");

    QString input_string = CUIPub::getTextEdit(ui->textEdit);
    QStringList list = CStringPub::stringSplitbyNewLineFilterEmptyUniqueSort(input_string);
    list = CStringPub::stringSplitbyNewLineTrimEnd(list);
    //定义排序算法，按长度大小 +字符大小
    qSort(list.begin(), list.end(), [](const QString& s1, const QString& s2)
    {
        if(s1.length() < s2.length())
        {
            return true;
        }
        return s1.toInt() < s2.toInt();
    });
    result = CStringPub::stringList2StringEnter(list);
    CUIPub::setTextBrowser(ui->textBrowser, result);
}


void MainWindow::proc_action_del_BCompare_xml()
{
    //删除BCompare生成的文件
    CFilePub::deleteDirFiles(CFilePub::getBComparePath());
}



void MainWindow::on_action_autoconvertaf_triggered()
{
    CUIPub::showStatusBarTimerOnly(QString("自动转变更:%1").arg(ui->action_autoconvertaf->isChecked()));
}

void MainWindow::proc_action_recentopen(bool bFlag)
{
    debugApp() << "bFlag:" << bFlag;
    if(true == bFlag)
    {
        CUIPub::showStatusBarTimerOnly(QString("关键字列表"));
        goto EXIT_LABEL;
    }
    CUIPub::showStatusBarTimerOnly(QString("具体项列表"));

EXIT_LABEL:
    updateListWidgetFrequse();
    updateListWidgetRecentOpen();

}

void MainWindow::updateListRecentOpenKey(QString findKey)
{
    uint8_t bFindFlag = false;

    if(CExpressPub::isZero(CStringPub::strSimLen(findKey)))
    {
        return;
    }

    foreach (QString item, m_ListRecentOpen) {
        if(CStringPub::strSim(item) == CStringPub::strSim(findKey))
        {
            bFindFlag = true;
            break;
        }
    }

    if((0 == m_ListRecentOpen.size()) || (false == bFindFlag))
    {
        m_ListRecentOpen.append(findKey);
    }

    m_ListRecentOpen.sort();

    debugApp() <<"size recent open:" << m_ListRecentOpen.size();
    proc_frequse_findkey(findKey);
    //    CFilePub::writeFileWR(m_FileNameRecentOpen, CStringPub::stringList2StringEnter(m_ListRecentOpen));
}

void MainWindow::proc_action_procreboot(bool bFlag)
{
    debugApp() << "bFlag:" << bFlag;
    qApp->closeAllWindows();
    //qApp->quit();

    //  如果是在嵌入式arm板子上，需要加入 -qws 的参数
    //QStringList args;
    //args.append("-qws");        //  参数信息
    //args.append("&");           //  后台运行
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());
}

void MainWindow::proc_action_GenRegExpTextSeq()
{
    quint8 ucFlag = 0;
    qulonglong dwStartNum = 0 ;
    qulonglong dwTotal = 0 ;
    QString tempText = "";
    QString result = "";
    QString leftText = CUIPub::getTextEdit(ui->textEdit);
    QStringList leftList = CStringPub::stringSplitbyNewLineFilterEmpty(leftText);
    if(0 == CStringPub::stringListCount(leftList))
    {
        CUIPub::showStatusBarTimerOnly("please input data in left textedit!!");
        return;
    }

    tempText = leftList.at(0);
    if(CExpressPub::isFalse(CStringPub::regExpIsDigtals(tempText)))
    {
        CUIPub::showStatusBarTimerOnly("the first line must be start num!!");
        QString eg = "12\n"
                     "aL:12\n"
                     "aL::12 \n\n";
        CUIPub::setTextEdit(ui->textEdit, eg + CUIPub::getTextEdit(ui->textEdit));
        return;
    }

    dwStartNum = CStringPub::strToDec(tempText);
    dwTotal += dwStartNum;
    debugApp() << "start num:" << dwStartNum;
    debugApp() << "dwTotal num:" << dwTotal;
    if(CStringPub::strSimLenBiggerThan(tempText, 1) && CNumPub::isNumZero(dwStartNum))
    {
        CUIPub::showStatusBarTimerOnly(QString("out of range:%1").arg(tempText));
        return;
    }


    leftList = CStringPub::stringSplitbyNewLine(leftText);
    CStringPub::appendStringEnter(result, "==========生成结果==================");


    foreach (QString item, leftList) {
        WORD32 dwLp =  0;
        QString tempBuffer = "";

        if(0 == ucFlag && CStringPub::strSimLen(item) > 0)
        {
            ucFlag++;
            continue;
        }

        if(CExpressPub::isFalse(CStringPub::regExpMaoHaoAfterDigtals(item)))
        {
            CStringPub::appendStringEnter(result, item);
            continue;
        }

        QStringList numList = item.split(QRegExp(":\\d+"));
        QStringList splitList = item.split(QRegExp(".*:"));
        qulonglong tempNum = CStringPub::strToDec(splitList.at(1));
        CStringPub::appendString(tempBuffer, numList.at(0) + ":");
        for(dwLp = 0;dwLp < tempNum;dwLp++)
        {
            CStringPub::appendString(tempBuffer, QString("\\%1").arg(dwTotal + dwLp));
        }

        CStringPub::appendStringEnter(result, tempBuffer);
        dwTotal += tempNum;
    }


    CStringPub::appendStringEnter(result, "\n\n\n");
    CStringPub::appendStringEnter(result, "=====org text:=======");
    CStringPub::appendStringEnter(result, leftText);


    CUIPub::setTextBrowser(ui->textBrowser, result);
}


void MainWindow::on_listWidget_searchresult_customContextMenuRequested(const QPoint &pos)
{
    QListWidgetItem* _curItem = ui->listWidget_searchresult->itemAt(pos);
    if (_curItem == nullptr)
        return;

    QAction* action_rename = new QAction("重命名", this);
    QObject::connect(action_rename, SIGNAL(triggered()), this, SLOT(proc_action_rename()));
    QMenu* popMenuResult = new QMenu(this);
    popMenuResult->addAction(action_rename);
    popMenuResult->exec(QCursor::pos());
    delete popMenuResult;
    popMenuResult = nullptr;
    delete action_rename;
    action_rename = nullptr;

}

void MainWindow::proc_action_rename()
{
    debugApp() << "rename ";

    m_rename = true;
    m_preName = ui->listWidget_searchresult->currentItem()->text();
    ui->listWidget_searchresult->currentItem()->setFlags(ui->listWidget_searchresult->currentItem()->flags() | Qt::ItemIsEditable);
    ui->listWidget_searchresult->editItem(ui->listWidget_searchresult->currentItem());
    connect(ui->listWidget_searchresult, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(proc_onNameChanged(QListWidgetItem*)));

}

void MainWindow::proc_onNameChanged(QListWidgetItem* item)
{
    Q_UNUSED(item)

    if (m_rename)
    {
        m_curName = ui->listWidget_searchresult->currentItem()->text();
        debugApp() << "prename:" << m_preName << ",newname:" << m_curName;
        if (m_preName != m_curName)
        {
            if(check_findKey_exist(m_curName))
            {
                CUIPub::showStatusBarTimerOnly(QString("节点已存在:%1").arg(m_curName));
                ui->listWidget_searchresult->currentItem()->setText(m_preName);
                m_rename = false;
            }
            else
            {
                disconnect(ui->listWidget_searchresult, &QListWidget::itemChanged, this, &MainWindow::proc_onNameChanged);
                ui->listWidget_searchresult->currentItem()->setText(m_curName);
                proc_newnode_rename(m_preName,m_curName);
                proc_newnode_rename_update_menulist(m_preName,m_curName);
                CUIPub::showStatusBarTimerOnly(QString("重命名成功 %1-->%2").arg(m_preName).arg(m_curName));
                m_rename = false;
            }

            //            QMessageBox _warninigDia(QMessageBox::Warning, "警告", "名称已存在，请重新编辑！", QMessageBox::Apply);
            //            _warninigDia.setButtonText(QMessageBox::Apply, "确定");
            //            int _retDel = _warninigDia.exec();
            //            if (_retDel == QMessageBox::Apply)
            //            {
            //                m_rename = false;
            //            }

            return;
        }
    }
}

void MainWindow::on_textEdit_copyAvailable(bool b)
{
    ui->action_Cut->setEnabled(b);
    ui->action_Copy->setEnabled(b);
    ui->action_Paste->setEnabled(ui->textEdit->canPaste());
}

void MainWindow::on_spinBoxFontSize_valueChanged(int aFontSize)
{

    //改变字体大小的spinBox
    QTextCharFormat fmt;
    fmt.setFontPointSize(aFontSize);
    ui->textEdit->mergeCurrentCharFormat(fmt);
    progressBar1->setValue(aFontSize);
}

void MainWindow::on_combFont_currentIndexChanged(const QString &arg1)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(arg1);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_action_FontBold_triggered(bool checked)
{
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();
    if(checked)
    {
        fmt.setFontWeight(QFont::Bold);
    }
    else
    {
        fmt.setFontWeight(QFont::Normal);
    }

    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_textEdit_textChanged()
{
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();

    ui->action_FontBold->setChecked(fmt.font().bold());
    ui->action_FontItalic->setChecked(fmt.fontItalic());
    ui->action_FontUnder->setChecked(fmt.fontUnderline());

}

void MainWindow::on_action_FontItalic_triggered(bool checked)
{
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();
    fmt.setFontItalic(checked);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_action_FontUnder_triggered(bool checked)
{
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();
    fmt.setFontUnderline(checked);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_action_clear_triggered()
{
    CUIPub::clearTextEdit(ui->textEdit);
}

void MainWindow::on_action_CurOpen_triggered()
{
    proc_actionOpenConfigFile();
}

void MainWindow::onthreadM_started()
{
    //线程的started()信号的响应槽函数
    //    CUIPub::showStatusBar(ui->statusbar, "线程开始");
}

void MainWindow::onthreadM_finished()
{
    //线程的 finished()信号的响应槽函数
    //    CUIPub::showStatusBar(ui->statusbar, "线程结束");
}

void MainWindow::onthreadM_newValue(int seq, int diceValue)
{
    //的newValue()信号的响应槽函数，显示内容
    //    CUIPub::showStatusBar(ui->statusbar, QString("seq:%1").arg(seq));
    qDebug() << QString("seq:%1").arg(seq);

    if(1 == seq)
    {
#if 0
        //dead loop test
        while(1)
        {
            Sleep(1000);
            qDebug() << "dead loop here";
        }
#endif
        proc_action_TryAgain_Thread();

    }
    else if(10 == seq)
    {
        on_ThreadM_Stop();
    }
    else
    {

    }

}

void MainWindow::on_ThreadM_Start()
{
    //启动线程 按钮
    threadMonitor.start();
    threadMonitor.diceBegin();
}

void MainWindow::on_ThreadM_Stop()
{
    //结束线程 按钮
    threadMonitor.stopThread();//结束线程的run()函数执行
    threadMonitor.wait();//
}

void MainWindow::on_action_CurRightOpen_triggered()
{
    proc_actionOpenConfigFileR();
}

void MainWindow::on_action_interfaces_triggered()
{
    CNetDiaglog tDiag(this);
    tDiag.exec();
}

void MainWindow::on_actionTcp_Server_triggered()
{
    CTcpServerWindow *pTcpServerWindow = NULL;

    pTcpServerWindow = new CTcpServerWindow();

    pTcpServerWindow->show();

}

void MainWindow::on_actionTcp_Client_triggered()
{
    CTcpClientWindow *pTcpClientWindow = NULL;

    pTcpClientWindow = new CTcpClientWindow();

    pTcpClientWindow->show();

}

void MainWindow::on_actionUDP_triggered()
{
    CUdpWindow *pUdpWindow = NULL;

    pUdpWindow = new CUdpWindow();

    pUdpWindow->show();
}

void MainWindow::on_actionUDP_Mcast_triggered()
{
    CUdpMcastWindow *pUdpMcastWindow = NULL;

    pUdpMcastWindow = new CUdpMcastWindow();

    pUdpMcastWindow->show();
}


void MainWindow::on_actionHTTP_triggered()
{
    CHttpWindow *pHttpWindow = NULL;

    pHttpWindow = new CHttpWindow();

    pHttpWindow->show();
}

void MainWindow::on_actionCalc_triggered()
{
    CSystemPub::execCmd("calc.exe");

}

void MainWindow::on_actionCmd_triggered()
{
    CSystemPub::execCmd("cmd.exe");
}

void MainWindow::on_action_AudioPlayer_triggered()
{
    CAudioPlayer *pAudioPlayerWindow = NULL;

    pAudioPlayerWindow = new CAudioPlayer();

    pAudioPlayerWindow->show();
}

void MainWindow::on_actionCmd_Window_triggered()
{
    CCmdWindow *pCmdWindow = NULL;

    pCmdWindow = new CCmdWindow();

    pCmdWindow->show();

}

void MainWindow::on_actionenvironment_triggered()
{
    CUIPub::setTextEdit(ui->textEdit, CSystemPub::getSystemEnvironment());
}

//生成Excel并打开
void MainWindow::on_action_TestCaseCreateWithTime_triggered()
{
    QString filename = CStringPub::getCurrentExePath() + CStringPub::constStringLeftXieHao()
            + CStringPub::constStringDoc() + CStringPub::constStringLeftXieHao()
            + CStringPub::constStringTestCase()
            + CStringPub::getSystemDate2() + ".csv";
    //    CExcelPub *pExcel = new CExcelPub;
    //    pExcel->open(filename);
    //    delete pExcel;

    CFilePub::createFileEmptyNoExist(filename);

    CSystemPub::explorer(filename);

}

void MainWindow::on_action_OpenCurExcel_triggered()
{
    QString filename = CStringPub::getCurrentExePath() + CStringPub::constStringLeftXieHao()
            +CStringPub::constStringDoc() + CStringPub::constStringLeftXieHao()
            + CUIPub::getTextEdit(ui->textEdit);

    if(CFilePub::pathNoExist(filename))
    {
        if(CStringPub::endWithExcel(filename))
        {
            CExcelPub *pExcel = new CExcelPub;
            pExcel->open(filename);
            delete pExcel;
        }
        else
        {
            CFilePub::createFileEmptyNoExist(filename);
        }
    }

    CSystemPub::explorer(filename);
}

void MainWindow::on_pushButton_saveas_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("保存文件"),
                                                    "",
                                                    tr("Txt Files (*.txt);;All Files (*.*)"));

    if (!fileName.isNull())
    {
        //fileName是文件名
        qDebug() << "fileName:" << fileName;
        CFilePub::writeFileWR(fileName, CUIPub::getTextBrowser(ui->textBrowser));

    }
    else
    {
        //点的是取消
    }

}

void MainWindow::on_pushButton_clicked()
{
    QString fileName =  CFilePub::toNativeSeparators(CUIPub::desktopPath() + CDateTime::format1().append(".txt"));
    qDebug() << "fileName:" << fileName;
    CFilePub::writeFileWR(fileName, CUIPub::getTextBrowser(ui->textBrowser));
}






