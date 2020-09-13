#include "supertest.h"
#include "ui_supertest.h"
#include "debugApp.h"

#include <cexpresspub.h>
#include <cfilepub.h>
#include <cstringpub.h>
#include <cuipub.h>

SuperTest::SuperTest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SuperTest)
{
    ui->setupUi(this);
    init_ActionSets();
    init_PushButtonSets();
    init_ListWidget();
    init_Vars();

}

SuperTest::~SuperTest()
{
    delete ui;
}

void SuperTest::init_ActionSets()
{
    QObject::connect(ui->action_scan_test_dir, SIGNAL(triggered()), this, SLOT(proc_pushButton_load_test_dir()));
}

void SuperTest::init_PushButtonSets()
{
    QObject::connect(ui->pushButton_load_test_dir, SIGNAL(clicked()), this, SLOT(proc_pushButton_load_test_dir()));

}

void SuperTest::init_Vars()
{
    file_content_txt = "content.txt";
    file_result_log = "result.log";
}

void SuperTest::init_ListWidget()
{
    QObject::connect(ui->listWidget_load_dir, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(proc_listWidget_load_dir_ItemDoubleClicked(QListWidgetItem *)));

}

void SuperTest::on_pushButton_load_test_dir_clicked()
{
    //    debugApp() << "proc_pushButton_load_test_dir";
}


void SuperTest::proc_pushButton_load_test_dir()
{
    debugApp() << "proc_pushButton_load_test_dir";
    //    QString filter = "*.*;;";
    //    QStringList getFileNames = CFilePub::getOpenDiagFiles(openFilePathRecent, filter);
    QString tips = "请选择扫描的测试的目录";
    QString dirname = CFilePub::getExistDir(tips, openFilePathRecent);
    if(CExpressPub::isZero(CStringPub::strSimLen(dirname)))
    {
        return;
    }

    config_cur_load_path(dirname);

    QStringList namefilter;
    namefilter << "*.*";
    QStringList filelist = CFilePub::getFileAllAbsoluteNames(namefilter, dirname);
    //    debugApp() << "filelist:" << filelist;
    filelist = CStringPub::filterFileListInclude(file_content_txt, filelist);
    filelist = CStringPub::filterFileListNoInclude(file_result_log, filelist);
    debugApp() << "filtered filelist:" << filelist;

    CUIPub::addListWidgetItems_ClearFirst(ui->listWidget_load_dir, filelist);

}

void SuperTest::config_cur_load_path(QString path)
{
    dir_cur_loaded = path;
    ui->label_load_path->setText(dir_cur_loaded);
}


void SuperTest::on_pushButton_open_test_dir_clicked()
{
    if(CStringPub::strSimLen(dir_cur_loaded))
    {
        CFilePub::openSystemPathOrUrl(dir_cur_loaded);
    }
}

void SuperTest::proc_listWidget_load_dir_ItemDoubleClicked(QListWidgetItem *item)
{
    ENTERTIPS;
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    CUIPub::setTextEdit(ui->textEdit_test_content, CFilePub::readFileAll(item->text()));
    CUIPub::setTextEdit(ui->textEdit_test_result, CFilePub::readFileAll(item->text() + "." + file_result_log));
}
