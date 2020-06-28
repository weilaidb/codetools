#ifndef CDIALOGASKTEXT_H
#define CDIALOGASKTEXT_H

#include <QDialog>

namespace Ui {
class CDialogAskText;
}

class CDialogAskText : public QDialog
{
    Q_OBJECT

public:
    explicit CDialogAskText(QWidget *parent = nullptr);
    ~CDialogAskText();

private:
    Ui::CDialogAskText *ui;
};

#endif // CDIALOGASKTEXT_H
