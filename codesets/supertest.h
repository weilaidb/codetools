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
    void init_ListWidget();
    void config_cur_load_path(QString path);

private slots:
    void proc_pushButton_load_test_dir();

    void on_pushButton_load_test_dir_clicked();

    void on_pushButton_open_test_dir_clicked();

    void proc_listWidget_load_dir_ItemDoubleClicked(QListWidgetItem *item);
private:
    Ui::SuperTest *ui;
    QString openFilePathRecent;
    QString file_content_txt;
    QString file_result_log;
    QString dir_cur_loaded;

};

#endif // SUPERTEST_H
