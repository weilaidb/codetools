#ifndef SUPERTEST_H
#define SUPERTEST_H

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


    //function
    void init_ActionSets();
    void init_PushButtonSets();
    void init_Vars();
    void init_UiSets();
    void init_ListWidget();
    void config_cur_load_path(QString path);
    void nodes_menu_leftbottom(QMenu *pMenu);

private slots:
    void proc_pushButton_load_test_dir();

    void on_pushButton_load_test_dir_clicked();

    void on_pushButton_open_test_dir_clicked();

    void proc_listWidget_load_dir_ItemDoubleClicked(QListWidgetItem *item);
    void on_pushButton_reload_dir_clicked();
    void proc_actionOpenConfigFile();
    void proc_actionOpenConfigDir();

    void proc_generate_menu_left(QPoint pos);
private:
    Ui::SuperTest *ui;
    QString openFilePathRecent;
    QString file_content_txt;
    QString file_result_log;
    QString dir_cur_loaded;
    QString file_cur_item_load;

    /* 右键菜单 */
    QMenu *pRightMouse;
};

#endif // SUPERTEST_H
