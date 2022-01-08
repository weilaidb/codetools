#include "cdatetime.h"

#include <QDateTime>

CDateTime::CDateTime()
{

}

QString CDateTime::format1()
{
    QDateTime begin_time = QDateTime::currentDateTime();//获取系统现在的时间
    QString begin =begin_time .toString("yyyyMMdd hhmmss");

    return begin;
}

QString CDateTime::format2()
{
    QDateTime begin_time = QDateTime::currentDateTime();//获取系统现在的时间
    QString begin =begin_time .toString("yyyy.MM.dd hh:mm:ss.zzz ddd");

    return begin;
}
