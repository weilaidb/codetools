#ifndef CMSGTIPS_H
#define CMSGTIPS_H

#include <QWidget>
#include <QLabel>

class CMsgTips : public QWidget
{
    Q_OBJECT
public:
    CMsgTips();
    ~CMsgTips();
    explicit CMsgTips(QWidget *parent = nullptr);
    CMsgTips(QWidget *parent,quint32 ultimeout);
    void SetTipsInfo(QString s);
    void WidgetXYsetDesktop_center(QWidget *widget);

signals:

private slots:
    void proc_timeout();

private:
    QString str;
    QTimer *timer;
    QLabel *label;
    quint32 m_ultimeout;
};


void ShowTipsInfo(QString s) ;
void ShowTipsInfoWithShowTime(QString s, quint32 ultimeout);



#endif // CMSGTIPS_H
