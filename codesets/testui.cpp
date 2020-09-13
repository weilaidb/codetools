#include "testui.h"
#include "ui_testui.h"
#include "debugApp.h"


testui::testui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::testui)
{
    ui->setupUi(this);

    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(proc_pushButton_clicked()));
}

testui::~testui()
{
    delete ui;
}

void testui::on_pushButton_clicked()
{
    debugApp() << "on push cliedn:";
}

void testui::proc_pushButton_clicked()
{
    debugApp() << "on push cliedn:123";
}
