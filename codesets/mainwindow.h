#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include "version.h"
#include "filepub.h"
#include "basetypepub.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
namespace Ui { class CDialogAskText; }
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
    void initUiOther();
    void readSetting();
    void readHistorySetting();
    void writeHistorySetting();
    WORD32 getAstyleFmt(QStringList filelist);
    void getAstyleConfig();
    void getAstyleOrgConfig();
    void freeArgv();
    void procAstyleInstance(QStringList filelist);
    void showStatus(QString msg);
    void showStatusTimer(QString msg);
    void showTextBrower(QString msg);
    void showTextBrowerAppend(QString msg);
    void getNameFilter();
    void addMenuCodeFormatRecent();
    QString getWordFindText();
    void setLeftTextEdit(QString str);
    void clearLeftTextEdit();
    void setRightTextEdit(QString str);
    void clearRightTextEdit();
public:
    enum{
        TYPE_FILE,
        TYPE_FILES,
        TYPE_DIR,
        TYPE_AUTO,
        TYPE_FILES_NOUI,
        TYPE_DIR_NOUI,
    };

private:
    Ui::MainWindow *ui;

private:
    QString openFilePathRecent;
    QString openDirPathRecent;
    char **m_argvp;
    WORD32 dwArgc;
    QStringList listAstyleArgv;
    QString logAstyleName;
    QString cfgAstyleName;
    QString cfgAstyleNameOrg;

    QStringList nameFilters;
    QStringList recentfiles;

    QString m_organization;
    QString m_application;

    QSettings *m_pSettings;

    QString openWordFilePathRecent;
private slots:
    void proc_action_codeFormat_File_trigger();
    void proc_action_codeFormat_Directory_trigger();
    void proc_action_codeFormat_Pub_trigger(int openType, QStringList autolist);
    void proc_action_codeFormat_Auto_trigger(QAction *action);
    void proc_action_codeFormat_Edit_Config_trigger();
    void proc_action_codeFormat_Save_Config_trigger();
    void proc_action_codeFormat_Del_Config_trigger();
    void proc_action_about_trigger();

    //mysql
    void proc_action_mysql_testdatabase_trigger();
    //office
    void proc_action_office_open_trigger();
    void proc_action_office_search_trigger();


};
#endif // MAINWINDOW_H
