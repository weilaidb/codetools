#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "version.h"
#include "filepub.h"
#include "basepub.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void showVersion();
    void actionSets();
    void initVars();
    WORD32 getAstyleFmt(QStringList filelist);
    void getAstyleConfig();
    void freeArgv();
    void procAstyleInstance(QStringList filelist);
    void showStatus(QString msg);
    void showTextBrower(QString msg);
    void showTextBrowerAppend(QString msg);
    void getNameFilter();
    void addMenuCodeFormatRecent();

public:
    enum{
        TYPE_FILE,
        TYPE_FILES,
        TYPE_DIR,
        TYPE_AUTO,
    };

private:
    Ui::MainWindow *ui;

private:
    QString openDirPathRecent;
    char **m_argvp;
    WORD32 dwArgc;
    QStringList listAstyleArgv;
    QString logAstyleName;
    QString cfgAstyleName;
    QString cfgAstyleNameOrg;

    QStringList nameFilters;
    QStringList recentfiles;

private slots:
    void proc_action_codeFormat_File_trigger();
    void proc_action_codeFormat_Directory_trigger();
    void proc_action_codeFormat_Pub_trigger(int openType, QStringList autolist);
    void proc_action_codeFormat_Auto_trigger(QAction *action);
    void proc_action_codeFormat_Edit_Config_trigger();
    void proc_action_codeFormat_Save_Config_trigger();
    void proc_action_codeFormat_Del_Config_trigger();
    void proc_action_about_trigger();
};
#endif // MAINWINDOW_H
