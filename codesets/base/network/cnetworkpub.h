#ifndef CNETWORKPUB_H
#define CNETWORKPUB_H

#include <QAbstractSocket>
#include <QString>



class CNetWorkPub
{
public:
    CNetWorkPub();

    static QString getAllInterface();
    static QString getAllAddress();


    static QString protocolName(QAbstractSocket::NetworkLayerProtocol protocol);
};

#endif // CNETWORKPUB_H
