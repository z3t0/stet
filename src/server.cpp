#include "server.hpp"
#include <iostream>

#include <zmq.hpp>
#include <string>
#ifndef _WIN32
#include <unistd.h>
#else
#include <window.h>
#define sleep(n) Sleep(n)
#endif


Server::Server(const std::string address) : m_address(address) {

}

void Server::init() {
  zmq::context_t context (1);
  zmq::socket_t socket (context, ZMQ_REP);
  socket.bind(m_address);

  std::cout << "Server Initialized" << std::endl;

  while (true) {

    zmq::message_t request;

    // wait for request
    socket.recv(&request);
    std::cout << "Received" << std::endl;

    zmq::message_t reply (5);
    memcpy(reply.data(), "World", 5);
    socket.send(reply);
  }
}
