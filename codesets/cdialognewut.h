#ifndef CDIALOGNEWUT_H
#define CDIALOGNEWUT_H

#include <QDialog>

namespace Ui {
class CDialogNewUt;
}

class CDialogNewUt : public QDialog
{
    Q_OBJECT

public:
    explicit CDialogNewUt(QWidget *parent = nullptr);
    ~CDialogNewUt();

    void setPath(QString &path);

private:
    Ui::CDialogNewUt *ui;
};

#endif // CDIALOGNEWUT_H
