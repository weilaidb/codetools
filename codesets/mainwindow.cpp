#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "astyle_main.h"
#include "debugApp.h"
#include "basepub.h"
#include "filepub.h"
#include "carraypub.h"
#include "signpub.h"
#include "cprintpub.h"
#include "cstringpub.h"
#include "cfilepub.h"
#include <QDebug>
#include <QDesktopServices>
#include <QException>
#include <QFileDialog>
#include <QProcess>


extern int AyStyleMain(int argc, char** argv);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showVersion();
    actionSets();
    initVars();


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showVersion()
{
    ui->statusbar->showMessage(APP_VERSION);
}

void MainWindow::actionSets()
{
    QObject::connect(ui->action_codeFormat_File, SIGNAL(triggered()), this, SLOT(proc_action_codeFormat_File_trigger()));
    QObject::connect(ui->action_codeFormat_Directory, SIGNAL(triggered()), this, SLOT(proc_action_codeFormat_Directory_trigger()));
    QObject::connect(ui->action_codeFormat_Edit_Config, SIGNAL(triggered()), this, SLOT(proc_action_codeFormat_Edit_Config_trigger()));
    QObject::connect(ui->action_codeFormat_Save_Config, SIGNAL(triggered()), this, SLOT(proc_action_codeFormat_Save_Config_trigger()));
    QObject::connect(ui->action_codeFormat_Del_Config, SIGNAL(triggered()), this, SLOT(proc_action_codeFormat_Del_Config_trigger()));
}

/**
 * @brief MainWindow::proc_action_codeFormat_Directory_trigger
 * 代码格式化，如何处理呢
 * 指定一个文件夹或文件来格式化吗
 */
void MainWindow::proc_action_codeFormat_Directory_trigger()
{
    debugApp() << "proc_action_codeFormat_Directory_trigger";
    proc_action_codeFormat_Pub_trigger(TYPE_DIR);
}

/**
 * @brief MainWindow::proc_action_codeFormat_File_trigger
 * 指定一个文件
 */
void MainWindow::proc_action_codeFormat_File_trigger()
{
    debugApp() << "proc_action_codeFormat_File_trigger";
    proc_action_codeFormat_Pub_trigger(TYPE_FILES);
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


void MainWindow::proc_action_codeFormat_Pub_trigger(int openType)
{
    debugApp() << "proc_action_codeFormat_Pub_trigger";

    switch (openType) {
    case TYPE_FILES:
    {
        /*打开一个dialog对话框，选择一个文件*/
        QStringList openfiles = QFileDialog::getOpenFileNames();
        if(openfiles.isEmpty())
        {
            return;
        }
        debugApp() << "Open Files:" << openfiles;
        procAstyleInstance(openfiles);
    }
        break;
    case TYPE_DIR:
    {
        /*打开一个dialog对话框，选择一个文件夹*/
        //文件夹路径
        QString openDirPath = QFileDialog::getExistingDirectory(
                    this, "choose Directory",
                    openDirPathRecent);
        if (openDirPath.isEmpty())
        {
            return;
        }
        openDirPath += "/";
        openDirPathRecent = openDirPath;
        debugApp() << "Open Dir:" << openDirPath;
    }
        break;

    default:
        break;
    }

}


void MainWindow::initVars()
{
    openDirPathRecent = "/";
    logAstyleName = "astyle.log";
    cfgAstyleName = "astyle.conf";
    cfgAstyleNameOrg = cfgAstyleName + ".org";
}


WORD32 MainWindow::getAstyleFmt(QStringList filelist)
{
    getAstyleConfig();
    listAstyleArgv << (filelist);


    m_argvp = new char*[listAstyleArgv.size()];
//    debugApp() << "listAstyleArgv:" << listAstyleArgv;

    int i = 0;
    foreach (QString item, listAstyleArgv) {
        WORD32 dwLen = strlen(item.toLocal8Bit().data());
        char *p = new char[dwLen + 1];
        memset(p,0,dwLen + 1);
        strcpy(p, item.toLocal8Bit().data());
        m_argvp[i++] = p;
    }

//    CArrayPub::printArray((char **)m_argvp, listAstyleArgv.size());

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

        if(0 == listAstyleArgv.size())
        {
            listAstyleArgv = CStringPub::toStringList(CFilePub::readFileAll(cfgAstyleNameOrg).toLocal8Bit().split(SIGNENTERS));
        }
    }
    else
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
        listAstyleArgv << ("-xW ");
        //char *argv[] = {" --style=allman  --style=ansi  --style=bsd  --style=break  -A1  --indent-switches  -S  --pad-return-type  -xq  --keep-one-line-statements  -o  --add-braces  -j  --max-continuation-indent=#  /  -M#  --indent-continuation=#  /  -xt#  --indent-preproc-block  -xW ", item.toLocal8Bit().data()};

        QString result("");
        foreach (QString item, listAstyleArgv) {
            result += item + SIGNENTER;
        }

        CFilePub::writeFileOnlly(cfgAstyleNameOrg,result);
        CFilePub::writeFileOnlly(cfgAstyleName,result);
    }
}
