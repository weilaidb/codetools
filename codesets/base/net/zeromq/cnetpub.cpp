#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "cnetpub.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <assert.h>
using namespace std;



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
//    //  Socket to talk to clients
//    void *context = zmq_ctx_new ();
//    void *responder = zmq_socket (context, ZMQ_REP);
//    int rc = zmq_bind (responder, uri);
//    assert (rc == 0);

//    while (1) {
//        char buffer [10];
//        zmq_recv (responder, buffer, 10, 0);
//        printf ("Received Hello\n");
//        sleep (1);          //  Do some 'work'
//        zmq_send (responder, "World", 5, 0);
//    }
    return 0;
}

int CNetPub::startClient(const char *uri)
{
    printf ("Connecting to hello world server...\n");

//    /*创建一个新的上下文*/
//    void *context = zmq_ctx_new ();
//    void *requester = zmq_socket (context, ZMQ_REQ);
//    /*通过tcp协议，5555端口，连接本机服务端*/
//    zmq_connect (requester, uri);

//    int request_nbr;
//    for (request_nbr = 0; request_nbr != 1000; request_nbr++) {
//        char buffer [10];
//        printf ("Sending Hello %d \n", request_nbr);
//        zmq_send (requester, "Hello", 5, 0);
//        zmq_recv (requester, buffer, 10, 0);
//        printf ("Received World %d\n", request_nbr);
//    }

//    zmq_close (requester);
//    zmq_ctx_destroy (context);
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

int CNetPub::startPublish()
{
//    void *context = zmq_ctx_new ();
//    void *publisher = zmq_socket (context, ZMQ_PUB);
//    int rc = zmq_bind (publisher, "tcp://*:5556");
//    assert (rc == 0);

//    //  Initialize random number generator
//    srand(time(0));
//    while (1) {
//        int zipcode, temperature, relhumidity;
//        zipcode     = rand() % 100000;
//        temperature = rand() % 215 - 80;
//        relhumidity = rand() % 50 + 10;

//        ostringstream os;
//        os << setw(5) << setfill('0')<< zipcode <<" "
//           << temperature <<" "<< relhumidity << "\n";

//        zmq_send(publisher, os.str().c_str(), strlen(os.str().c_str()), 0);
//    }
//    zmq_close (publisher);
//    zmq_ctx_destroy (context);

    return 0;
}

int CNetPub::startSubscribe()
{
    //  Socket to talk to server
    printf ("Collecting updates from weather server...\n");
//    void *context = zmq_ctx_new ();
//    void *subscriber = zmq_socket (context, ZMQ_SUB);
//    int rc = zmq_connect (subscriber, "tcp://localhost:5556");
//    assert (rc == 0);

//    char filter1[] = "10001 ";
//    char filter2[] = "20002 ";
//    rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE,filter1, strlen (filter1));
//    assert (rc == 0);
//    rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE,filter2, strlen (filter2));
//    assert (rc == 0);

//    //  Process 100 updates
//    int size;
//    char buffer [256];
//    for (int update_nbr = 0; update_nbr < 100; update_nbr++) {

//        memset(buffer, 0, 256*sizeof(char));
//        size = zmq_recv (subscriber, buffer, 255, 0);
//        if (size == -1){
//            cout<< "receiver error , skip this message"<<endl;
//            continue;
//        }
//        buffer[size] = '\0';
//        cout << buffer <<endl;
//    }

//    zmq_close (subscriber);
//    zmq_ctx_destroy (context);

    return 0;
}


