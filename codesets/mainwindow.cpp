#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "astyle_main.h"
#include "debugApp.h"
#include "basepub.h"
#include "filepub.h"
#include "carraypub.h"
#include "signpub.h"
#include <QDebug>
#include <QDesktopServices>
#include <QFileDialog>


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
        QString filenames_str("");
        foreach (QString item, openfiles) {
            debugApp() << "AyStyle:" << item;
            filenames_str = item + SIGNENTER;
        }

        getAstyleFmt(filenames_str);
        int argc = getAstyleArgc();
        AyStyleMain(argc, m_argvp);
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
    memset(filebuf, 0, sizeof(filebuf));
}


void MainWindow::getAstyleFmt(QString item)
{
#define ARGVITEM(STR)  strcpy(m_argv[lp++], STR);

    memset(m_argv,0, sizeof (m_argv));
    memset(m_argvp,0, sizeof (m_argvp));

    snprintf(filebuf, sizeof(filebuf), "%s", item.toLocal8Bit().data());

    int lp=0;
    ARGVITEM("app.exe");
    ARGVITEM( "--style=ansi");
    ARGVITEM( "-s4");
    ARGVITEM( "-S");
    ARGVITEM( "-N");
    ARGVITEM( "-L");
    ARGVITEM( "-m0");
    ARGVITEM( "-M40");
    ARGVITEM( "--convert-tabs");
    ARGVITEM( "--suffix=.pre");
    ARGVITEM( filebuf);

    int i = 0;
    for (i = 0; i < ARGVROWS;i ++) {
        if('\0' == m_argv[i][0])
        {
            break;
        }
        m_argvp[i] = (char *)m_argv[i];
    }

    CArrayPub::printArray(m_argv);

//            char *argv[] = {" --style=allman  --style=ansi  --style=bsd  --style=break  -A1  --indent-switches  -S  --pad-return-type  -xq  --keep-one-line-statements  -o  --add-braces  -j  --max-continuation-indent=#  /  -M#  --indent-continuation=#  /  -xt#  --indent-preproc-block  -xW ", item.toLocal8Bit().data()};


}


UINT32 MainWindow::getAstyleArgc()
{
    UINT32 dwCnt = 0;
    int i = 0;
    for (i = 0; i < ARGVROWS;i ++) {
        if(nullptr == m_argvp[i])
        {
           break;
        }
        dwCnt++;
    }

    return dwCnt;
}
