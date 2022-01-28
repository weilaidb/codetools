#include "test1.h"
#include "ui_test1.h"

test1::test1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::test1)
{
    ui->setupUi(this);
}

test1::~test1()
{
    delete ui;
}
