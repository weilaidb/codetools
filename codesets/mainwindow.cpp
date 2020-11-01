#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_cdialogasktext.h"
#include "ui_supertest.h"
#include "supertest.h"
#include "cdialogsearch.h"
#include "astyle_main.h"
#include "debugApp.h"
#include "basetypepub.h"
#include "basedefinepub.h"
#include "csignpub.h"
#include "cprintpub.h"
#include "cstringpub.h"
#include "cfilepub.h"
#include "cmsgtips.h"
#include "looppub.h"
#include "cuipub.h"
#include "csqlpub.h"
#ifdef WIN32
#include "cofficepub.h"
#endif
#include "cdialogpub.h"
#include "cnetpub.h"
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

/**
  **处理内容最大值
  **/
#define MANYCONTENTMAX    500


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
    init_ActionSets();
    init_CheckBoxSets();
    init_PushButtonSets();
    init_Vars();
    init_UiSets();

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

void MainWindow::init_SuperTest()
{
    //test
    if(nullptr == pMulWinTest)
    {
        pMulWinTest = new SuperTest();
    }
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
    QObject::connect(ui->action_attention, SIGNAL(triggered()), this, SLOT(proc_action_attention()));

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
    CFilePub::createFileEmptyNoExistAndVar(m_FileNameMenu, "reg/selfmenu.txt;reg/selfmenu_user.txt");
    /**
      ** 模式：
      ** 单行 多处理
      ** 单行 单处理
      ** 多行 单处理
      ** 多行 多处理
      **/
    CFilePub::createFileEmptyNoExistAndVar(m_FileMode_SingleL_ExecMulti, "reg/selfmode_singleline_execmulti.txt");
    CFilePub::createFileEmptyNoExistAndVar(m_FileMode_AllL_ExecMulti, "reg/selfmode_allline_execmulti.txt");

    //配置默认关闭
    emit ui->action_EditCfgFile->triggered(false);

    pCheckLeftTimer = CUIPub::createTimer(iTimeout, 600);
    connect(pCheckLeftTimer, SIGNAL(timeout()), this, SLOT(proc_textEdit_textChanged()));

    pClipBoardTimer = CUIPub::createTimer(iClipBoardTimeout, 600);
    connect(pClipBoardTimer, SIGNAL(timeout()), this, SLOT(proc_clipBoard_textChanged()));

    //后台数据更新频率，暂定为1分钟
    pTimerBackgroundUpdate = CUIPub::createTimer(iTimeoutBackgroundUpdate, 1000 * 60 * 1);
    connect(pTimerBackgroundUpdate, SIGNAL(timeout()), this, SLOT(proc_TimerBackgroundUpdate()));

    m_dwLstFreqUseCnt = 15;
    read_FreqUseFile();
    CFilePub::createFileEmptyNoExistAndVar(m_AttentionFile, "reg/attention.txt");

    //打开常用文件列表
    m_dwLstNormalUseCnt = 30;
    CFilePub::createFileEmptyNoExistAndVar(m_ListOpenFile, "reg/normalfiles.txt");

    //search result list widget, default hide
    CUIPub::hideListWidget(ui->listWidget_searchresult);

    //ui spliter 分割比例
    CUIPub::setSpliterFactor(ui->splitter_10, 0, 3);
    CUIPub::setSpliterFactor(ui->splitter_10, 1, 7);
    //中间三栏 分割比例
    CUIPub::setSpliterFactor(ui->splitter_2, 0, 4);
    CUIPub::setSpliterFactor(ui->splitter_2, 1, 2);
    CUIPub::setSpliterFactor(ui->splitter_2, 2, 4);
}

void MainWindow::read_CfgFile2List(QStringList &list, QString &filenamevar, QString filename)
{
    list = CFilePub::readFileAllFilterEmptyUniqueNoExistAndVar(filenamevar, filename);
}

void MainWindow::read_FreqUseFile()
{
    read_CfgFile2List(m_listfrequse, m_ListFreqUseFile, "reg/frequse.txt");
}

void MainWindow::update_generate_menu_left()
{
    QMutexLocker update_locker(&m_lock);
    debugApp() << "update_generate_menu_left!!";
    //此处删除会异常，正在显示的内容突然被删除
    CUIPub::clearMenuAll(&pRightMouse_L);
    free_RightMouseList();

    pRightMouse_L = new QMenu(this);
    //可能与此处有关，因为ui->menuGenerate不能释放掉，一直在用，所以此处应该用拷贝
    //    pRightMouse_L->addMenu(CUIPub::copyMenu(ui->menuGenerate));

    pMenuCustom = proc_fromfile_menu(m_FileNameMenu);
    if(pMenuCustom)
    {
        pRightMouse_L->addMenu((pMenuCustom));
    }
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
    debugApp() << "right mouse clicked!!";
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
    QStringList modelist_singl_execmulti = CFilePub::readFileAllFilterEmptyUniqueMulti(m_FileMode_SingleL_ExecMulti);
    QStringList modelist_alll_execmulti = CFilePub::readFileAllFilterEmptyUniqueMulti(m_FileMode_AllL_ExecMulti);

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
    //-------Mode Data end  --------

    QMenu *pMenu = nullptr;
    CTreePub::freeTreeMenu();
    foreach (QString item, list) {
        CTreePub::procSubNode(item);
    }
    pMenu = CTreePub::getTreeMenu(CStringPub::stringSelfMenu());
    if(pMenu)
    {
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
    append_RightMouseList(pActionClearLeft);
    //    append_RightMouseList(pActionPaste);
    //    append_RightMouseList(pActionSelectCopy);
    //    append_RightMouseList(pActionSelectAllCopy);
    //    append_RightMouseList(pActionOpenCfgDir);
    //    append_RightMouseList(pActionOpenCfgMenu);

    QObject::connect(pActionClearLeft, SIGNAL(triggered()), this, SLOT(proc_actionClearLeft()));
    QObject::connect(pActionPaste, SIGNAL(triggered()), this, SLOT(proc_actionPasteLeft()));
    QObject::connect(pActionSelectCopy, SIGNAL(triggered()), this, SLOT(proc_actionSelectCopy()));
    QObject::connect(pActionSelectAllCopy, SIGNAL(triggered()), this, SLOT(proc_actionSelectAllCopyLeft()));
    QObject::connect(pActionOpenCfgDir, SIGNAL(triggered()), this, SLOT(proc_actionOpenConfigBaseDir()));
    QObject::connect(pActionOpenCfgMenu, SIGNAL(triggered()), this, SLOT(proc_actionOpenCfgMenu()));
    QObject::connect(pActionReload, SIGNAL(triggered()), this, SLOT(proc_actionReload()));

    pMenu->addMenu(proc_frequse_menu());
    pMenu->addAction(pActionOpenCfgDir);
    pMenu->addAction(pActionOpenCfgMenu);
    pMenu->addMenu(proc_openfilelist_menu());
    pMenu->addAction(pActionClearLeft);
    pMenu->addAction(pActionSelectCopy);
    pMenu->addAction(pActionPaste);
    pMenu->addAction(pActionSelectAllCopy);
    pMenu->addAction(pActionReload);

}

QMenu *MainWindow::proc_frequse_menu()
{
    QMenu *pFreqUse = new QMenu("常用配置列表");
    read_FreqUseFile();
    //更新频繁使用列表
    updateListWidgetFrequse();
    debugApp() << m_listfrequse.count();
    foreach (QString item, m_listfrequse) {
        QAction *pTmpAction = CUIPub::createActionFull(item);
        pFreqUse->addAction(pTmpAction);
        //        append_RightMouseList(pTmpAction);
    }

    if(pFreqUse)
    {
        QObject::connect(pFreqUse, SIGNAL(triggered(QAction *)), this, SLOT(proc_action_gen_custom_action(QAction *)));
    }

    return pFreqUse;
}

QMenu *MainWindow::proc_openfilelist_menu()
{
    QMenu *pOpenFile = new QMenu("文件列表");
    m_listNormalUse = CFilePub::readFileAllFilterEmptyUniqueSort(m_ListOpenFile);
    foreach (QString item, m_listNormalUse) {
        if(CUIPub::getCheckedQAction(ui->action_checknoexistpath)
                &&CStringPub::contain(item, "^\\w:"))
        {
            if(CFilePub::pathNoExist(item))
            {
                continue;
            }
        }
        QAction *pTmpAction = CUIPub::createActionFull(item);
        pOpenFile->addAction(pTmpAction);
        append_RightMouseList(pTmpAction);
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
    //    append_RightMouseList(pActionClearRight);
    //    append_RightMouseList(pActionPaste);
    //    append_RightMouseList(pActionSelectCopy);
    //    append_RightMouseList(pActionSelectAllCopy);
    //    append_RightMouseList(pActionClearEmpty);

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
    //    append_RightMouseList(pActionOpenCfgFile);
    //    append_RightMouseList(pActionOpenCfgDir);
    QObject::connect(pActionOpenCfgFile, SIGNAL(triggered()), this, SLOT(proc_actionOpenConfigFile()));
    QObject::connect(pActionOpenCfgDir, SIGNAL(triggered()), this, SLOT(proc_actionOpenConfigDir()));

    pMenu->addAction(pActionOpenCfgFile);
    pMenu->addAction(pActionOpenCfgDir);
}

void MainWindow::nodes_menu_rightbottom(QMenu *pMenu)
{
    if(CExpressPub::isNullPtr(pMenu))
    {
        return;
    }
    QAction *pActionOpenCfgFile    = CUIPub::createAction("打开当前配置文件");
    QAction *pActionOpenCfgDir    = CUIPub::createAction("打开当前配置文件夹");
    //    append_RightMouseList(pActionOpenCfgFile);
    //    append_RightMouseList(pActionOpenCfgDir);
    QObject::connect(pActionOpenCfgFile, SIGNAL(triggered()), this, SLOT(proc_actionOpenConfigFileR()));
    QObject::connect(pActionOpenCfgDir, SIGNAL(triggered()), this, SLOT(proc_actionOpenConfigDirR()));

    pMenu->addAction(pActionOpenCfgFile);
    pMenu->addAction(pActionOpenCfgDir);
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
    //    debugApp() << "proc_action_codeFormat_Directory";
    proc_action_codeFormat_Pub(TYPE_DIR,autolist);
}

/**
 * @brief MainWindow::proc_action_codeFormat_File
 * 指定一个文件
 */
void MainWindow::proc_action_codeFormat_File()
{
    QStringList autolist;
    //    debugApp() << "proc_action_codeFormat_File";
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
    debugApp() << CAlgorithmPub::getMd5SumOfFile(m_apppath);
    //    debugApp() << CStringPub::getCurrentExePath();
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


void MainWindow::proc_action_codeFormat_Pub(int openType,QStringList autolist)
{
    debugApp() << "proc_action_codeFormat_Pub";
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
        debugApp() << "Open Files:" << openfiles;
        openFilePathRecent = openfiles.at(0);
        recentfiles_codeformat.append(openfiles);
        proc_AstyleInstance(openfiles);

    }
        break;
    case TYPE_FILES_NOUI:
    {
        /*打开一个dialog对话框，选择一个文件*/
        debugApp() << "Open Files:" << autolist;
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
        debugApp() << "Open Dir:" << openDirPath;
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
    debugApp() << "Astyle done:" << filelist;
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
            debugApp() << "[OpenFile]" + item ;
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

    debugApp() << "Word Find Text:" << findtext;
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
    debugApp() << "closeEvent";
    write_HistorySetting();
    event->accept();
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
#if UT_TESTCASE
    EXECLOOP(create_thread_network(m_thread_server, CNetPub::startServer),100);
#else
    EXECLOOP(create_thread_network(m_thread_server, CNetPub::startServer),1)
        #endif
}

void MainWindow::proc_threadmessage(const QString& info)
{
    debugApp() << "recv message:" << info;
}

void MainWindow::proc_threadprogress(int progress)
{
    debugApp() << "progress:" << progress;
}

void MainWindow::proc_threadfinished()
{
    debugApp() << "threadfinished:" ;
}




void MainWindow::proc_action_net_client()
{
#if UT_TESTCASE
    EXECLOOP(create_thread_network(m_thread_client,CNetPub::startClient),100);
#else
    EXECLOOP(create_thread_network(m_thread_client,CNetPub::startClient),1);
#endif
}

void MainWindow::proc_action_net_publish()
{
#if UT_TESTCASE
    EXECLOOP(create_thread_network(m_thread_client,CNetPub::startPublish),100);
#else
    EXECLOOP(create_thread_network(m_thread_publish,CNetPub::startPublish),1);
#endif
}


void MainWindow::proc_action_net_subscribe()
{
#if UT_TESTCASE
    EXECLOOP(create_thread_network(m_thread_client,CNetPub::startSubscribe),100);
#else
    EXECLOOP(create_thread_network(m_thread_subscribe,CNetPub::startSubscribe,false),1);
#endif
}





void MainWindow::proc_action_gen_pub(QString configfilename, int type)
{
    QString keyword   = CUIPub::getSelectTextEdit(ui->textEdit);
    QString linewords = CUIPub::getSelectLineTextEdit(ui->textEdit);
    QString lefttext  = CUIPub::getTextEdit(ui->textEdit);
    QString proctext  = CStringPub::emptyString();

    debugApp() << "keyword:" << keyword;
    debugApp() << "linewords:" << linewords;

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

    debugApp() << "proctext:" << proctext;
    if(!CUIPub::isCheckedQAction(ui->action_manycontent_proc) && CStringPub::strSimLen(proctext) >= MANYCONTENTMAX)
    {
        show_StatusTimer(QString("内容超过处理范围%1").arg(MANYCONTENTMAX));
        set_RightTextEdit(proctext);
        return;
    }
    set_RightTextEdit(CRegExpPub::procTextByRegExpList(configfilename, type,proctext));
}

void MainWindow::proc_action_edit_pub(QString configfilename, int type)
{
    QString proctext  = CStringPub::emptyString();

    debugApp() << "configfilename:" << configfilename;
    debugApp() << "type          :" << type;
    CUIPub::setPlainTextEdit(ui->textEdit_cfgTips, CRegExpPub::handlerTip(configfilename, type,CRegExpPub::FILE_TIPS));
    CUIPub::setPlainTextEdit(ui->textEdit_cfgBefore, CRegExpPub::handlerTip(configfilename, type, CRegExpPub::FILE_BEFORE));
    CUIPub::setPlainTextEdit(ui->textEdit_cfgAfter, CRegExpPub::handlerTip(configfilename, type, CRegExpPub::FILE_AFTER));
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
    CFilePub::deleteFileSameLineExt(m_ListFreqUseFile, configfilename);
}


/**
 * @brief MainWindow::proc_action_gen_custom_action
 * @param pAction
 * 自定义菜单，右键
 */
void MainWindow::proc_action_gen_custom_action(QAction *pAction)
{
    debugApp() << "custom action:" << pAction->text();
    debugApp() << "custom data  :" << pAction->data();

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

void MainWindow::proc_action_EditCfgFile(bool checked)
{
    if(CExpressPub::isFalse(checked))
    {
        if(CExpressPub::isFull(m_EditConfig))
        {
            CRegExpPub::handlerTipSave(m_EditConfig, 0, CUIPub::getTextEdit(ui->textEdit_cfgTips)   , CRegExpPub::FILE_TIPS  );
            CRegExpPub::handlerTipSave(m_EditConfig, 0, CUIPub::getTextEdit(ui->textEdit_cfgBefore) , CRegExpPub::FILE_BEFORE);
            CRegExpPub::handlerTipSave(m_EditConfig, 0, CUIPub::getTextEdit(ui->textEdit_cfgAfter)  , CRegExpPub::FILE_AFTER );
            show_StatusTimerWindowTitle(QString("保存配置文件成功:%1").arg(m_EditConfig));
        }
        CUIPub::hideTextEdit(ui->textEdit_cfgTips);
        CUIPub::hideTextEdit(ui->textEdit_cfgBefore);
        CUIPub::hideTextEdit(ui->textEdit_cfgAfter);
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
    CUIPub::explorerPathExt(CRegExpPub::getRegExpFileNameTips(m_EditConfig));
}

void MainWindow::proc_actionOpenConfigDir()
{
    QString dirPath = CFilePub::parentDir(CRegExpPub::getRegExpFileNameTips(m_EditConfig));
    CUIPub::explorerPathExt(dirPath);
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
    CUIPub::explorerPathExt(CFilePub::getCurrentPath(m_ListOpenFile));
    CUIPub::explorerPathExt(CFilePub::getCurrentPath(m_FileMode_AllL_ExecMulti));
    CUIPub::explorerPathExt(CFilePub::getCurrentPath(m_FileMode_SingleL_ExecMulti));
    CUIPub::explorerPathExt(CFilePub::getCurrentPath(m_FileNameMenu));
}

void MainWindow::proc_actionReload()
{
    CUIPub::clearTextEdit(ui->textEdit);
    CUIPub::pushButtonEmitClick(ui->pushButton_tryagain);
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
    CUIPub::setPlainTextEdit(ui->textEdit_cfgAfter,text.replace("\n", "$NL"));
}

void MainWindow::proc_actionCovertMulLine()
{
    QString text = CUIPub::getTextEdit(ui->textEdit_cfgAfter);
    CUIPub::setPlainTextEdit(ui->textEdit_cfgAfter,text.replace("$NL", "\n"));
}


void MainWindow::proc_action_TryAgain()
{
    //编辑配置文件模式
    if(CUIPub::isCheckedQAction(ui->action_EditCfgFile)
            || CExpressPub::isEmpty(m_EditConfig))
    {
        return;
    }

    setWindowTitle(QString("生成代码【%1】").arg(m_EditConfig));
    proc_action_gen_pub(m_EditConfig, EUM_CLASSTYPE::COMMON_OPERATIONS);

}

void MainWindow::proc_textEdit_textChanged()
{
    if(CUIPub::getCheckedQAction(ui->action_EditCfgFile)
            ||CUIPub::getCheckedQAction(ui->action_DeleteCfgFile))
    {
        return;
    }


    static QString oldText = CStringPub::emptyString();
    static QString curText = CStringPub::emptyString();

    curText = CUIPub::getTextEdit(ui->textEdit);
    if(CExpressPub::isEmpty(curText))
    {
        pCheckLeftTimer->stop();
        oldText = curText;
        return;
    }

    if(curText != oldText)
    {
        pCheckLeftTimer->start(iTimeout);
        oldText = curText;
        return;
    }

    oldText = curText;
    //    proc_action_TryAgain();
    pCheckLeftTimer->stop();

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

void MainWindow::proc_frequse_config(QString configfilename)
{
    CLogPub::logDefault("[proc_frequse_config]add config:" + configfilename);
    CStringPub::addStringHeaderUniqueMax(m_listfrequse, configfilename, m_dwLstFreqUseCnt);
    //    CLogPub::logDefault("[proc_frequse_config]m_ListFreqUseFile:" + configfilename);
    //    CLogPub::logDefault("[proc_frequse_config]m_listfrequse:" + CStringPub::stringList2StringEnter(m_listfrequse));
    CFilePub::writeFileWOnly(m_ListFreqUseFile, m_listfrequse);
}

void MainWindow::proc_action_openfilelist(QAction *pAction)
{
    if(CExpressPub::isTrue(CUIPub::getCheckedQAction(ui->action_EditCfgFile)))
    {
        show_StatusTimerWindowTitle("编译常用列表模式");
        CUIPub::explorerPathExt(m_ListOpenFile);
        return;
    }
    show_StatusTimerWindowTitle("打开配置文件" + pAction->text());
    CUIPub::explorerPathExt(pAction->text());
}

void MainWindow::append_RightMouseList(QAction *ptr)
{
    m_lstRightMouse.append(ptr);
}

void MainWindow::free_RightMouseList()
{
    //    foreach (QAction *ptr, m_lstRightMouse) {
    //        if(ptr){
    //            delete ptr;
    //        }
    //    }
    m_lstRightMouse.clear();
}

void MainWindow::proc_action_background_update(bool bFlag)
{
    debugApp() << "bFlag:" << bFlag;
}

void MainWindow::proc_action_update(bool bFlag)
{
    debugApp() << "bFlag:" << bFlag;
    update_generate_menu_left();
}

void MainWindow::proc_action_scan_test_dir(bool bFlag)
{
    debugApp() << "bFlag:" << bFlag;
    //支持创建多个界面
    pMulWinTest = new SuperTest();
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
}

void MainWindow::proc_pushButton_tryagain()
{
    proc_action_TryAgain();
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


void MainWindow::on_action_search_triggered()
{
    SHOWCURFUNC;
    CDialogSearch *pDiaglogKey = new CDialogSearch();
    //文件中的菜单列表
    QStringList menuList = CStringPub::emptyStringList();
    Qt::CaseSensitivity cs;
    QStringList resultlist = CStringPub::emptyStringList();
    QString findKey = CStringPub::emptyString();

    if(QDialog::Rejected == pDiaglogKey->exec())
    {
        goto ENDLABEL;
    }
    debugApp() << pDiaglogKey->getKey();
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
    CUIPub::clearAddListWidgetItemsAndShow(ui->listWidget_searchresult, resultlist);
    QObject::connect(ui->listWidget_searchresult, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(proc_listWidget_searchresult_ItemClicked(QListWidgetItem *)));

    //更新左侧常用列表
    updateListWidgetFrequse();

    delete pDiaglogKey;
    return;

ENDLABEL:
    CUIPub::clearHideListWidget(ui->listWidget_searchresult);
    delete pDiaglogKey;
}

void MainWindow::proc_listWidget_searchresult_ItemClicked(QListWidgetItem *item)
{
    QAction *tempAction = CUIPub::createActionData("tempAction", item->text());
    proc_action_gen_custom_action(tempAction);
    delete tempAction;
}

void MainWindow::updateListWidgetFrequse()
{
    CUIPub::clearAddListWidgetItemsAndShow(ui->listWidget_frequse, m_listfrequse);
    QObject::connect(ui->listWidget_frequse, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(proc_listWidget_searchresult_ItemClicked(QListWidgetItem *)));
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
