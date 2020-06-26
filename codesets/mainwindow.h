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
    void freeArgv();
    void procAstyleInstance(QStringList filelist);
    void showStatus(QString msg);

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
    char m_argv[ARGVROWS][FILENAMEMAX];
    char **m_argvp;
    WORD32 dwArgc;
    QStringList listAstyleArgv;
    QString logAstyleName;

private slots:
    void proc_action_codeFormat_File_trigger();
    void proc_action_codeFormat_Directory_trigger();
    void proc_action_codeFormat_Pub_trigger(int openType);
};
#endif // MAINWINDOW_H
