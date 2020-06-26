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
    void initVars();


public:
    enum{
        TYPE_FILE,
        TYPE_FILES,
        TYPE_DIR,
    };

private:
    Ui::MainWindow *ui;

private:
    QString openDirPathRecent;

private slots:
    void proc_action_codeFormat_File_trigger();
    void proc_action_codeFormat_Directory_trigger();
    void proc_action_codeFormat_Pub_trigger(int openType);
};
#endif // MAINWINDOW_H
