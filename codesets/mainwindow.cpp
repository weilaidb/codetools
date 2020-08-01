#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_cdialogasktext.h"
#include "astyle_main.h"
#include "debugApp.h"
#include "basetypepub.h"
#include "filepub.h"
#include "signpub.h"
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


extern int AyStyleMain(int argc, char** argv);


MainWindow::MainWindow(char *appexe, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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

    readSetting();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initDialog()
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

void MainWindow::showVersion()
{
    ui->statusbar->showMessage(APP_VERSION);
}

void MainWindow::initCheckBoxSets()
{

}


void MainWindow::initActionSets()
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

    //text edit
    QObject::connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(proc_textEdit_textChanged()));

    //clipboard change


    //check no exist path
//    QObject::connect(ui->action_checknoexistpath, SIGNAL(triggered(bool)), this, SLOT(proc_action_checknoexistpath(bool)));

}


void MainWindow::initVars()
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




void MainWindow::initUiSets()
{
    //    this->setWindowIcon();
    pRightMouse = nullptr;
    //QTextEdit 右键菜单
    GEN_MENU_PUB(ui->textEdit, slot_generate_menu_left);
    GEN_MENU_PUB(ui->textBrowser, slot_generate_menu_right);
    GEN_MENU_PUB(ui->textEdit_cfgTips, slot_generate_menu_leftbottom);

    //自定义菜单，从文件读取
    pMenuCustom = nullptr;
    CFilePub::createFileEmptyNoExistAndVar(m_FileNameMenu, "reg/selfmenu.txt");
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

    m_iListFreqUseCnt = 10;
    m_listfrequse = CFilePub::readFileAllFilterEmptyUniqueNoExistAndVar(m_ListFreqUseFile, "reg/frequse.txt");

    CFilePub::createFileEmptyNoExistAndVar(m_AttentionFile, "reg/attention.txt");

    //打开常用文件列表
    m_iListNormalUseCnt = 30;
    CFilePub::createFileEmptyNoExistAndVar(m_ListOpenFile, "reg/normalfiles.txt");
}

/**
 * @brief MainWindow::slot_generate_menu_left
 * @param pos
 * 左边显示生成的菜单
 */
void MainWindow::slot_generate_menu_left(QPoint pos)
{
    Q_UNUSED(pos)
    //此处删除会异常，正在显示的内容突然被删除
    CUIPub::clearMenuAll(&pRightMouse);

    debugApp() << "right mouse clicked!!";

    QCursor cur=this->cursor();
    pRightMouse = new QMenu(this);
    //可能与此处有关，因为ui->menuGenerate不能释放掉，一直在用，所以此处应该用拷贝
    //    pRightMouse->addMenu(CUIPub::copyMenu(ui->menuGenerate));

    pMenuCustom = slot_fromfile_menu(m_FileNameMenu);
    if(pMenuCustom)
    {
        pRightMouse->addMenu((pMenuCustom));
    }
    nodes_menu_left(pRightMouse);
    pRightMouse->exec(cur.pos()); //关联到光标
}

/**
 * @brief MainWindow::slot_generate_menu_right
 * @param pos
 * 右边显示生成的菜单
 */
void MainWindow::slot_generate_menu_right(QPoint pos)
{
    Q_UNUSED(pos)
    CUIPub::clearMenuAll(&pRightMouse);

    QCursor cur=this->cursor();
    pRightMouse = new QMenu(this);
    nodes_menu_right(pRightMouse);
    pRightMouse->exec(cur.pos()); //关联到光标
}

void MainWindow::slot_generate_menu_leftbottom(QPoint pos)
{
    Q_UNUSED(pos)
    CUIPub::clearMenuAll(&pRightMouse);

    QCursor cur=this->cursor();
    pRightMouse = new QMenu(this);
    nodes_menu_leftbottom(pRightMouse);
    pRightMouse->exec(cur.pos()); //关联到光标
}


QMenu *MainWindow::slot_fromfile_menu(QString filename)
{
    QStringList list = CFilePub::readFileAllFilterEmptyUnique(filename);
    QStringList modelist_singl_execmulti = CFilePub::readFileAllFilterEmptyUnique(m_FileMode_SingleL_ExecMulti);
    QStringList modelist_alll_execmulti = CFilePub::readFileAllFilterEmptyUnique(m_FileMode_AllL_ExecMulti);

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

    QObject::connect(pActionClearLeft, SIGNAL(triggered()), this, SLOT(proc_actionClearLeft()));
    QObject::connect(pActionPaste, SIGNAL(triggered()), this, SLOT(proc_actionPasteLeft()));
    QObject::connect(pActionSelectCopy, SIGNAL(triggered()), this, SLOT(proc_actionSelectCopy()));
    QObject::connect(pActionSelectAllCopy, SIGNAL(triggered()), this, SLOT(proc_actionSelectAllCopyLeft()));
    QObject::connect(pActionOpenCfgDir, SIGNAL(triggered()), this, SLOT(proc_actionOpenConfigDir()));
    QObject::connect(pActionOpenCfgMenu, SIGNAL(triggered()), this, SLOT(proc_actionOpenCfgMenu()));

    pMenu->addMenu(slot_frequse_menu());
    pMenu->addAction(pActionOpenCfgDir);
    pMenu->addAction(pActionOpenCfgMenu);
    pMenu->addMenu(slot_openfilelist_menu());
    pMenu->addAction(pActionClearLeft);
    pMenu->addAction(pActionSelectCopy);
    pMenu->addAction(pActionPaste);
    pMenu->addAction(pActionSelectAllCopy);

}

QMenu *MainWindow::slot_frequse_menu()
{
    QMenu *pFreqUse = new QMenu("常用配置列表");
    debugApp() << m_listfrequse.count();
    foreach (QString item, m_listfrequse) {
        QAction *pTmpAction = CUIPub::createActionFull(item);
        pFreqUse->addAction(pTmpAction);
    }

    if(pFreqUse)
    {
        QObject::connect(pFreqUse, SIGNAL(triggered(QAction *)), this, SLOT(proc_action_gen_custom_action(QAction *)));
    }

    return pFreqUse;
}

QMenu *MainWindow::slot_openfilelist_menu()
{
    QMenu *pOpenFile = new QMenu("文件列表");
    m_listNormalUse = CFilePub::readFileAllFilterEmptyUniqueSort(m_ListOpenFile);
    foreach (QString item, m_listNormalUse) {
        if(CUIPub::getCheckedQAction(ui->action_checknoexistpath)
                &&CStringPub::contain(item, "\\w+:"))
        {
            if(CFilePub::pathNoExist(item))
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


void MainWindow::nodes_menu_leftbottom(QMenu *pMenu)
{
    if(CExpressPub::isNullPtr(pMenu))
    {
        return;
    }
    QAction *pActionOpenCfgFile    = CUIPub::createAction("打开配置文件");

    QObject::connect(pActionOpenCfgFile, SIGNAL(triggered()), this, SLOT(proc_actionOpenConfigFile()));

    pMenu->addAction(pActionOpenCfgFile);
}


void MainWindow::readSetting()
{
    readHistorySetting();
    addMenuCodeFormatRecent();
    addMenuDocumentOpenRecent();
    addMenuDocumentSearchRecent();
}

void MainWindow::procHistorySetting(int type)
{
    quint8 ucType = type;
    m_pSettings = CUIPub::readHistorySettings(m_organization,m_application);
    CUIPub::procStringList(m_pSettings, BINDSTRWORDS(recentfiles_codeformat), ucType);
    CUIPub::procStringList(m_pSettings, BINDSTRWORDS(recentfiles_document), ucType);
    CUIPub::procString(m_pSettings, BINDSTRWORDS(openFilePathRecent), ucType);
    CUIPub::procString(m_pSettings, BINDSTRWORDS(openDirPathRecent), ucType);
    CUIPub::procString(m_pSettings, BINDSTRWORDS(openWordFilePathRecent), ucType);
    CUIPub::procAction(m_pSettings, ui->action_SwitchClearLeftText, ucType);
    CUIPub::procAction(m_pSettings, ui->action_ClipBoarChange, ucType);
    CUIPub::procAction(m_pSettings, ui->action_checknoexistpath, ucType);
}

void MainWindow::readHistorySetting()
{
    procHistorySetting(CUIPub::TYPE_READ);
}


void MainWindow::writeHistorySetting()
{
    procHistorySetting(CUIPub::TYPE_WRITE);
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
    showStatus("编译Asytle配置....");
}

void MainWindow::proc_action_codeFormat_Save_Config()
{
    QString result = ui->textEdit->toPlainText();
    if(result.trimmed().isEmpty())
    {
        showStatus("内容为空，不允许!!");
        return;
    }
    CFilePub::writeFileOnlly(cfgAstyleName, result);
    showStatus("保存Asytle配置成功");
}
void MainWindow::proc_action_codeFormat_Del_Config()
{
    CFilePub::deleteFile(cfgAstyleName);
    showStatus("删除Asytle配置成功");
}

void MainWindow::proc_action_about()
{
    debugApp() << CAlgorithmPub::getMd5SumOfFile(m_apppath);
//    debugApp() << CStringPub::getCurrentExePath();
    CLogPub::logDefault(m_apppath);
    showStatus(QString("当前版本是:") + APP_VERSION
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
    getNameFilter();

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
        procAstyleInstance(openfiles);

    }
        break;
    case TYPE_FILES_NOUI:
    {
        /*打开一个dialog对话框，选择一个文件*/
        debugApp() << "Open Files:" << autolist;
        procAstyleInstance(autolist);
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
        procAstyleInstance(openfiles);
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
        procAstyleInstance(openfiles);
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



WORD32 MainWindow::getAstyleFmt(QStringList filelist)
{
    getAstyleConfig();
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
    addMenuCodeFormatRecent();

    return listAstyleArgv.size();
}

void MainWindow::freeArgv()
{
    WORD32 i = 0;
    for (i = 0; i < dwArgc;i++) {
        delete m_argvp[i];
        m_argvp[i] = nullptr;
    }
}


void MainWindow::procAstyleInstance(QStringList filelist)
{
    if(0 == filelist.size())
    {
        showStatus("文件数量为空，不处理");
        return;
    }

    if(filelist.size() > ASTYLE_PROC_FILES_MAX)
    {
        showStatus("文件数量较多，建议不处理");
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

    dwArgc = getAstyleFmt(filelist);
    AyStyleMain(dwArgc, m_argvp);
    debugApp() << "Astyle done:" << filelist;
    freeArgv();
    CPrintPub::canclePrintToFile();

    showStatus("deal done! etc" + filelist.at(0));
    showTextBrower("Astyle following files deal done!" SIGNENTER + CStringPub::stringList2String(listAstyleArgv,SIGNENTER));
}


void MainWindow::showStatus(QString msg)
{
    ui->statusbar->showMessage(msg);
    if(1)
    {
        showStatusTimer(msg);
    }
}

void MainWindow::showStatusTimer(QString msg)
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

void MainWindow::showStatusTimerWindowTitle(QString msg)
{
    showStatusTimer(msg);
    setWindowTitle(msg);
}

void MainWindow::showTextBrower(QString msg)
{
    ui->textBrowser->setText(msg);
}

void MainWindow::showTextBrowerAppend(QString msg)
{
    ui->textBrowser->append(msg);
}


void MainWindow::getAstyleConfig()
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
        getAstyleOrgConfig();
        foreach (QString item, listAstyleArgv) {
            result += item + SIGNENTER;
        }
        CFilePub::writeFileOnlly(cfgAstyleNameOrg,result);
        CFilePub::writeFileOnlly(cfgAstyleName,result);
    }
}

void MainWindow::getAstyleOrgConfig()
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

void MainWindow::getNameFilter()
{
    nameFilters.clear();
    nameFilters << "*.c";
    nameFilters << "*.cpp";
    nameFilters << "*.cxx";
    nameFilters << "*.h";
    nameFilters << "*.hpp";
    nameFilters << "*.java";
}

void MainWindow::addMenuRecent(QStringList recent, QMenu *pMenu)
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


void MainWindow::addMenuCodeFormatRecent()
{
    addMenuRecent(recentfiles_codeformat, ui->menu_codeFormat_Recent);
}

void MainWindow::addMenuDocumentOpenRecent()
{
    addMenuRecent(recentfiles_document, ui->menu_document_open_recent);
}

void MainWindow::addMenuDocumentSearchRecent()
{
    addMenuRecent(recentfiles_document, ui->menu_document_search_recent);
}

void MainWindow::setLeftTextEdit(QString str)
{
    ui->textEdit->setText(str);
}

void MainWindow::clrLeftTextEdit()
{
    ui->textEdit->setText("");
}

void MainWindow::setRightTextEdit(QString str)
{
    ui->textBrowser->setText(str);
}

void MainWindow::clrRightTextEdit()
{
    ui->textBrowser->setText("");
}

void MainWindow::proc_action_mysql_testdatabase()
{
    QString hostName;
    QString dbName;
    QString userName;
    QString password;
    //    QSqlDatabase dbconn;

    hostName = "localhost";   // 主机名
    dbName = "alldb";   // 数据库名称
    userName = "root";   // 用户名
    password = "Zzerp123";   // 密码

    CSqlPub::openDb(hostName, dbName, userName, password);

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
        CHECKFALSE_TIPS_RETURN(ret, showStatus, STRING_TIPS_DIR_NO_SUPPORT);

        ret = CFilePub::fileExist(filename);
        CHECKFALSE_TIPS_RETURN(ret, showStatus, STRING_TIPS_FILE_NO_EXIST);

        COfficePub *pObjOffice = new COfficePub();
        setRightTextEdit(pObjOffice->readWord(filename));
        showStatus("打开文档成功!" + filename);
    }
        break;
    case ACTIONTYPE_SEARCH:
    {
        filename = list.at(0);

        ret = CFilePub::fileExist(filename);
        CHECKFALSE_TIPS_RETURN(ret, showStatus, STRING_TIPS_FILE_NO_EXIST);

        COfficePub *pObjOffice = new COfficePub(findtext);
        setRightTextEdit(pObjOffice->readWordFindText(filename));
        setLeftTextEdit(findtext);
        showStatus("查找文档结束!" + filename);
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
        setRightTextEdit(result);
        setLeftTextEdit(findtext);
        showStatus("查找文档结束!" + list.at(0));
    }
        break;
    default:
        break;
    }
    updateRecent(recentfiles_document,  ui->menu_document_search_recent);
    updateRecent(recentfiles_document,  ui->menu_document_open_recent);
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
    CHECKFALSERETURN(getDialogFindText(findtext));
    QStringList list = proc_action_office_auto_pub(filter, filterlist, openRecent, recentfiles_document, openDiagFlag, openfilelist);
    CHECKSIZEZERORETURN(list);
    proc_action_office_action_pub(ACTIONTYPE_SEARCH, list, findtext);
}

void MainWindow::proc_action_office_search_dir_pub(QString filter,QStringList filterlist, QString openRecent, quint8 openDiagFlag, QStringList openfilelist)
{
    QString findtext;
    CHECKFALSERETURN(getDialogFindText(findtext));
    CHECKEMPTY_TIPS_RETURN(findtext,showStatus, STRING_INPUT_FIND_KEY_EMPTY);
    QStringList list = proc_action_office_auto_pub(filter, filterlist, openRecent, recentfiles_document, openDiagFlag, openfilelist);
    CHECKSIZEZERO_TIPS_RETURN(list,showStatus, STRING_RES_FIND_FILES_EMPTY);
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



quint8 MainWindow::getDialogFindText(QString &findtext)
{
    quint8 ucresult = false;
    QString result("");

    initDialog();
    int ret=pDialog->exec () ;// 以模态方式显示对话框
    if (ret==QDialog::Accepted)
    { //OK按钮被按下，获取对话框上的输入，设置行数和列数
        findtext = uiDialog->textEdit->toPlainText();
        ucresult = true;
    }
    delete pDialog;
    delete uiDialog;

    debugApp() << "Word Find Text:" << findtext;
    setLeftTextEdit("Word Find Text:" + findtext);

    return ucresult;
}




void MainWindow::updateRecent(QStringList &list, QMenu *pMenu)
{
    addMenuRecent(list,pMenu);
}

void MainWindow::updateRecentAppend(QStringList &list, QString name, QMenu *pMenu)
{
    list.append(name);
    addMenuRecent(list,pMenu);
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
    writeHistorySetting();
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
        showStatus("正在运行中...");
        return;
    }

    showStatus("开始运行");
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
        CUIPub::setTextEditOnEmpty(ui->textEdit, CRegExpPub::handlerTip(configfilename, type, CRegExpPub::FILE_TIPS));
        setRightTextEdit(CStringPub::emptyString());
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

    setRightTextEdit(CRegExpPub::procTextByRegExpList(configfilename, type,proctext));
}

void MainWindow::proc_action_edit_pub(QString configfilename, int type)
{
    QString proctext  = CStringPub::emptyString();

    debugApp() << "configfilename:" << configfilename;
    debugApp() << "type          :" << type;
    CUIPub::setTextEdit(ui->textEdit_cfgTips, CRegExpPub::handlerTip(configfilename, type,CRegExpPub::FILE_TIPS));
    CUIPub::setTextEdit(ui->textEdit_cfgBefore, CRegExpPub::handlerTip(configfilename, type, CRegExpPub::FILE_BEFORE));
    CUIPub::setTextEdit(ui->textEdit_cfgAfter, CRegExpPub::handlerTip(configfilename, type, CRegExpPub::FILE_AFTER));
}

void MainWindow::proc_action_editinginfo(QString configfilename, int type)
{
    Q_UNUSED(type)
    proc_action_edit_pub(configfilename, EUM_CLASSTYPE::EDIT_CFGFILE_OPERATIONS);
    CStringPub::setString(m_EditConfig, configfilename);
    showStatusTimerWindowTitle(QString("编译配置文件中【%1】").arg(m_EditConfig));
}

void MainWindow::proc_action_deleteinfo(QString configfilename, int type)
{
    Q_UNUSED(type)

    if(CUIPub::showBoxInfoIsNo(QString("确认删除配置文件%1").arg(configfilename)))
    {
        return;
    }
    showStatusTimerWindowTitle(QString("删除配置文件【%1】").arg(configfilename));

    CFilePub::deleteFile(CRegExpPub::getRegExpFileNameBefore(CRegExpPub::getFileNameByClassCfgType(configfilename, type)));
    CFilePub::deleteFile(CRegExpPub::getRegExpFileNameAfter(CRegExpPub::getFileNameByClassCfgType(configfilename, type)));
    CFilePub::deleteFile(CRegExpPub::getRegExpFileNameTips(CRegExpPub::getFileNameByClassCfgType(configfilename, type)));

    CFilePub::deleteFileSameLine(m_FileNameMenu, configfilename);
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
            showStatusTimerWindowTitle(QString("保存配置文件成功:%1").arg(m_EditConfig));
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
            showStatusTimerWindowTitle(QString("进入编辑配置文件模式"));
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
        showStatusTimerWindowTitle(QString("退出删除配置文件模式"));
        return;
    }
    showStatusTimerWindowTitle(QString("进入删除配置文件模式"));
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
    CUIPub::setTextEdit(ui->textEdit, CUIPub::getClipBoardText());
}

void MainWindow::proc_actionSelectCopy()
{
    CUIPub::setClipBoardText(CUIPub::getSelectTextEdit(ui->textEdit));
}

void MainWindow::proc_actionSelectAllCopyLeft()
{
    CUIPub::setClipBoardText(CUIPub::getTextEdit(ui->textEdit));
}


void MainWindow::proc_actionOpenConfigDir()
{
    CUIPub::explorerPath(CRegExpPub::getConfigBase());
}

void MainWindow::proc_actionOpenConfigFile()
{
    CUIPub::explorerPath(CRegExpPub::getRegExpFileNameTips(m_EditConfig));
}


void MainWindow::proc_actionOpenCfgMenu()
{
    CUIPub::explorerPath(CFilePub::getCurrentPath(m_FileMode_AllL_ExecMulti));
    CUIPub::explorerPath(CFilePub::getCurrentPath(m_FileMode_SingleL_ExecMulti));
    CUIPub::explorerPath(CFilePub::getCurrentPath(m_FileNameMenu));
}


void MainWindow::proc_actionEditCfgFile()
{
    CUIPub::explorerPath(CRegExpPub::getConfigBefore());
}

void MainWindow::proc_actionSaveCfgFile()
{
    CUIPub::explorerPath(CRegExpPub::getConfigBefore());
}


void MainWindow::proc_actionClearRight()
{
    CUIPub::clearTextBrowser(ui->textBrowser);
}

void MainWindow::proc_actionPasteRight()
{
    CUIPub::setTextBrowser(ui->textBrowser, CUIPub::getClipBoardText());
}

void MainWindow::proc_actionSelectAllCopyRight()
{
    CUIPub::setClipBoardText(CUIPub::getTextBrowser(ui->textBrowser));
}

void MainWindow::proc_actionClearEmpty()
{
    CUIPub::setTextBrowser(ui->textBrowser, CStringPub::stringFilterEmpty(CUIPub::getTextBrowser(ui->textBrowser)));
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
        CUIPub::setTextEdit(ui->textEdit, curText);
        proc_action_TryAgain();
        oldText = curText;
        return;
    }

    oldText = curText;
}

void MainWindow::proc_frequse_config(QString configfilename)
{
    CStringPub::addStringUniqueSortMax(m_listfrequse, configfilename, m_iListFreqUseCnt);
    CFilePub::writeFileWOnly(m_ListFreqUseFile, m_listfrequse);
}

void MainWindow::proc_action_openfilelist(QAction *pAction)
{
    if(CExpressPub::isTrue(CUIPub::getCheckedQAction(ui->action_EditCfgFile)))
    {
        showStatusTimerWindowTitle("编译常用列表模式");
        CUIPub::explorerPath(m_ListOpenFile);
        return;
    }
    showStatusTimerWindowTitle("打开配置文件" + pAction->text());
    CUIPub::explorerPath(pAction->text());
}
