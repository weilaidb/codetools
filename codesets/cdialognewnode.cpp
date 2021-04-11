#include "cdialognewnode.h"
#include "ui_cdialognewnode.h"
#include "debugApp.h"

#include <QCloseEvent>
#include <cstringpub.h>
#include <cuipub.h>
#include <cuipub.h>

CDialogNewNode::CDialogNewNode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDialogNewNode)
{
    ui->setupUi(this);

    init_Vars();
    read_Setting();
    init_UiSets();

}

CDialogNewNode::~CDialogNewNode()
{
    delete ui;
}

void CDialogNewNode::setName(QString &name)
{
    CUIPub::setLineEdit(ui->lineEdit, name);
    CUIPub::setLineEditFocus(ui->lineEdit);
}

QString CDialogNewNode::getName()
{
    return CUIPub::getLineEdit(ui->lineEdit);
}

QString CDialogNewNode::getNameFromCopy()
{
    return CUIPub::getLineEdit(ui->lineEdit_fromCopy);
}

bool CDialogNewNode::isChkedBoxfromCopy()
{
    return CUIPub::isCheckedQCheckBox(ui->checkBox);
}

int CDialogNewNode::getType ()
{
    return m_type ;
}

int CDialogNewNode::setType (int _val)
{
    m_type  = _val;
    CUIPub::setLabelText(ui->label, CUIPub::getLabelEdit(ui->label) + QString("[%1]").arg(getTypeText()));
    return m_type ;
}

QString CDialogNewNode::getTypeText()
{
    QString result("");

    switch (m_type) {
    case NEWUSERMODE:
        result = "用户模式";
        break;
    case NEWSTANDMODE:
        result = "标准模式";
        break;
    default:
        result = "非法模式";
        break;
    }
    return result;
}


void CDialogNewNode::closeEvent(QCloseEvent *event)
{
    ////debugApp() << "closeEvent";
    write_HistorySetting();
    event->accept();
}

void CDialogNewNode::read_HistorySetting()
{
    proc_HistorySetting(CUIPub::TYPE_READ);
}


void CDialogNewNode::write_HistorySetting()
{
    proc_HistorySetting(CUIPub::TYPE_WRITE);
}

void CDialogNewNode::read_Setting()
{
    read_HistorySetting();
}

void CDialogNewNode::proc_HistorySetting(int type)
{
    quint8 ucType = type;
    m_pSettings = CUIPub::read_HistorySettings(m_organization,m_application);
    CUIPub::procLineEdit(m_pSettings, ui->lineEdit, ucType);
    CUIPub::procLineEdit(m_pSettings, ui->lineEdit_fromCopy, ucType);
    CUIPub::procCheckBox(m_pSettings, ui->checkBox,ucType);
    debugApp() << "ucType:" << ucType;
}

void CDialogNewNode::init_Vars()
{
    CStringPub::clearString(m_name);
    CStringPub::setString(m_organization, "weilaidb");
    CStringPub::setString(m_application, "CDialogNewNode");
}


void CDialogNewNode::init_UiSets()
{

}
