#ifndef CNETDIAGLOG_H
#define CNETDIAGLOG_H

#include <QDialog>
#include <QHostInfo>

namespace Ui {
class CNetDialog;
}

class CNetDiaglog : public QDialog
{
    Q_OBJECT

public:
    explicit CNetDiaglog(QWidget *parent = 0);
    ~CNetDiaglog();

private slots:
    void lookedUpHostInfo(const QHostInfo &host);

    //===========================
    void on_btnGetHostInfo_clicked();

    void on_btnDetail_clicked();

    void on_btnLookup_clicked();

    void on_btnALLInterface_clicked();

    void on_btnClear_clicked();

private:
    Ui::CNetDialog *ui;

    QString  protocolName(QAbstractSocket::NetworkLayerProtocol protocol);
};


#endif // CNETDIAGLOG_H
