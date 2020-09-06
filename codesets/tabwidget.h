#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMutex>
#include <QSettings>
#include <cnetthreadpub.h>



QT_BEGIN_NAMESPACE
namespace Ui { class TabWidget; }
QT_END_NAMESPACE

class TabWidget : public QMainWindow
{
    Q_OBJECT

public:
    TabWidget(char *appexe, QWidget *parent = nullptr);
    void initUiSets();
private:
    void showVersion();
    void initActionSets();
    void initCheckBoxSets();
    void initVars();

public slots:
    void actNewTab();
private:
    Ui::TabWidget *ui;
    //程序名
    QString m_apppath;
    QMdiArea *m_mdiArea;
    quint16 m_tabpos;
    quint16 m_deftabcnt;

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


};

#endif // TABWIDGET_H
