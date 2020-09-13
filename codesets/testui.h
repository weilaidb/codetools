#ifndef TESTUI_H
#define TESTUI_H

#include <QMainWindow>

namespace Ui {
class testui;
}

class testui : public QMainWindow
{
    Q_OBJECT

public:
    explicit testui(QWidget *parent = nullptr);
    ~testui();

private slots:
    void on_pushButton_clicked();
    void proc_pushButton_clicked();

private:
    Ui::testui *ui;
};

#endif // TESTUI_H
