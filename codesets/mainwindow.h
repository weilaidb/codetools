#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "version.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showVersion();
    void actionSets();

private:
    Ui::MainWindow *ui;


private slots:
    void proc_action_codeFormat_trigger();
};
#endif // MAINWINDOW_H
