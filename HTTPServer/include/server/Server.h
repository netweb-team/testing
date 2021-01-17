#ifndef COMREDSERVER_SERVER_H
#define COMREDSERVER_SERVER_H

#include <string>
#include <vector>

#include "BeastServerHeader.h"

namespace server {
class Server {
public:
  Server(const std::string &addr,
         unsigned short port, int threads);

  void run();

private: // functions
  void setAccept();

private: // functions
  std::string address_;
  unsigned short port_;
  net::io_context context_;
  int threads_;
};

}

#endif //COMREDSERVER_SERVER_H
