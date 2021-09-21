#include "cnetworkpub.h"

#include <QNetworkInterface>
#include "cstringpub.h"

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

        CStringPub::appendStringEnter(result, ("设备名称："+ aInterface.humanReadableName()));
        CStringPub::appendStringEnter(result, ("硬件地址："+ aInterface.hardwareAddress()));
        QList<QNetworkAddressEntry> entryList=aInterface.addressEntries();
        for(int j=0;j<entryList.count();j++)
        {
            QNetworkAddressEntry aEntry=entryList.at(j);
            CStringPub::appendStringEnter(result, "  IP 地址："+ aEntry.ip().toString());
            CStringPub::appendStringEnter(result, "  子网掩码："+ aEntry.netmask().toString());
            CStringPub::appendStringEnter(result, "  广播地址："+ aEntry.broadcast(). toString()+"\n");
        }
        CStringPub::appendStringEnter(result, "");
    }

    return result;
}
