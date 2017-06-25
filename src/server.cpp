#include "server.hpp"
#include <iostream>
#include <pthread.h>
#include <unistd.h>

#include <zmq.hpp>
#include <string>
#ifndef _WIN32
#include <unistd.h>
#else
#include <window.h>
#define sleep(n) Sleep(n)
#endif

void *request_handler(void *arg);


Server::Server(const std::string address) : m_address(address) {

}

void Server::init() {
  zmq::context_t context (1);
  zmq::socket_t clients(context, ZMQ_ROUTER);
  clients.bind(m_address);
  zmq::socket_t workers (context, ZMQ_DEALER);
  workers.bind("inproc://workers");

  std::cout << "Server Initialized" << std::endl;

  // Launch workers
  for (int thread_nbr = 0; thread_nbr != 5; thread_nbr++) {
    pthread_t worker;
    pthread_create(&worker, NULL, request_handler, (void *) &context);
  }

  zmq::proxy(clients, workers, NULL);
  
}


void *request_handler(void *arg) {

  std::cout << "Worker thread initialized" << std::endl;

  zmq::context_t *context = (zmq::context_t *) arg;

  zmq::socket_t socket (*context, ZMQ_REP);
  socket.connect("inproc://workers");

  while(true) {
    // Wait for next request
    zmq::message_t request;
    socket.recv (&request);
    std::cout << "Received request: [" << (char*) request.data() << "]" << std::endl;

    // Do somw work

    // Send reply back
    zmq::message_t reply (6);
    memcpy((void *) reply.data(), "World", 6);
    socket.send(reply);

  }

  return (NULL);

}
