#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QCloseEvent>
#include <QTextEdit>
#include <QTimer>
#include "cnetthreadpub.h"
#include "version.h"
#include "basedefinepub.h"
#include "basetypepub.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
namespace Ui { class CDialogAskText; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(char *appexe, QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);

private:
    void showVersion();
    void initDialog();
    void initActionSets();
    void initCheckBoxSets();
    void initVars();
    void initUiSets();
    void readSetting();
    void procHistorySetting(int type);
    void readHistorySetting();
    void writeHistorySetting();
    WORD32 getAstyleFmt(QStringList filelist);
    void getAstyleConfig();
    void getAstyleOrgConfig();
    void freeArgv();
    void procAstyleInstance(QStringList filelist);
    void showStatus(QString msg);
    void showStatusTimer(QString msg);
    void showStatusTimerWindowTitle(QString msg);
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
    void clrLeftTextEdit();
    void setRightTextEdit(QString str);
    void clrRightTextEdit();
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


    /* 右键菜单 */
    QMenu *pRightMouse;
    //custom menu
    QMenu *pMenuCustom;
    QString m_FileNameMenu;
    /**
      ** 模式：
      ** 单行 多处理
      ** 单行 单处理
      ** 多行 单处理
      ** 多行 多处理
      **/
    QString m_FileMode_SingleL_ExecMulti;
    QString m_FileMode_AllL_ExecMulti;
    //常用列表 configfile, 显示的最大数量
    QStringList m_listfrequse;
    int m_iListFreqUseCnt;
    QString m_ListFreqUseFile;
    //注意事项
    QString m_AttentionFile;
    //常用文件打开列表
    QStringList m_listNormalUse;
    int m_iListNormalUseCnt;
    QString m_ListOpenFile;

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

    //Edit File
    QString m_EditConfig;

    //text edit
    QTimer *pCheckLeftTimer;
    int iTimeout;
    //text edit
    QTimer *pClipBoardTimer;
    int iClipBoardTimeout;

    //程序名
    QString m_apppath;
private slots:
    void proc_action_codeFormat_File();
    void proc_action_codeFormat_Directory();
    void proc_action_codeFormat_Pub(int openType, QStringList autolist);
    void proc_menu_codeFormat_Recent(QAction *action);
    void proc_action_codeFormat_Edit_Config();
    void proc_action_codeFormat_Save_Config();
    void proc_action_codeFormat_Del_Config();
    void proc_action_about();
    void proc_action_attention();

    //mysql
    void proc_action_mysql_testdatabase();
    //office
    QStringList proc_action_office_auto_pub(QString filter, QStringList filterlist, QString &openRecent, QStringList &recentfiles, quint8 openDiagFlag, QStringList openfilelist);
    void proc_action_office_open_pub(QString filter, QStringList filterlist, QString &openRecent, quint8 openDiagFlag, QStringList openfilelist);
    void proc_action_office_action_pub(quint8 ucActionType, QStringList list,QString findtext);
    void proc_action_office_open();
    void proc_action_office_search_file_pub(QString filter, QStringList filterlist, QString openRecent, quint8 openDiagFlag, QStringList openfilelist);
    void proc_action_office_search_dir_pub(QString filter, QStringList filterlist, QString openRecent, quint8 openDiagFlag, QStringList openfilelist);
    void proc_action_office_search_file();
    void proc_action_office_search_dir();
    void proc_menu_document_open_recent(QAction *action);
    void proc_menu_document_search_recent(QAction *action);

    //dialog ask text
    void clearDialogText();
    void pasteDialogText();

    //network
    void proc_action_net_server();
    void proc_action_net_client();
    void proc_action_net_publish();
    void proc_action_net_subscribe();
    void create_thread_network(CNetThreadPub *&pTthread, handler_retint_nopara hander, qint8 checkrunning);
    void proc_threadmessage(const QString &info);
    void proc_threadprogress(int progress);
    void proc_threadfinished();

    //text edit
    void proc_textEdit_textChanged();
    void proc_clipBoard_textChanged();


    //generate 添加右键菜单
    void proc_action_gen_pub(QString configfilename, int type);
    void proc_action_gen_custom_action(QAction *pAction);
    void proc_action_openfilelist(QAction *pAction);
    void proc_action_EditCfgFile(bool checked);
    void proc_action_DeleteCfgFile(bool checked);
    void proc_action_EditCfgFileMutex();
    void proc_action_edit_pub(QString configfilename, int type);
    void proc_action_editinginfo(QString configfilename, int type);
    void proc_action_deleteinfo(QString configfilename, int type);
    void proc_action_TryAgain();
    void proc_frequse_config(QString configfilename);


    void slot_generate_menu_left(QPoint pos);
    void slot_generate_menu_right(QPoint pos);
    void slot_generate_menu_leftbottom(QPoint pos);
    QMenu *slot_fromfile_menu(QString filename);
    QMenu *slot_frequse_menu();
    QMenu *slot_openfilelist_menu();
    void nodes_menu_left(QMenu *pMenu);
    void nodes_menu_right(QMenu *pMenu);
    void nodes_menu_leftbottom(QMenu *pMenu);
    void proc_actionClearLeft();
    void proc_actionClearRight();
    void proc_actionPasteLeft();
    void proc_actionSelectCopy();
    void proc_actionSelectAllCopyLeft();
    void proc_actionPasteRight();
    void proc_actionSelectAllCopyRight();
    void proc_actionClearEmpty();
    void proc_actionOpenConfigDir();
    void proc_actionOpenConfigFile();
    void proc_actionOpenCfgMenu();
    void proc_actionEditCfgFile();
    void proc_actionSaveCfgFile();

    //read file
    void read_CfgFile2List(QStringList &list, QString &filenamevar, QString filename);
    void read_FreqUseFile();
};
#endif // MAINWINDOW_H
