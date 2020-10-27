#include "supertest.h"
#include "ui_supertest.h"
#include "debugApp.h"
#include "cdialognewut.h"

#include <QMessageBox>
#include <cexpresspub.h>
#include <cfilepub.h>
#include <csignpub.h>
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
    init_CheckBoxSets();
    init_Vars();
    init_UiSets();

    read_Setting();
}

SuperTest::~SuperTest()
{
    delete ui;
}

void SuperTest::init_ActionSets()
{
    QObject::connect(ui->action_scan_test_dir, SIGNAL(triggered()), this, SLOT(proc_pushButton_load_test_dir()));
    QObject::connect(ui->action_about, SIGNAL(triggered()), this, SLOT(proc_actionAbout()));
}

void SuperTest::init_PushButtonSets()
{
    QObject::connect(ui->pushButton_load_test_dir, SIGNAL(clicked()), this, SLOT(proc_pushButton_load_test_dir()));

}

void SuperTest::init_Vars()
{
    file_content_txt = "content.txt";
    file_result_log = "result.log";

    m_organization = "weilaidb";
    m_application = "supertest";
    m_AttentionFile = "reg/attention_st.txt";

}

void SuperTest::init_UiSets()
{
    pRightMouse = nullptr;
    GEN_MENU_PUB(ui->textEdit_test_content, proc_generate_menu_left);
    CUIPub::clearMenuAll(&pRightMouse);

    pRightMouse = new QMenu(this);
    nodes_menu_leftbottom(pRightMouse);

    pRightMouseListWidget = new QMenu(this);
    nodes_menu_listwidget(pRightMouseListWidget);
    QObject::connect(pRightMouseListWidget, SIGNAL(triggered(QAction *)), this, SLOT(proc_menu_RightMouseListWidget(QAction *)));


    CUIPub::setSpliterFactor(ui->splitter_4, 0, 4);
    CUIPub::setSpliterFactor(ui->splitter_4, 1, 6);


    //自定义菜单
    ui->listWidget_load_dir->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(ui->listWidget_load_dir, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(proc_customContextMenuRequested(QPoint)));

    //    customContextMenuRequested(const QPoint &pos);

}

void SuperTest::proc_generate_menu_left(QPoint pos)
{
    Q_UNUSED(pos)
    debugApp() << "right mouse clicked!!";
    QCursor cur=this->cursor();

    if(pRightMouse)
    {
        pRightMouse->exec(cur.pos()); //关联到光标
    }
}


void SuperTest::init_ListWidget()
{
    QObject::connect(ui->listWidget_load_dir, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(proc_listWidget_load_dir_ItemClicked(QListWidgetItem *)));
    QObject::connect(ui->listWidget_load_dir, SIGNAL(currentRowChanged(int)), this, SLOT(OnListWidgetCurrentListChanged(int)));

}

void SuperTest::init_CheckBoxSets()
{
    QObject::connect(ui->checkBox_fullPath, SIGNAL(stateChanged(int)), this, SLOT(proc_checkBox_fullPath_stateChaned(int)));
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
    on_pushButton_reload_dir_clicked();
}

void SuperTest::proc_actionAbout()
{
    CUIPub::showBoxInfoIsNo(CFilePub::readFileAll(m_AttentionFile));
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

void SuperTest::proc_listWidget_load_dir_ItemClicked(QListWidgetItem *item)
{
    ENTERTIPS;
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    CUIPub::setTextEdit(ui->textEdit_test_content, CFilePub::readFileAll(proc_itemWholePathOnCheckBox(item->text())));
    CUIPub::setTextEdit(ui->textEdit_test_result, CFilePub::readFileAll(proc_itemWholePathOnCheckBox(item->text()) + CSignPub::signDot() + file_result_log));
    file_cur_item_load = proc_itemWholePathOnCheckBox(item->text());

    m_RenameIndex = CUIPub::getListWidgetCurrentRow(ui->listWidget_load_dir); //用来保存需要修改名称的index
    m_RenamePrev = CUIPub::getListWidgetCurrentItem(ui->listWidget_load_dir)->text(); //用来保存需要修改前的名称
}


void SuperTest::OnListWidgetCurrentListChanged(int index)
{
    ENTERTIPS;
    printf("index : %d(%#x)\n", index, index);

    if(0 == CStringPub::strSimLen(m_RenamePrev))
    {
        return;
    }

    if(CUIPub::getListWidgetItemText(ui->listWidget_load_dir, m_RenameIndex) == m_RenamePrev)
    {
        return;
    }


    QString fileNamePre = proc_itemWholePathOnCheckBox(m_RenamePrev);
    QString fileNameAft = proc_itemWholePathOnCheckBox(CUIPub::getListWidgetItemText(ui->listWidget_load_dir, m_RenameIndex));
//    debugApp() << "fileNamePre:" << fileNamePre;
//    debugApp() << "fileNameAft:" << fileNameAft;

    bool ok = QFile::rename(fileNamePre, fileNameAft);
    if (!ok)
    {
        QMessageBox::information(NULL, tr("Error"), tr("Rename Failed"));
        return;
    }
}

//获取全路径
QString SuperTest::proc_itemWholePathOnCheckBox(QString text)
{
    if(CUIPub::isCheckedQCheckBox(ui->checkBox_fullPath))
    {
        return CStringPub::toNativeSeparators(text);
    }
    else
    {
        QString relatePath  = text;
        relatePath = CUIPub::getLabelEdit(ui->label_load_path) + QDir::separator() + relatePath;
        return CStringPub::toNativeSeparators(relatePath);
    }
}

void SuperTest::on_pushButton_reload_dir_clicked()
{
    QStringList namefilter;
    namefilter << "*.*";
    QStringList filelist = CStringPub::emptyStringList();
    if(CUIPub::isCheckedQCheckBox(ui->checkBox_fullPath))
    {
        filelist = CFilePub::getFileAllAbsoluteNames(namefilter, dir_cur_loaded);
    }
    else
    {
        filelist = CFilePub::getFileAllRelateNames(namefilter, dir_cur_loaded);
    }
    //    debugApp() << "filelist:" << filelist;
    filelist = CStringPub::filterFileListInclude(file_content_txt, filelist);
    filelist = CStringPub::filterFileListNoInclude(file_result_log, filelist);
    debugApp() << "filtered filelist:" << filelist;

    QString findstr = CUIPub::getLineEdit(ui->lineEdit);
    QString mode = "";
    if(CStringPub::strSimLen(findstr))
    {
        Qt::CaseSensitivity cs = (CUIPub::isCheckedQCheckBox(ui->checkBox) == true) ? Qt::CaseSensitive : Qt::CaseInsensitive;
        filelist = CStringPub::filterFileListInclude(findstr, filelist, cs);
        mode = "[过滤模式]";
    }

    CUIPub::addListWidgetItems_ClearFirst(ui->listWidget_load_dir, filelist);

    CUIPub::showStatusBarTimerBoth(ui->statusbar, QString("%1用例个数:%2").arg(mode).arg(ui->listWidget_load_dir->count()));
}

void SuperTest::nodes_menu_leftbottom(QMenu *pMenu)
{
    if(CExpressPub::isNullPtr(pMenu))
    {
        return;
    }
    QAction *pActionOpenCfgFile    = CUIPub::createAction("打开当前配置文件");
    QAction *pActionOpenCfgDir     = CUIPub::createAction("打开当前配置文件夹");
    QAction *pActionSaveFile       = CUIPub::createAction("保存");
    QAction *pActionReloadFile         = CUIPub::createAction("重新加载");
    //    append_RightMouseList(pActionOpenCfgFile);
    //    append_RightMouseList(pActionOpenCfgDir);
    QObject::connect(pActionOpenCfgFile, SIGNAL(triggered()), this, SLOT(proc_actionOpenConfigFile()));
    QObject::connect(pActionOpenCfgDir, SIGNAL(triggered()), this, SLOT(proc_actionOpenConfigDir()));
    QObject::connect(pActionSaveFile, SIGNAL(triggered()), this, SLOT(proc_actionSaveFile()));
    QObject::connect(pActionReloadFile, SIGNAL(triggered()), this, SLOT(proc_actionReloadFile()));

    pMenu->addAction(pActionOpenCfgFile);
    pMenu->addAction(pActionOpenCfgDir);
    pMenu->addAction(pActionReloadFile);
    pMenu->addAction(pActionSaveFile);
}

//自定义菜单
void SuperTest::nodes_menu_listwidget(QMenu *pMenu)
{
    if(CExpressPub::isNullPtr(pMenu))
    {
        return;
    }
    QAction *pActionDeleteItem    = CUIPub::createAction("删除节点");
    QObject::connect(pActionDeleteItem, SIGNAL(triggered()), this, SLOT(proc_actionDeleteItem()));
    pMenu->addAction(pActionDeleteItem);

}



void SuperTest::proc_actionOpenConfigFile()
{
    if(0 == CStringPub::strSimLen(file_cur_item_load))
    {
        return;
    }
    CUIPub::explorerPathExt(file_cur_item_load);
}

void SuperTest::proc_actionOpenConfigDir()
{
    if(0 == CStringPub::strSimLen(file_cur_item_load))
    {
        return;
    }
    QString dirPath = CFilePub::parentDir(file_cur_item_load);

    debugApp() << "file_cur_item_load:" << file_cur_item_load;
    debugApp() << "dirPath:" << dirPath;

    CUIPub::explorerPathExt(dirPath);
}

void SuperTest::proc_actionSaveFile()
{
    if(0 == CStringPub::strSimLen(file_cur_item_load))
    {
        return;
    }
    CFilePub::writeFileWOnly(file_cur_item_load, CUIPub::getTextEdit(ui->textEdit_test_content));
    CUIPub::showStatusBarTimerBoth(ui->statusbar, QString("保存文件:%1").arg(file_cur_item_load));
}

void SuperTest::proc_actionReloadFile()
{
    if(0 == CStringPub::strSimLen(file_cur_item_load))
    {
        return;
    }
    CUIPub::setTextEdit(ui->textEdit_test_content, CFilePub::readFileAll(file_cur_item_load));
    CUIPub::setTextEdit(ui->textEdit_test_result, CFilePub::readFileAll(file_cur_item_load + CSignPub::signDot() + file_result_log));
    CUIPub::showStatusBarTimerBoth(ui->statusbar, QString("重新加载:%1").arg(file_cur_item_load));
}



void SuperTest::closeEvent(QCloseEvent *event)
{
    debugApp() << "closeEvent";
    write_HistorySetting();
    event->accept();
}

void SuperTest::read_Setting()
{
    read_HistorySetting();
}

void SuperTest::proc_HistorySetting(int type)
{
    quint8 ucType = type;
    m_pSettings = CUIPub::read_HistorySettings(m_organization,m_application);
    CUIPub::procString(m_pSettings, BINDSTRWORDS(openFilePathRecent), ucType);
    CUIPub::procString(m_pSettings, BINDSTRWORDS(dir_cur_loaded), ucType);
    CUIPub::setLabelText(ui->label_load_path, dir_cur_loaded);
    CUIPub::setLabelText(ui->label_load_path, dir_cur_loaded);
    CUIPub::procCheckBox(m_pSettings, ui->checkBox, ucType);
    CUIPub::procCheckBox(m_pSettings, ui->checkBox_fullPath, ucType);
}

void SuperTest::read_HistorySetting()
{
    proc_HistorySetting(CUIPub::TYPE_READ);
}


void SuperTest::write_HistorySetting()
{
    proc_HistorySetting(CUIPub::TYPE_WRITE);
}

void SuperTest::on_action_new_ut_instance_triggered()
{
    CDialogNewUt *pDiaglog = new CDialogNewUt();

    if(CStringPub::strSimLen(dir_cur_loaded))
    {
        QString newPath = dir_cur_loaded + getUtNamePrefix() + CSignPub::signDot();
        pDiaglog->setPath(newPath);
    }

    if(QDialog::Rejected == pDiaglog->exec())
    {
        return;
    }


    //支持同时创建多个文件用例
    debugApp() << pDiaglog->getPath();

    QStringList strPathList =CStringPub::stringSplitbyNewLineFilterEmpty(pDiaglog->getPath());
    if(1 == strPathList.size())
    {
        CFilePub::createFileEmptyNoExist(pDiaglog->getPath());
    }
    else
    {
        QString prefix = strPathList.at(0);
        quint16 dsLp = 0;
        foreach (QString item, strPathList) {
            if(0 == dsLp)
            {
                dsLp++;
                continue;
            }
            QString filelast = prefix + item;
            CFilePub::createFileEmptyNoExist(filelast);
        }
    }


    on_pushButton_reload_dir_clicked();
}

QString SuperTest::getUtNamePrefix()
{
    return file_content_txt;
}



void SuperTest::on_actionSave_triggered()
{
    proc_actionSaveFile();
}

void SuperTest::on_lineEdit_returnPressed()
{
    on_pushButton_reload_dir_clicked();
}

void SuperTest::on_checkBox_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    on_pushButton_reload_dir_clicked();
}

void SuperTest::on_pushButton_save_clicked()
{
    proc_actionSaveFile();
}

void SuperTest::on_pushButton_reload_clicked()
{
    proc_actionReloadFile();
}

void SuperTest::proc_checkBox_fullPath_stateChaned(int)
{
    on_pushButton_reload_dir_clicked();
}

//菜单右键显示
void SuperTest::proc_customContextMenuRequested(QPoint)
{
    QCursor cur=this->cursor();

    if(pRightMouseListWidget)
    {
        pRightMouseListWidget->exec(cur.pos()); //关联到光标
    }
}


void SuperTest::proc_menu_RightMouseListWidget(QAction *pAction)
{
    debugApp() << CUIPub::getQActionText(pAction);
    QListWidgetItem * item = CUIPub::getListWidgetCurrentItem(ui->listWidget_load_dir);
    CHECK_NULLPOINTER_RETURN(item);

    QList<QListWidgetItem*> pListSelct = CUIPub::getListWidgetSelectedItems(ui->listWidget_load_dir);
    debugApp() << "select list size:" << pListSelct.size();
    if(0 == pListSelct.size())
    {
        int ch = QMessageBox::warning(NULL, "Warning",
                                      QString("Are you sure to delete file 【%1】?\n").arg(item->text()),
                                      QMessageBox::Yes | QMessageBox::No,
                                      QMessageBox::No);

        if ( ch != QMessageBox::Yes )
            return;
        //删除文件
        CFilePub::deleteFile(proc_itemWholePathOnCheckBox(item->text()));

        CUIPub::getListWidgetTakeItem(ui->listWidget_load_dir, item);
        delete item;
        return;
    }

    //删除文件列表
    QString showText = CStringPub::emptyString();
    showText += CSignPub::signEnter();
    foreach (QListWidgetItem *pItem, pListSelct) {
        showText += pItem->text() + CSignPub::signEnter();
    }

    int ch = QMessageBox::warning(NULL, "Warning",
                                  QString("Are you sure to delete these files 【%1】?\n").arg(showText),
                                  QMessageBox::Yes | QMessageBox::No,
                                  QMessageBox::No);

    if ( ch != QMessageBox::Yes )
        return;
    foreach (QListWidgetItem *pItem, pListSelct) {
        CFilePub::deleteFile(proc_itemWholePathOnCheckBox(pItem->text()));

        CUIPub::getListWidgetTakeItem(ui->listWidget_load_dir, item);
        delete pItem;
    }



}

