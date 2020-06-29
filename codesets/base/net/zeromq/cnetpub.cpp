#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <zmq.h>
#include "cnetpub.h"

CNetPub::CNetPub()
{

}

int CNetPub::sendMsg()
{
    return 0;
}


int CNetPub::startServer(const char *uri)
{
    printf ("startServer\n");
    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, uri);
    assert (rc == 0);

    while (1) {
        char buffer [10];
        zmq_recv (responder, buffer, 10, 0);
        printf ("Received Hello\n");
        sleep (1);          //  Do some 'work'
        zmq_send (responder, "World", 5, 0);
    }
    return 0;
}

int CNetPub::startClient(const char *uri)
{
    printf ("Connecting to hello world server...\n");

    /*创建一个新的上下文*/
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    /*通过tcp协议，5555端口，连接本机服务端*/
    zmq_connect (requester, uri);

    int request_nbr;
    for (request_nbr = 0; request_nbr != 1000; request_nbr++) {
        char buffer [10];
        printf ("Sending Hello %d \n", request_nbr);
        zmq_send (requester, "Hello", 5, 0);
        zmq_recv (requester, buffer, 10, 0);
        printf ("Received World %d\n", request_nbr);
    }

    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}

int CNetPub::startServer()
{
    startServer("tcp://*:5555");
    return 0;
}

int CNetPub::startClient()
{
    startClient("tcp://localhost:5555");
    return 0;
}


