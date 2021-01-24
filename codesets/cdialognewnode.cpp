#include "cdialognewnode.h"
#include "ui_cdialognewnode.h"

#include <cuipub.h>
#include <cuipub.h>

CDialogNewNode::CDialogNewNode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDialogNewNode)
{
    ui->setupUi(this);
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

