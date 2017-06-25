#include <iostream>
#include "server.hpp"

int main() {

  std::cout << "Stet initialized" << std::endl;

  Server server("tcp://*:5555");
  server.init();

  std::cout << "Hello, world" << std::endl;

  return 1;
}
