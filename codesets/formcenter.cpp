#include "formcenter.h"
#include "ui_formcenter.h"

FormCenter::FormCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCenter)
{
    ui->setupUi(this);
}

FormCenter::~FormCenter()
{
    delete ui;
}
