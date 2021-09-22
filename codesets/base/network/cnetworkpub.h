#ifndef CNETWORKPUB_H
#define CNETWORKPUB_H

#include <QAbstractSocket>
#include <QHostInfo>
#include <QString>



class CNetWorkPub
{
public:
    CNetWorkPub();

    static QString getAllInterface();
    static QString getAllAddress();


    static QString protocolName(QAbstractSocket::NetworkLayerProtocol protocol);
    static QString lookedUpHostInfo(const QHostInfo &host);
};

#endif // CNETWORKPUB_H
