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

private:
    void showVersion();
    void initUiSets();

public slots:
    void actNewTab();
private:
    Ui::TabWidget *ui;
    //程序名
    QString m_apppath;
    QMdiArea *m_mdiArea;
    quint16 m_tabpos;
    quint16 m_deftabcnt;


};

#endif // TABWIDGET_H
