#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QCloseEvent>
#include "cnetthreadpub.h"
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
    void closeEvent(QCloseEvent *event);

private:
    void showVersion();
    void initDialog();
    void initActionSets();
    void initVars();
    void initUiOther();
    void readSetting();
    void pubHistorySetting(int type);
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
    void addMenuRecent(QStringList recent, QMenu *pMenu);
    void addMenuCodeFormatRecent();
    void addMenuDocumentOpenRecent();
    void addMenuDocumentSearchRecent();
    void updateRecent(QStringList &list, QMenu *pMenu);
    void updateRecentAppend(QStringList &list, QString name, QMenu *pMenu);
    //获取对话框输入的文字
    quint8 getDialogFindText(QString &findtext);
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

    enum{
        OPENTYPE_YES_FILE,
        OPENTYPE_YES_DIR,
        OPENTYPE_NO_FILE,
        OPENTYPE_NO_DIR,
    };

    enum{
        ACTIONTYPE_OPEN,
        ACTIONTYPE_SEARCH,
        ACTIONTYPE_SEARCH_ALLFILES,
    };


private:
    Ui::MainWindow *ui;

    //模态对话框，动态创建，用过后删除
    Ui::CDialogAskText *uiDialog;
    QDialog *pDialog;

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
    QStringList recentfiles_codeformat;
    QStringList recentfiles_document;

    QString m_organization;
    QString m_application;

    QSettings *m_pSettings;

    QString openWordFilePathRecent;


    //thread
    CNetThreadPub *m_thread_server;
    CNetThreadPub *m_thread_client;
    CNetThreadPub *m_thread_publish;
    CNetThreadPub *m_thread_subscribe;
private slots:
    void proc_action_codeFormat_File_trigger();
    void proc_action_codeFormat_Directory_trigger();
    void proc_action_codeFormat_Pub_trigger(int openType, QStringList autolist);
    void proc_menu_codeFormat_Recent_trigger(QAction *action);
    void proc_action_codeFormat_Edit_Config_trigger();
    void proc_action_codeFormat_Save_Config_trigger();
    void proc_action_codeFormat_Del_Config_trigger();
    void proc_action_about_trigger();

    //mysql
    void proc_action_mysql_testdatabase_trigger();
    //office
    QStringList proc_action_office_auto_pub_trigger(QString filter, QStringList filterlist, QString &openRecent, QStringList &recentfiles, quint8 openDiagFlag, QStringList openfilelist);
    void proc_action_office_open_pub_trigger(QString filter, QStringList filterlist, QString &openRecent, quint8 openDiagFlag, QStringList openfilelist);
    void proc_action_office_action_pub_trigger(quint8 ucActionType, QStringList list,QString findtext);
    void proc_action_office_open_trigger();
    void proc_action_office_search_file_pub_trigger(QString filter, QStringList filterlist, QString openRecent, quint8 openDiagFlag, QStringList openfilelist);
    void proc_action_office_search_dir_pub_trigger(QString filter, QStringList filterlist, QString openRecent, quint8 openDiagFlag, QStringList openfilelist);
    void proc_action_office_search_file_trigger();
    void proc_action_office_search_dir_trigger();
    void proc_menu_document_open_recent_trigger(QAction *action);
    void proc_menu_document_search_recent_trigger(QAction *action);

    //dialog ask text
    void clearDialogText();
    void pasteDialogText();

    //network
    void proc_action_net_server_trigger();
    void proc_action_net_client_trigger();
    void proc_action_net_publish_trigger();
    void proc_action_net_subscribe_trigger();
    void create_thread_network(CNetThreadPub *&pTthread, handler_retint_nopara hander);
    void proc_threadmessage_trigger(const QString &info);
    void proc_threadprogress_trigger(int progress);
    void proc_threadfinished_trigger();
};
#endif // MAINWINDOW_H
