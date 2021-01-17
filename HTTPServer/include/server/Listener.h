#ifndef COMREDSERVER_LISTENER_H
#define COMREDSERVER_LISTENER_H

#include "Connection.h"
#include "BeastServerHeader.h"

namespace server {
class Listener : public std::enable_shared_from_this<Listener> {
public:
  Listener(net::io_context &ioc, tcp::endpoint endpoint);

  void run();

private:
  void doAccept();

  void onAccept(beast::error_code ec, tcp::socket socket);

private:
  net::io_context &ioc_;
  tcp::acceptor acceptor_;
};
}

#endif //COMREDSERVER_INCLUDE_SERVER_LISTENER_H
