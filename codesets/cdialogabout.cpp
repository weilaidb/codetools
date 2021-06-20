#include "cdialogabout.h"
#include "ui_cdialogabout.h"
#include "cuipub.h"

CDialogAbout::CDialogAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDialogAbout)
{
    ui->setupUi(this);
}

CDialogAbout::~CDialogAbout()
{
    delete ui;
}

void CDialogAbout::setText(QString text)
{
    CUIPub::setTextEdit(ui->textEdit, text);
}
