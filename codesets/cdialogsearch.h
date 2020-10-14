#ifndef CDIALOGSEARCH_H
#define CDIALOGSEARCH_H

#include <QDialog>
#include <QListWidget>
#include <QSettings>

namespace Ui {
class CDialogSearch;
}

class CDialogSearch : public QDialog
{
    Q_OBJECT

public:
    explicit CDialogSearch(QWidget *parent = nullptr);
    ~CDialogSearch();

    QString getKey();
    Qt::CaseSensitivity getCaseSentived();
    bool getFileContented();
private:
    Ui::CDialogSearch *ui;
    QString m_key;


public:
    void closeEvent(QCloseEvent *event);

private:
    void init_Vars();
    void init_UiSets();
    void read_Setting();
    void proc_HistorySetting(int type);
    void read_HistorySetting();
    void write_HistorySetting();

    QSettings *m_pSettings;
    QString m_organization;
    QString m_application;
    QStringList m_searchList;
    QListWidget *m_pListWidget;

};

#endif // CDIALOGSEARCH_H
