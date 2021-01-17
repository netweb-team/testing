#ifndef COMREDSERVER_CONNECTION_H
#define COMREDSERVER_CONNECTION_H

#include "handleRequest.h"

#include <iostream>

namespace server {

class Connection : public std::enable_shared_from_this<Connection> {
public:
  explicit Connection(tcp::socket &&socket)
      : stream_(std::move(socket)), lambda_(*this) {
  }

  void run();

  void doRead();

  void onRead(beast::error_code ec, std::size_t bytes_transferred);

  void onWrite(bool close, beast::error_code ec, std::size_t bytes_transferred);

  void doClose();

private:
  struct SendLambda {
    Connection &self_;

    explicit
    SendLambda(Connection &self)
        : self_(self) {
    }

    void operator()(http::response<http::string_body> &&msg) const;
  };

private:
  beast::tcp_stream stream_;
  beast::flat_buffer buffer_;
  std::shared_ptr<std::string const> doc_root_;
  http::request<http::string_body> req_;
  std::shared_ptr<void> res_;
  SendLambda lambda_;
};
}

#endif //COMREDSERVER_INCLUDE_SERVER_CONNECTION_H
