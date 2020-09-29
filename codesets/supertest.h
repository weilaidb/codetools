#ifndef SUPERTEST_H
#define SUPERTEST_H

#include <QCloseEvent>
#include <QSettings>
#include <QListWidget>
#include <QMainWindow>

namespace Ui {
class SuperTest;
}

class SuperTest : public QMainWindow
{
    Q_OBJECT

public:
    explicit SuperTest(QWidget *parent = nullptr);
    ~SuperTest();
    void closeEvent(QCloseEvent *event);


private:
    //function
    void init_ActionSets();
    void init_PushButtonSets();
    void init_Vars();
    void init_UiSets();
    void init_ListWidget();
    void config_cur_load_path(QString path);
    void nodes_menu_leftbottom(QMenu *pMenu);
    void read_Setting();
    void proc_HistorySetting(int type);
    void read_HistorySetting();
    void write_HistorySetting();
    QString getUtNamePrefix();


private slots:
    void proc_pushButton_load_test_dir();
    void proc_actionAbout();

    void on_pushButton_load_test_dir_clicked();

    void on_pushButton_open_test_dir_clicked();

    void proc_listWidget_load_dir_ItemDoubleClicked(QListWidgetItem *item);
    void on_pushButton_reload_dir_clicked();
    void proc_actionOpenConfigFile();
    void proc_actionOpenConfigDir();
    void proc_actionSaveFile();
    void proc_actionReloadFile();

    void proc_generate_menu_left(QPoint pos);
    void on_action_new_ut_instance_triggered();

    void on_actionSave_triggered();

    void on_lineEdit_returnPressed();

private:
    Ui::SuperTest *ui;
    QString openFilePathRecent;
    QString file_content_txt;
    QString file_result_log;
    QString dir_cur_loaded;
    QString file_cur_item_load;

    /* 右键菜单 */
    QMenu *pRightMouse;


    //QSettings
    QSettings *m_pSettings;
    QString m_organization;
    QString m_application;
    //Attention
    QString m_AttentionFile;
};

#endif // SUPERTEST_H
