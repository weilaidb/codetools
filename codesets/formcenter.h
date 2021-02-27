#ifndef FORMCENTER_H
#define FORMCENTER_H

#include <QWidget>

namespace Ui {
class FormCenter;
}

class FormCenter : public QWidget
{
    Q_OBJECT

public:
    explicit FormCenter(QWidget *parent = nullptr);
    ~FormCenter();

    //函数
private:
    void initButtonSets();


private slots:
    void proc_pushButton_tryagain();
    void proc_action_TryAgain();

private:
    Ui::FormCenter *ui;
};

#endif // FORMCENTER_H
