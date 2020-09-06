#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QMainWindow>
#include <QMdiArea>



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

public slots:
    void actNewTab();
private:
    Ui::TabWidget *uitab;
    //程序名
    QString m_apppath;
    QMdiArea *m_mdiArea;
    quint16 m_tabpos;
    quint16 m_deftabcnt;
};

#endif // TABWIDGET_H
