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

private:
    Ui::FormCenter *ui;
};

#endif // FORMCENTER_H
