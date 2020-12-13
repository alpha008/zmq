
#include "zmq.hpp"
#include <iostream>
#include <unistd.h>

int main(int argc, char** argv){
    
    zmq::context_t context (1);
    zmq::socket_t frontend(context, ZMQ_ROUTER);
    frontend.bind("tcp://*:9005");
   
    zmq::socket_t backend(context, ZMQ_DEALER);
    backend.bind("tcp://*:9006");

    sleep(1);
    std::cout << "start proxy before" << std::endl;
    //zmq::proxy(&xsub, &xpub, nullptr);
    zmq::proxy((void*)frontend, (void*)backend, nullptr);
    std::cout << "start proxy" << std::endl;

    return 0;
}

