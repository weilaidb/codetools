#include "cnetworkpub.h"

#include <QNetworkInterface>

CNetWorkPub::CNetWorkPub()
{

}

QString CNetWorkPub::getAllInterface()
{
    QString result;

    //QNetworkInterface::allInterfaces()函数的使用
    QList<QNetworkInterface>   list=QNetworkInterface::allInterfaces();
    for(int i=0;i<list.count();i++)
    {
        QNetworkInterface aInterface=list.at(i);
        if (!aInterface.isValid())
            continue;

        result.append("设备名称："+ aInterface.humanReadableName());
        result.append("硬件地址："+ aInterface.hardwareAddress());
        QList<QNetworkAddressEntry> entryList=aInterface.addressEntries();
        for(int j=0;j<entryList.count();j++)
        {
            QNetworkAddressEntry aEntry=entryList.at(j);
            result.append("  IP 地址："+ aEntry.ip().toString());
            result.append("  子网掩码："+ aEntry.netmask().toString());
            result.append("  广播地址："+ aEntry.broadcast(). toString()+"\n");
        }
        result.append("\n");
    }

    return result;
}
