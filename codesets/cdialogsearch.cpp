#include "cdialogsearch.h"
#include "ui_cdialogsearch.h"
#include "cuipub.h"
#include "debugApp.h"
#include "cexpresspub.h"
#include "cstringpub.h"
#include <QCloseEvent>
#include <QSettings>


CDialogSearch::CDialogSearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDialogSearch)
{
    ui->setupUi(this);


    init_Vars();
    read_Setting();
    init_UiSets();
}

CDialogSearch::~CDialogSearch()
{
    delete ui;
}

QString CDialogSearch::getKey()
{
    //getKey之前保存下历史数据
    QString curText = CUIPub::getComBox(ui->comboBox);
    CStringPub::addStringUnique(m_searchList, curText);
    write_HistorySetting();
    return curText;
}

Qt::CaseSensitivity CDialogSearch::getCaseSentived()
{
    Qt::CaseSensitivity cs = ui->checkBox_caseSensitive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    return cs;
}

bool CDialogSearch::getFileContented()
{
    return CUIPub::isCheckedQCheckBox(ui->checkBox_findFileContent);
}

void CDialogSearch::init_Vars()
{
    CStringPub::clearString(m_key);
    CStringPub::setString(m_organization, "weilaidb");
    CStringPub::setString(m_application, "CDialogSearch");
}

void CDialogSearch::init_UiSets()
{
    CUIPub::setComBoxFocus(ui->comboBox);
    CUIPub::clearComBoxFocus(ui->comboBox);

    m_pListWidget = new QListWidget (this) ;
    CUIPub::clearListWidget(m_pListWidget);
    foreach (QString item, m_searchList) {
        CUIPub::addListWidgetItem(m_pListWidget, item);
    }
    CUIPub::setComBoxModel(ui->comboBox, m_pListWidget->model());
    CUIPub::setComBoxView(ui->comboBox, m_pListWidget);

    //comboBox的当前值被前面的覆盖了，需要重新处理
    CUIPub::procComboBox(m_pSettings, ui->comboBox, CUIPub::TYPE_READ);

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
    CUIPub::procComboBox(m_pSettings, ui->comboBox, ucType);
    CUIPub::procStringList(m_pSettings, BINDSTRWORDS(m_searchList), ucType);
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
    ////debugApp() << "closeEvent";
    write_HistorySetting();
    event->accept();
}

