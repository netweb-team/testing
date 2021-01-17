#include "server/Listener.h"

namespace server {
Listener::Listener(net::io_context &ioc, tcp::endpoint endpoint)
    : ioc_(ioc), acceptor_(net::make_strand(ioc)) {
  beast::error_code ec;

  acceptor_.open(endpoint.protocol(), ec);
  if (ec) {
    fail(ec, "open");
    return;
  }

  acceptor_.set_option(net::socket_base::reuse_address(true), ec);
  if (ec) {
    fail(ec, "set_option");
    return;
  }

  acceptor_.bind(endpoint, ec);
  if (ec) {
    fail(ec, "bind");
    return;
  }

  acceptor_.listen(
      net::socket_base::max_listen_connections, ec);
  if (ec) {
    fail(ec, "listen");
    return;
  }
}

void Listener::run() {
  doAccept();
}

void Listener::doAccept() {
  acceptor_.async_accept(
      net::make_strand(ioc_),
      beast::bind_front_handler(
          &Listener::onAccept,
          shared_from_this()));
}

void Listener::onAccept(beast::error_code ec, tcp::socket socket) {
  if (ec) {
    fail(ec, "accept");
  } else {
    std::make_shared<Connection>(std::move(socket))->run();
  }
  doAccept();
}
}

