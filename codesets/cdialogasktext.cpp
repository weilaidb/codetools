#include "cdialogasktext.h"
#include "ui_cdialogasktext.h"

CDialogAskText::CDialogAskText(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDialogAskText)
{
    ui->setupUi(this);
}

CDialogAskText::~CDialogAskText()
{
    delete ui;
}
