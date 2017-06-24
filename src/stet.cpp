#include <iostream>
#include <zmq.hpp>
#include <string>
#ifndef _WIN32
#include <unistd.h>
#else
#include <window.h>
#define sleep(n) Sleep(n)
#endif

using namespace std;

int main() {

  std::cout << "Stet initialized" << std::endl;

  // zeromq
  zmq::context_t context (1);
  zmq::socket_t socket (context, ZMQ_REP);
  socket.bind("tcp://*:5555");

  while (true) {

    zmq::message_t request;

    // wait for request
    socket.recv(&request);
    std::cout << "Received" << std::endl;

    zmq::message_t reply (5);
    memcpy(reply.data(), "World", 5);
    socket.send(reply);
  }

  return 1;
}
