#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "astyle_main.h"
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showVersion();
    actionSets();



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showVersion()
{
    ui->statusbar->showMessage(APP_VERSION);
}

void MainWindow::actionSets()
{
    QObject::connect(ui->action_codeFormat, SIGNAL(triggered()), this, SLOT(proc_action_codeFormat_trigger()));
}


void MainWindow::proc_action_codeFormat_trigger()
{
    qDebug() << "on_action_codeFormat_trigger";
}




