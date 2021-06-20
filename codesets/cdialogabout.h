#ifndef CDIALOGABOUT_H
#define CDIALOGABOUT_H

#include <QDialog>

namespace Ui {
class CDialogAbout;
}

class CDialogAbout : public QDialog
{
    Q_OBJECT

public:
    explicit CDialogAbout(QWidget *parent = nullptr);
    ~CDialogAbout();
    void setText(QString text);
private:
    Ui::CDialogAbout *ui;
};

#endif // CDIALOGABOUT_H
