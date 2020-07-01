#ifndef CNETPUB_H
#define CNETPUB_H


class CNetPub
{
public:
    CNetPub();
    static int sendMsg();
    static int startServer(const char *uri);
    static int startClient(const char *uri);
    static int startServer();
    static int startClient();
    static int startPublish();
    static int startSubscribe();

};

#endif // CNETPUB_H
