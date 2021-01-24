#ifndef CDIALOGNEWNODE_H
#define CDIALOGNEWNODE_H

#include <QDialog>

namespace Ui {
class CDialogNewNode;
}


class CDialogNewNode : public QDialog
{
    Q_OBJECT

public:
    enum {NEWSTANDMODE, NEWUSERMODE, NEWINVALIDMODE};


    explicit CDialogNewNode(QWidget *parent = nullptr);
    ~CDialogNewNode();

    void setName(QString &name);
    QString getName();
    int getType ();
    int setType(int _val);
    QString getTypeText();
private:
    Ui::CDialogNewNode *ui;
    int m_type;
};

#endif // CDIALOGNEWNODE_H
