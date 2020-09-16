#include "cdialognewut.h"
#include "ui_cdialognewut.h"
#include <QTextCursor>
#include <cuipub.h>

CDialogNewUt::CDialogNewUt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CDialogNewUt)
{
    ui->setupUi(this);
}

CDialogNewUt::~CDialogNewUt()
{
    delete ui;
}

void CDialogNewUt::setPath(QString &path)
{
    CUIPub::setTextEdit(ui->textEdit, path);
    CUIPub::setTextEditFocus(ui->textEdit);
    CUIPub::setTextEditmoveCursorEnd(ui->textEdit);
}

