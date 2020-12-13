
/*
 * you need to build libzmq firstly.
 * g++ -o request request.cpp -lzmq
 * request_v3 192.168.2.128:9005 identify
 */


#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_BUFFER_LEN 1024

int main (int argc, char** argv){

    printf ("Connecting to hello world server…\n");
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);

    const char *host = (argc > 1)? argv[1]:"localhost:9005";
    char endpoint[128];
    snprintf(endpoint, 128, "%s%s", "tcp://", host);
    zmq_connect( requester, endpoint);
    printf("connect to %s", endpoint);

    const char *identify = (argc > 2) ? argv[2] : "" ;

    for (int i = 0; i < 50; i ++){
        char buffer [MAX_BUFFER_LEN] = {0};
        sprintf(buffer, "%s hello_%d", identify, i);
        printf ("Send %s to server.\n", buffer);
        zmq_send (requester, buffer, strlen(buffer), 0);
        memset(buffer, 0, MAX_BUFFER_LEN);
        zmq_recv (requester, buffer, 10, 0);
        printf ("Received %s.\n", buffer);
    }

    zmq_close (requester);
    zmq_ctx_destroy (context);
   
    return 0;
}

