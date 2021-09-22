#ifndef CCMDWINDOW_H
#define CCMDWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <handleapi.h>
#include <QShortcut>

namespace Ui {
class CmdWindow;
}

class CCmdWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CCmdWindow(QWidget *parent = 0);
    ~CCmdWindow();

private:
    Ui::CmdWindow *ui;
    QProcess *process;
    QShortcut *key;

public slots:
    void write_cmd();
    void read_data();
    void finished_process();
    void error_process();

};

#endif // CCMDWINDOW_H
