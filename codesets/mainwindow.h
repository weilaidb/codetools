#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QCloseEvent>
#include <QTextEdit>
#include <QTimer>
#include <QMutex>
#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QSpinBox>
#include <QFontComboBox>
#include <QHostInfo>
#include "cnetthreadpub.h"
#include "version.h"
#include "basedefinepub.h"
#include "basetypepub.h"
#include "supertest.h"
#include "cdialognewnode.h"
#include "cdialogsearch.h"
#include "cregexppub.h"
#include "cthreadextpub.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
namespace Ui { class CDialogAskText; }
namespace Ui { class SuperTest; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

    Q_CLASSINFO("author", "WeiLai")
    Q_CLASSINFO("company","WeiLaiDB")
    Q_CLASSINFO("version","1.0")

public:
    MainWindow(char *appexe, QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);
    bool eventFilter(QObject *target, QEvent *event);

private:
    void show_Version();
    void init_Dialog();
    void init_ActionSets();
    void init_CheckBoxSets();
    void init_Vars();
    void init_UiSets();
    void init_PushButtonSets();
    void InstallEventFilterSets();
    void read_Setting();
    void proc_HistorySetting(int type);
    void read_HistorySetting();
    void write_HistorySetting();
    WORD32 get_AstyleFmt(QStringList filelist);
    void get_AstyleConfig();
    void get_AstyleOrgConfig();
    void free_Argv();
    void proc_AstyleInstance(QStringList filelist);
    void show_Status(QString msg);
    void show_StatusOnly(QString msg);
    void show_StatusTimer(QString msg);
    void show_StatusTimerWindowTitle(QString msg);
    void show_TextBrower(QString msg);
    void show_TextBrowerAppend(QString msg);
    void get_NameFilter();
    void add_MenuRecent(QStringList recent, QMenu *pMenu);
    void add_MenuCodeFormatRecent();
    void add_MenuDocumentOpenRecent();
    void add_MenuDocumentSearchRecent();
    void update_Recent(QStringList &list, QMenu *pMenu);
    void update_RecentAppend(QStringList &list, QString name, QMenu *pMenu);
    //获取对话框输入的文字
    quint8 get_DialogFindText(QString &findtext);
    void set_LeftTextEdit(QString str);
    void clear_LeftTextEdit();
    void set_RightTextEdit(QString str);
    void clear_RightTextEdit();

    //spliter
    void procRightSplitter();

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

    //test ui
    Ui::SuperTest *uiTest;
    SuperTest *pMulWinTest;

    /* 右键菜单 */
    QMenu *pRightMouse_L;
    QMenu *pRightMouse_R;
    QList<QAction *> m_lstRightMouse;
    //custom menu
    QMenu *pMenuCustom;
    QString m_FileNameMenu_stand;
    QString m_FileNameMenu_user;
    QString m_FileNameMenu;
    /**
      ** 模式：
      ** 单行 多处理
      ** 单行 单处理
      ** 多行 单处理
      ** 多行 多处理
      **/
    QString m_FileMode_AllL_ExecMulti;
    QString m_FileMode_SingleL_ExecMulti;
    QString m_FileMode_SingleL_ExecSingle;//一行执行对应的行，执行与模式数量不对齐的话，中间项参考前面项
    //常用列表 configfile, 显示的最大数量
    QStringList m_ListFreqUse;
    quint32 m_ActualFreqUseCnt;
    QString m_FileNameMenuListFreqUse;
    //注意事项
    QString m_AttentionFile;
    //常用文件打开列表
    QStringList m_listNormalUse;
    QString m_ListOpenFile; //配置文件文件列表

    QString m_FileNameContentMax; //内容最大数量(BYTES)
    QString m_FileNameFreqUseMax; //常用左侧内容项最大个数
    QString m_FileNameRecentOpen;//最近打开文件列表要读取的文件名
    QStringList m_ListRecentOpen;//最近打开文件列表

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

    QTimer *pTimerBackgroundUpdate;
    int iTimeoutBackgroundUpdate;

    //程序名
    QString m_apppath;

    //QMutexLocker
//    QMutexLocker update_locker;
    QMutex m_lock;

    //pop menu
    QMenu *pPopMenu;

    QString m_ListNetSearchFile; //搜索数据文件名
    //net search Text
    QStringList m_NetSearchList;

    //
    QLabel *fLabCurFile;//状态栏显示当前文件的Label
    QProgressBar *progressBar1;//状态栏上的进度条
    QSpinBox *spinFontSize;//字体大小spinBox
    QFontComboBox *comboFont;//字体名称combBox

private:
    void iniUiOther();


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
    void proc_action_attentionnew();

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
    void proc_TimerBackgroundUpdate();


    //generate 添加右键菜单
    void proc_action_gen_pub(QString configfilename, int type);
    void proc_action_gen_custom_action(QAction *pAction);
    void proc_action_netsearch_custom_action(QAction *pAction);
    void proc_action_openfilelist(QAction *pAction);
    void proc_action_EditCfgFile(bool checked);
    void proc_action_DeleteCfgFile(bool checked);
    void proc_action_EditCfgFileMutex();
    void proc_action_edit_pub(QString configfilename, int type);
    bool proc_action_edit_convertline_pub(QString configfilename);
    void proc_action_editinginfo(QString configfilename, int type);
    void proc_action_deleteinfo(QString configfilename, int type);
    void proc_action_TryAgain();
    void proc_action_TryAgain_Thread();
    void proc_frequse_config(QString configfilename);
    void proc_frequse_findkey(QString findKey);
    void proc_action_background_update(bool bFlag);
    void proc_action_update(bool bFlag);
    void proc_action_scan_test_dir(bool bFlag);

    void proc_actionascii_to_string();
    void proc_actionascii_to_string_10();
    void proc_actionascii_to_string_pub(int hexflag);
    void proc_actionstring_to_ascii();
    void proc_actionstring_to_ascii_10();
    void proc_actionstring_to_asciipub(int hexflag);

    void proc_action_newstandnode();
    void proc_action_newusernode();
    void proc_newnode_more(CDialogNewNode *pDiaglog);
    bool proc_newnode_check(CDialogNewNode *pDiaglog);
    bool proc_configexist_check(QString newNodeName);
    void proc_newnode_copy(CDialogNewNode *pDiaglog);
    void proc_newnode_rename(QString preNodeName, QString toNamedNodeName);
    void proc_newnode_rename_update_menulist(QString preNodeName, QString toNamedNodeName);
    void update_menulist_byitem(QString m_FileName, QString preNodeName, QString newNodeName);
    //tools
    void proc_action_delspace();
    void proc_action_dellastspacesort();
    void proc_action_del_BCompare_xml();

    void update_generate_menu_left();
    void proc_generate_menu_left(QPoint pos);
    void proc_generate_menu_right(QPoint pos);
    void proc_generate_menu_cfgAfter(QPoint pos);
    void proc_generate_menu_leftbottom(QPoint pos);
    QMenu *proc_fromfile_menu(QString filename);
    QMenu *proc_frequse_menu();
    QMenu *proc_netsearch_menu();
    QMenu *proc_openfilelist_menu();
    void nodes_menu_left(QMenu *pMenu);
    void nodes_menu_left_little(QMenu *pMenu);
    void nodes_menu_right(QMenu *pMenu);
    void nodes_menu_cfgAfter(QMenu *pMenu);
    void nodes_menu_leftbottom(QMenu *pMenu);
    void nodes_menu_rightbottom(QMenu *pMenu);
    void nodes_menu_find(QMenu *pMenu);
    void nodes_menu_other(QMenu *pMenu);
    void nodes_menu_forwardright(QMenu *pMenu);
    void proc_actionClearLeft();
    void proc_actionClearRight();
    void proc_actionPasteLeft();
    void proc_actionSelectCopy();
    void proc_actionSelectAllCopyLeft();
    void proc_actionPasteRight();
    void proc_actionSelectAllCopyRight();
    void proc_actionClearEmpty();
    void proc_actionCovertOneLine();
    void proc_actionCovertMulLine();
    void proc_actionOpenConfigBaseDir();
    void proc_actionOpenConfigFile();
    void proc_actionOpenConfigDir();
    void proc_actionOpenConfigFileR();
    void proc_actionOpenConfigDirR();
    void proc_actionOpenCfgMenu();
    void proc_actionReload();
    void proc_LinePacket();
    void proc_ActionForward();
    void proc_ActionForwardRight();
    void proc_actionEditCfgFile();
    void proc_actionSaveCfgFile();

    //read file
    void read_CfgFile2List(QStringList &list, QString &filenamevar, QString filename);
    void read_FreqUseFile();



    //pushbutton
    void proc_pushButton_left_clear  ()  ;
    void proc_pushButton_left_paste  ()  ;
    void proc_pushButton_tryagain    ()  ;
    void proc_pushButton_right_clear ()  ;
    void proc_pushButton_right_copy  ()  ;
    void hide_PushButtonSets();

    void on_pushButton_clearTryAgainExt_clicked();
    void on_action_search_triggered();
    void on_action_researchresult_triggered();
    void on_action_search_triggered_handle(int flag);
    void on_action_search_triggered_handle_quick(QString findKey);
    bool check_findKey_exist(QString findKey);
    void proc_search_filecontent(QStringList menuList, Qt::CaseSensitivity cs, QString findKey, QStringList &resultlist);
    void updateListWidgetFrequse();
    void updateListWidgetRecentOpen();


    void proc_listWidget_searchresult_ItemClicked(QListWidgetItem *item);
    void proc_listWidget_findkey_ItemClicked(QListWidgetItem *item);
    void on_pushButton_left_clear_clicked();
    void on_actionclearTry_triggered();
    void proc_character_trim_pub(const QString &pattern);
    void on_action_trim_line_firstspace_triggered();
    void on_action_trim_line_endspace_triggered();
    void on_action_trim_line_space_triggered();
    void on_action_clear_allspace_triggered();
    void on_pushButton_mainfind_clicked();
    void on_pushButton_mainfind_clicked_pub(int reverse);
    void on_pushButton_mainfindreverse_clicked();
    void on_lineEdit_mainsearch_returnPressed();
    void on_action_autoconvertaf_triggered();
    //recent open list process
    void proc_action_recentopen(bool bFlag);
    void updateListRecentOpenKey(QString findKey);
    //process reboot
    void proc_action_procreboot(bool bFlag);
    //regexp text sequence
    void proc_action_GenRegExpTextSeq();
    //mul process mode
    void proc_action_MulProcMode();

    //A/B模式 多行多处理
    void proc_mode_AB_multiline_multiproc(T_RegExpParas &tPara);
    void on_listWidget_searchresult_customContextMenuRequested(const QPoint &pos);
    void proc_action_rename();
    void proc_onNameChanged(QListWidgetItem* item);

    void on_textEdit_copyAvailable(bool b);

    //
    void on_spinBoxFontSize_valueChanged(int aFontSize);//字体大小
    void on_combFont_currentIndexChanged(const QString &arg1);//选择字体

    void on_action_FontBold_triggered(bool checked);

    void on_textEdit_textChanged();

    void on_action_FontItalic_triggered(bool checked);

    void on_action_FontUnder_triggered(bool checked);

    void on_action_clear_triggered();

    void on_action_CurOpen_triggered();

private:
    QString m_preName;
    QString m_curName;
    bool m_rename;


private:
       CThreadExtPub threadMonitor;

private slots:
    void    onthreadM_started();
    void    onthreadM_finished();
    void    onthreadM_newValue(int seq, int diceValue);
    //控制线程
    void on_ThreadM_Start();
    void on_ThreadM_Stop();

    void on_action_CurRightOpen_triggered();

    void on_action_interfaces_triggered();

    void on_actionTcp_Server_triggered();

    void on_actionTcp_Client_triggered();

private:
    bool eventFilter_ui_textEdit(QObject *target, QEvent *event);
    bool eventFilter_ui_textEdit_Tips(QObject *target, QEvent *event);
    bool duplicate_current_line_ui_textEdit();
    bool duplicate_current_line_ui_textEdit_Tips();

};
#endif // MAINWINDOW_H
