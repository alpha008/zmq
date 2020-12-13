
#include "zmq.hpp"
#include <iostream>
#include <unistd.h>

int main(int argc, char** argv){
    
    zmq::context_t context (1);
    zmq::socket_t xsub(context, ZMQ_XSUB);
    xsub.bind("tcp://*:9005");
   
    zmq::socket_t xpub(context, ZMQ_XPUB);
    xpub.bind("tcp://*:9006");

    sleep(1);
    std::cout << "start proxy before" << std::endl;
    //zmq::proxy(&xsub, &xpub, nullptr);
    zmq::proxy((void*)xsub, (void*)xpub, nullptr);
    std::cout << "start proxy" << std::endl;

    return 0;
}

