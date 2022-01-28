#ifndef TEST1_H
#define TEST1_H

#include <QWidget>

namespace Ui {
class test1;
}

class test1 : public QWidget
{
    Q_OBJECT

public:
    explicit test1(QWidget *parent = nullptr);
    ~test1();

private:
    Ui::test1 *ui;
};

#endif // TEST1_H
