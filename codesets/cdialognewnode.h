#ifndef CDIALOGNEWNODE_H
#define CDIALOGNEWNODE_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class CDialogNewNode;
}


class CDialogNewNode : public QDialog
{
    Q_OBJECT

public:
    enum {NEWSTANDMODE, NEWUSERMODE, NEWINVALIDMODE};


    explicit CDialogNewNode(QWidget *parent = nullptr);
    ~CDialogNewNode();

    void setName(QString &name);
    QString getName();
    int getType ();
    int setType(int _val);
    QString getTypeText();
    void write_HistorySetting();

public:
    void closeEvent(QCloseEvent *event);

private:
    void read_Setting();
    void proc_HistorySetting(int type);
    void read_HistorySetting();
    void init_Vars();
    void init_UiSets();

private:
    Ui::CDialogNewNode *ui;
    int m_type;
    QString m_name;

    QSettings *m_pSettings;
    QString m_organization;
    QString m_application;
};

#endif // CDIALOGNEWNODE_H
