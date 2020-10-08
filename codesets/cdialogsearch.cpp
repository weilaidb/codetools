#include "cdialogsearch.h"
#include "ui_cdialogsearch.h"
#include "cuipub.h"
#include "debugApp.h"
#include <QCloseEvent>
#include <QSettings>


CDialogSearch::CDialogSearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDialogSearch)
{
    ui->setupUi(this);


    init_Vars();
    read_Setting();
}

CDialogSearch::~CDialogSearch()
{
    delete ui;
}

QString CDialogSearch::getKey()
{
    //getKey之前保存下历史数据
    write_HistorySetting();
    return CUIPub::getLineEdit(ui->lineEdit);
}

Qt::CaseSensitivity CDialogSearch::getCaseSentived()
{
    Qt::CaseSensitivity cs = ui->checkBox_caseSensitive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    return cs;
}

bool CDialogSearch::getFileContented()
{
    return ui->checkBox_findFileContent->isChecked();
}

void CDialogSearch::init_Vars()
{
    m_key.clear();

    m_organization = "weilaidb";
    m_application = "CDialogSearch";

}

void CDialogSearch::read_Setting()
{
    read_HistorySetting();
}

void CDialogSearch::proc_HistorySetting(int type)
{
    quint8 ucType = type;
    m_pSettings = CUIPub::read_HistorySettings(m_organization,m_application);
    CUIPub::procCheckBox(m_pSettings, ui->checkBox_caseSensitive, ucType);
    CUIPub::procCheckBox(m_pSettings, ui->checkBox_findFileContent, ucType);
}

void CDialogSearch::read_HistorySetting()
{
    proc_HistorySetting(CUIPub::TYPE_READ);
}


void CDialogSearch::write_HistorySetting()
{
    proc_HistorySetting(CUIPub::TYPE_WRITE);
}


void CDialogSearch::closeEvent(QCloseEvent *event)
{
    debugApp() << "closeEvent";
    write_HistorySetting();
    event->accept();
}


