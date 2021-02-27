#include "cmsgtips.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QTimer>


CMsgTips::CMsgTips()
{

}

CMsgTips::~CMsgTips()
{
    deleteLater();
}

CMsgTips::CMsgTips(QWidget *parent) :
    QWidget(parent),
    m_ultimeout(2000)
{
    setWindowFlags(Qt::FramelessWindowHint);
    label = new QLabel(this);
    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()), this,SLOT(close()));
}

CMsgTips::CMsgTips(QWidget *parent,quint32 ultimeout) :
    QWidget(parent),
    m_ultimeout(ultimeout)
{
    setWindowFlags(Qt::FramelessWindowHint);
    label = new QLabel(this);
    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()), this,SLOT(proc_timeout()));
}


void CMsgTips::proc_timeout()
{
   close();
   delete this;
}

void CMsgTips::SetTipsInfo(QString s)
{
    str = s;
    label->setText(QString::fromUtf8(str.toUtf8()));
    label->setStyleSheet("QLabel{font: bold italic large \"Times New Roman\";font-size:25px;color:rgb(55,100,255);height:50px;border:4px solid rgb(155,200,33);background-color: rgba(0,0,0,30);border-radius:15px;selection-color:pink}");
    label->setWordWrap(false);
    label->adjustSize(); //自动调整大小
    label->setAlignment(Qt::AlignCenter);
    timer->start(m_ultimeout);
}

void CMsgTips::WidgetXYsetDesktop_center(QWidget *widget)
{
    QDesktopWidget *desk=QApplication::desktop();
    int wd=desk->width();
    int ht=desk->height();
    widget->move((wd - width()/2)/2,(ht-height()/2)/2);
}


void ShowTipsInfo(QString s)
{
    CMsgTips *tipsinfo = new CMsgTips(NULL);
    tipsinfo->SetTipsInfo(s);
    //无任务栏图标，无工具栏，置顶显示
    tipsinfo->setWindowFlags( Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    tipsinfo->show();
}

void ShowTipsInfoWithShowTime(QString s, quint32 ultimeout)
{
    CMsgTips *tipsinfo = new CMsgTips(NULL, ultimeout);
    tipsinfo->SetTipsInfo(s);
    //无任务栏图标，无工具栏，置顶显示
    tipsinfo->setWindowFlags( Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    tipsinfo->show();
}




