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
#include "cofficepub.h"
#include "expresspub.h"
#include "cdialogpub.h"
#include "cnetpub.h"
#include "cregexppub.h"
#include "cexpresspub.h"
#include <QDebug>
#include <QDesktopServices>
#include <QException>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QProgressBar>
#include <iostream>

extern int AyStyleMain(int argc, char** argv);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showVersion();
    initActionSets();
    initVars();
    initUiOther();

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


void MainWindow::initActionSets()
{
    QObject::connect(ui->action_codeFormat_File, SIGNAL(triggered()), this, SLOT(proc_action_codeFormat_File_trigger()));
    QObject::connect(ui->action_codeFormat_Directory, SIGNAL(triggered()), this, SLOT(proc_action_codeFormat_Directory_trigger()));
    QObject::connect(ui->action_codeFormat_Edit_Config, SIGNAL(triggered()), this, SLOT(proc_action_codeFormat_Edit_Config_trigger()));
    QObject::connect(ui->action_codeFormat_Save_Config, SIGNAL(triggered()), this, SLOT(proc_action_codeFormat_Save_Config_trigger()));
    QObject::connect(ui->action_codeFormat_Del_Config, SIGNAL(triggered()), this, SLOT(proc_action_codeFormat_Del_Config_trigger()));
    QObject::connect(ui->action_about, SIGNAL(triggered()), this, SLOT(proc_action_about_trigger()));
    QObject::connect(ui->menu_codeFormat_Recent, SIGNAL(triggered(QAction *)), this, SLOT(proc_menu_codeFormat_Recent_trigger(QAction *)));

    //mysql
    QObject::connect(ui->action_mysql_testdatabase, SIGNAL(triggered()), this, SLOT(proc_action_mysql_testdatabase_trigger()));


    //office
    QObject::connect(ui->action_office_open, SIGNAL(triggered()), this, SLOT(proc_action_office_open_trigger()));
    QObject::connect(ui->action_office_search_file, SIGNAL(triggered()), this, SLOT(proc_action_office_search_file_trigger()));
    QObject::connect(ui->action_office_search_dir, SIGNAL(triggered()), this, SLOT(proc_action_office_search_dir_trigger()));
    QObject::connect(ui->menu_document_open_recent, SIGNAL(triggered(QAction *)), this, SLOT(proc_menu_document_open_recent_trigger(QAction *)));
    QObject::connect(ui->menu_document_search_recent, SIGNAL(triggered(QAction *)), this, SLOT(proc_menu_document_search_recent_trigger(QAction *)));

    //net
    QObject::connect(ui->action_net_server, SIGNAL(triggered()), this, SLOT(proc_action_net_server_trigger()));
    QObject::connect(ui->action_net_client, SIGNAL(triggered()), this, SLOT(proc_action_net_client_trigger()));
    QObject::connect(ui->action_net_publish, SIGNAL(triggered()), this, SLOT(proc_action_net_publish_trigger()));
    QObject::connect(ui->action_net_subscribe, SIGNAL(triggered()), this, SLOT(proc_action_net_subscribe_trigger()));

    //generate
    QObject::connect(ui->action_gen_Constructor, SIGNAL(triggered()), this, SLOT(proc_action_gen_Constructor()));
    QObject::connect(ui->action_gen_Destructor, SIGNAL(triggered()), this, SLOT(proc_action_gen_Destructor()));
    QObject::connect(ui->action_gen_Getter, SIGNAL(triggered()), this, SLOT(proc_action_gen_Getter()));
    QObject::connect(ui->action_gen_Setter, SIGNAL(triggered()), this, SLOT(proc_action_gen_Setter()));
    QObject::connect(ui->action_gen_Getter_and_Setter, SIGNAL(triggered()), this, SLOT(proc_action_gen_Getter_and_Setter()));
    QObject::connect(ui->action_gen_Equality_Operators, SIGNAL(triggered()), this, SLOT(proc_action_gen_Equality_Operators()));
    QObject::connect(ui->action_gen_Relational_Operators, SIGNAL(triggered()), this, SLOT(proc_action_gen_Relational_Operators  ()));
    QObject::connect(ui->action_gen_Stream_Output_Operator  , SIGNAL(triggered()), this, SLOT(proc_action_gen_Stream_Output_Operator()));
    QObject::connect(ui->action_gen_Override_Functions, SIGNAL(triggered()), this, SLOT(proc_action_gen_Override_Functions()));
    QObject::connect(ui->action_gen_Implement_Functions, SIGNAL(triggered()), this, SLOT(proc_action_gen_Implement_Functions()));
    QObject::connect(ui->action_gen_Generate_Definitions, SIGNAL(triggered()), this, SLOT(proc_action_gen_Generate_Definitions()));


}


void MainWindow::initVars()
{
    openDirPathRecent = "/";
    openFilePathRecent = "/";
    openWordFilePathRecent = "/";
    logAstyleName = "astyle.log";
    cfgAstyleName = "astyle.conf";
    cfgAstyleNameOrg = cfgAstyleName + ".org";
    nameFilters.clear();
    recentfiles_codeformat.clear();
    recentfiles_document.clear();
    m_organization = "weilaidb";
    m_application = "codesets";
    m_pSettings = nullptr;

    m_thread_server = nullptr;
    m_thread_client = nullptr;
    m_thread_publish = nullptr;
    m_thread_subscribe = nullptr;
}

void MainWindow::initUiOther()
{
    //    this->setWindowIcon();
    pRightMouse = NULL;
    //QTextEdit 右键菜单
    ui->textEdit->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(ui->textEdit, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_generate_menu(QPoint)));

    //自定义菜单，从文件读取
    pMenuCustom = NULL;
    m_FileNameMenu = "reg/selfmenu.txt";
    CFilePub::createFileNoExist(m_FileNameMenu);
}


void MainWindow::slot_generate_menu(QPoint pos)
{
    Q_UNUSED(pos);
    if(pRightMouse)
    {
        delete pRightMouse;
    }
    debugApp() << "right mouse clicked!!";

    QCursor cur=this->cursor();
    pRightMouse = new QMenu(this);
    pRightMouse->addMenu(ui->menuGenerate);

    if(pMenuCustom)
    {
        CUIPub::clearMenu(pMenuCustom);
    }
    pMenuCustom = slot_fromfile_menu(m_FileNameMenu);
    if(pMenuCustom)
    {
        pRightMouse->addMenu(pMenuCustom);
    }
    pRightMouse->exec(cur.pos()); //关联到光标
}

QMenu *MainWindow::slot_fromfile_menu(QString filename)
{
    QStringList list = CStringPub::stringSplitbyNewLineFilterEmpty(CFilePub::readFileAll(filename));
    if(CExpressPub::isZero(list.length()))
    {
        return NULL;
    }

    QMenu *pMenu = new QMenu(CStringPub::stringSelfMenu());
    foreach (QString item, list) {
        QAction *pAction = new QAction(item);
        pMenu->addAction(pAction);
    }
    if(pMenu)
    {
        QObject::connect(pMenu, SIGNAL(triggered(QAction *)), this, SLOT(proc_action_gen_custom_action(QAction *)));
    }

    return pMenu;
}

void MainWindow::readSetting()
{
    readHistorySetting();
    addMenuCodeFormatRecent();
    addMenuDocumentOpenRecent();
    addMenuDocumentSearchRecent();
}

void MainWindow::pubHistorySetting(int type)
{
    quint8 ucType = type;
    m_pSettings = CUIPub::readHistorySettings(m_organization,m_application);
    CUIPub::procStringList(m_pSettings, BINDSTRWORDS(recentfiles_codeformat), ucType);
    CUIPub::procStringList(m_pSettings, BINDSTRWORDS(recentfiles_document), ucType);
    CUIPub::procString(m_pSettings, BINDSTRWORDS(openFilePathRecent), ucType);
    CUIPub::procString(m_pSettings, BINDSTRWORDS(openDirPathRecent), ucType);
    CUIPub::procString(m_pSettings, BINDSTRWORDS(openWordFilePathRecent), ucType);
}

void MainWindow::readHistorySetting()
{
    pubHistorySetting(CUIPub::TYPE_READ);
}


void MainWindow::writeHistorySetting()
{
    pubHistorySetting(CUIPub::TYPE_WRITE);
}


void MainWindow::proc_menu_codeFormat_Recent_trigger(QAction *action)
{
    QStringList autolist = CStringPub::actionNameList(action);
    CHECKSIZEZERORETURN(autolist);
    proc_action_codeFormat_Pub_trigger(TYPE_AUTO,autolist);
}
/**
 * @brief MainWindow::proc_action_codeFormat_Directory_trigger
 * 代码格式化，如何处理呢
 * 指定一个文件夹或文件来格式化吗
 */
void MainWindow::proc_action_codeFormat_Directory_trigger()
{
    QStringList autolist;
    //    debugApp() << "proc_action_codeFormat_Directory_trigger";
    proc_action_codeFormat_Pub_trigger(TYPE_DIR,autolist);
}

/**
 * @brief MainWindow::proc_action_codeFormat_File_trigger
 * 指定一个文件
 */
void MainWindow::proc_action_codeFormat_File_trigger()
{
    QStringList autolist;
    //    debugApp() << "proc_action_codeFormat_File_trigger";
    proc_action_codeFormat_Pub_trigger(TYPE_FILES,autolist);
}

void MainWindow::proc_action_codeFormat_Edit_Config_trigger()
{
    ui->textEdit->setText(CFilePub::readFileAll(cfgAstyleName));
    showStatus("编译Asytle配置....");
}

void MainWindow::proc_action_codeFormat_Save_Config_trigger()
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
void MainWindow::proc_action_codeFormat_Del_Config_trigger()
{
    CFilePub::deleteFile(cfgAstyleName);
    showStatus("删除Asytle配置成功");
}

void MainWindow::proc_action_about_trigger()
{
    showStatus(QString("当前版本是:") + APP_VERSION);
}


void MainWindow::proc_action_codeFormat_Pub_trigger(int openType,QStringList autolist)
{
    debugApp() << "proc_action_codeFormat_Pub_trigger";
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
                proc_action_codeFormat_Pub_trigger(TYPE_FILES_NOUI, autolist);
            }
            else if(true == CFilePub::isDir(item))
            {
                proc_action_codeFormat_Pub_trigger(TYPE_DIR_NOUI, autolist);
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
        WORD32 dwLen = strlen(item.toLocal8Bit().data());
        char *p = new char[dwLen + 1];
        memset(p,0,dwLen + 1);
        strcpy(p, item.toLocal8Bit().data());
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
        int result = QMessageBox::warning(NULL, "warning", QString("文件数量较多 %1，是否继续处理?").arg(filelist.size()), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
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
            listAstyleArgv = CStringPub::toStringList(CFilePub::readFileAll(cfgAstyleNameOrg).toLocal8Bit().split(SIGNENTERS));
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
    //char *argv[] = {" --style=allman  --style=ansi  --style=bsd  --style=break  -A1  --indent-switches  -S  --pad-return-type  -xq  --keep-one-line-statements  -o  --add-braces  -j  --max-continuation-indent=#  /  -M#  --indent-continuation=#  /  -xt#  --indent-preproc-block  -xW ", item.toLocal8Bit().data()};

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
    CUIPub::clearMenu(pMenu);

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

void MainWindow::clearLeftTextEdit()
{
    ui->textEdit->setText("");
}

void MainWindow::setRightTextEdit(QString str)
{
    ui->textBrowser->setText(str);
}

void MainWindow::clearRightTextEdit()
{
    ui->textBrowser->setText("");
}

void MainWindow::proc_action_mysql_testdatabase_trigger()
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

QStringList MainWindow::proc_action_office_auto_pub_trigger(QString filter, QStringList filterlist, QString &openRecent, QStringList &recentfiles, quint8 openDiagFlag, QStringList openfilelist)
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



void MainWindow::proc_action_office_action_pub_trigger(quint8 ucActionType, QStringList list,QString findtext)
{
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
}

/**
 * @brief MainWindow::proc_action_office_open_pub_trigger
 * @param filter
 * @param openRecent
 * @param openDiagFlag 是否打开对话框
 * @param openfilelist
 */
void MainWindow::proc_action_office_open_pub_trigger(QString filter,QStringList filterlist,  QString &openRecent,quint8 openDiagFlag, QStringList openfilelist)
{
    QStringList list = proc_action_office_auto_pub_trigger(filter, filterlist, openRecent, recentfiles_document, openDiagFlag, openfilelist);
    CHECKSIZEZERORETURN(list);
    proc_action_office_action_pub_trigger(ACTIONTYPE_OPEN, list, CStringPub::emptyString());
}


void MainWindow::proc_action_office_search_file_pub_trigger(QString filter,QStringList filterlist, QString openRecent, quint8 openDiagFlag, QStringList openfilelist)
{
    QString findtext;
    CHECKFALSERETURN(getDialogFindText(findtext));
    QStringList list = proc_action_office_auto_pub_trigger(filter, filterlist, openRecent, recentfiles_document, openDiagFlag, openfilelist);
    CHECKSIZEZERORETURN(list);
    proc_action_office_action_pub_trigger(ACTIONTYPE_SEARCH, list, findtext);
}

void MainWindow::proc_action_office_search_dir_pub_trigger(QString filter,QStringList filterlist, QString openRecent, quint8 openDiagFlag, QStringList openfilelist)
{
    QString findtext;
    CHECKFALSERETURN(getDialogFindText(findtext));
    CHECKEMPTY_TIPS_RETURN(findtext,showStatus, STRING_INPUT_FIND_KEY_EMPTY);
    QStringList list = proc_action_office_auto_pub_trigger(filter, filterlist, openRecent, recentfiles_document, openDiagFlag, openfilelist);
    CHECKSIZEZERO_TIPS_RETURN(list,showStatus, STRING_RES_FIND_FILES_EMPTY);
    proc_action_office_action_pub_trigger(ACTIONTYPE_SEARCH_ALLFILES, list, findtext);
}


void MainWindow::proc_action_office_search_file_trigger()
{
    proc_action_office_search_file_pub_trigger(FILTERWORD, CStringPub::emptyStringList(),  openWordFilePathRecent, OPENTYPE_YES_FILE, CStringPub::emptyStringList());
}

void MainWindow::proc_action_office_search_dir_trigger()
{
    proc_action_office_search_dir_pub_trigger(FILTERWORD, CStringPub::wordNameFilter(), openWordFilePathRecent, OPENTYPE_YES_DIR, CStringPub::emptyStringList());
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


void MainWindow::proc_action_office_open_trigger()
{
    proc_action_office_open_pub_trigger(FILTERWORD, CStringPub::emptyStringList(), openWordFilePathRecent, OPENTYPE_YES_FILE, CStringPub::emptyStringList());
}

void MainWindow::proc_menu_document_open_recent_trigger(QAction *action)
{
    QStringList autolist = CStringPub::actionNameList(action);
    CHECKSIZEZERORETURN(autolist);
    proc_action_office_open_pub_trigger(FILTERWORD, CStringPub::emptyStringList(), openWordFilePathRecent, OPENTYPE_NO_FILE, autolist);
}

void MainWindow::proc_menu_document_search_recent_trigger(QAction *action)
{
    QStringList autolist = CStringPub::actionNameList(action);
    CHECKSIZEZERORETURN(autolist);

    if(CFilePub::isDir(action->iconText()))
    {
        proc_action_office_search_dir_pub_trigger(FILTERWORD, CStringPub::wordNameFilter(), openWordFilePathRecent, OPENTYPE_NO_DIR, autolist);
    }
    else
    {
        proc_action_office_search_file_pub_trigger(FILTERWORD,CStringPub::emptyStringList(),  openWordFilePathRecent, OPENTYPE_NO_FILE, autolist);
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
            ,this,&MainWindow::proc_threadmessage_trigger);
    connect(pTthread,&CNetThreadPub::progress
            ,this,&MainWindow::proc_threadprogress_trigger);
    connect(pTthread,&CNetThreadPub::finished
            ,this,&MainWindow::proc_threadfinished_trigger);
    connect(pTthread, SIGNAL(finished()), pTthread, SLOT(deleteLater())); //线程释放自己
}


void MainWindow::proc_action_net_server_trigger()
{
#if UT_TESTCASE
    EXECLOOP(create_thread_network(m_thread_server, CNetPub::startServer),100);
#else
    EXECLOOP(create_thread_network(m_thread_server, CNetPub::startServer),1);
#endif
}

void MainWindow::proc_threadmessage_trigger(const QString& info)
{
    debugApp() << "recv message:" << info;
}

void MainWindow::proc_threadprogress_trigger(int progress)
{
    debugApp() << "progress:" << progress;
}

void MainWindow::proc_threadfinished_trigger()
{
    debugApp() << "threadfinished:" ;
}




void MainWindow::proc_action_net_client_trigger()
{
#if UT_TESTCASE
    EXECLOOP(create_thread_network(m_thread_client,CNetPub::startClient),100);
#else
    EXECLOOP(create_thread_network(m_thread_client,CNetPub::startClient),1);
#endif
}

void MainWindow::proc_action_net_publish_trigger()
{
#if UT_TESTCASE
    EXECLOOP(create_thread_network(m_thread_client,CNetPub::startPublish),100);
#else
    EXECLOOP(create_thread_network(m_thread_publish,CNetPub::startPublish),1);
#endif
}


void MainWindow::proc_action_net_subscribe_trigger()
{
#if UT_TESTCASE
    EXECLOOP(create_thread_network(m_thread_client,CNetPub::startSubscribe),100);
#else
    EXECLOOP(create_thread_network(m_thread_subscribe,CNetPub::startSubscribe,false),1);
#endif
}





void MainWindow::proc_action_gen_pub(int type)
{
    QString keyword   = CUIPub::getSelectTextEdit(ui->textEdit);
    QString linewords = CUIPub::getSelectLineTextEdit(ui->textEdit);
    QString lefttext  = CUIPub::getTextEdit(ui->textEdit);
    QString proctext  = CStringPub::emptyString();

    debugApp() << "keyword:" << keyword;
    debugApp() << "linewords:" << linewords;

    if(CExpressPub::isZero(CStringPub::strSimLen(keyword)) && CExpressPub::isZero(CStringPub::strSimLen(lefttext)))
    {
        setLeftTextEdit(CRegExpPub::handlerTip(type));
        setRightTextEdit(CStringPub::emptyString());
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

    setRightTextEdit(CRegExpPub::procTextByRegExpList(type,proctext));
}

void MainWindow::proc_action_gen_Constructor()
{

}

void MainWindow::proc_action_gen_Destructor()
{

}

void MainWindow::proc_action_gen_Getter()
{
    proc_action_gen_pub(EUM_CLASSTYPE::GETTER);
}

void MainWindow::proc_action_gen_Setter()
{
    proc_action_gen_pub(EUM_CLASSTYPE::SETTER);
}

void MainWindow::proc_action_gen_Getter_and_Setter()
{
    proc_action_gen_pub(EUM_CLASSTYPE::GETTER_AND_SETTER);
}

void MainWindow::proc_action_gen_Equality_Operators()
{

}

void MainWindow::proc_action_gen_Relational_Operators()
{

}

void MainWindow::proc_action_gen_Stream_Output_Operator()
{

}

void MainWindow::proc_action_gen_Override_Functions()
{

}

void MainWindow::proc_action_gen_Implement_Functions()
{

}

void MainWindow::proc_action_gen_Generate_Definitions()
{

}

void MainWindow::proc_action_gen_custom_action(QAction *pAction)
{
    debugApp() << "custom action:" << pAction->text();
}





