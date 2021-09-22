#include "cnetworkpub.h"

#include <QHostInfo>
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

QString CNetWorkPub::getAllAddress()
{
    QString result;

    //QNetworkInterface::allAddresses()的使用
    QList<QHostAddress> addList=QNetworkInterface::allAddresses();
    if (!addList.isEmpty())
        for (int i=0;i<addList.count();i++)
        {
            QHostAddress aHost=addList.at(i);
            CStringPub::appendStringEnter(result, "协  议："+ protocolName(aHost.protocol()));
            CStringPub::appendStringEnter(result, "IP地址："+aHost.toString());
            CStringPub::appendStringEnter(result, "");
        }

    return result;
}

QString CNetWorkPub::protocolName(QAbstractSocket::NetworkLayerProtocol protocol)
{//通过协议类型返回协议名称
    switch(protocol)
    {
    case QAbstractSocket::IPv4Protocol:
        return "IPv4 Protocol";
    case QAbstractSocket::IPv6Protocol:
        return "IPv6 Protocol";
    case QAbstractSocket::AnyIPProtocol:
        return "Any IP Protocol";
    default:
        return "Unknown Network Layer Protocol";
    }
}


QString CNetWorkPub::lookedUpHostInfo(const QHostInfo &host)
{
    QString result;

    qDebug() << "hostname:" << host.hostName();

    //查找主机信息的槽函数
    QList<QHostAddress> addList=host.addresses();//
    if (!addList.isEmpty())
        for (int i=0;i<addList.count();i++)
        {
            QHostAddress aHost=addList.at(i);
            CStringPub::appendStringEnter(result, ("协 议："+protocolName(aHost.protocol())));
            CStringPub::appendStringEnter(result, aHost.toString());
            CStringPub::appendStringEnter(result, "");
        }

    return result;
}
