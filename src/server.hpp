#ifndef SERVER_HPP
#define SERVER_HPP
#include <string>

class Server {
public:
  Server(const std::string address);
  void init();

  std::string m_address;


};

#endif
