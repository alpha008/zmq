/*
 *  you need build libzmq firstly
 *  g++ -o responser responser.cpp -lzmq
 */

#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#define MAX_BUFFER_LEN 1024

int main (int argc, char** argv)
{
    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    const char *host = (argc > 1)? argv[1]:"localhost:9006";
    char endpoint[128];
    snprintf(endpoint, 128, "%s%s", "tcp://", host);
    printf("endpoint is %s.\n", endpoint);

    int rc = zmq_connect (responder, endpoint);
    if (rc != 0)
    {
        printf ("Error occurred during zmq_bind(): %s\n", zmq_strerror (errno));
        return -1;
    } else {
        printf("connected to %s.\n", endpoint);
    }

    printf("service started with host %s.\n", endpoint);
    int count = 0;

    while (1) 
    {
        char buffer [MAX_BUFFER_LEN] = {0};
        zmq_recv (responder, buffer, 10, 0);
        printf ("%s.\n", buffer);
        sleep (1);
        zmq_send (responder, "World", 5, 0);
        printf("send world to client with count=%d.\n", count);
        count ++;
    }

    return 0;
}


