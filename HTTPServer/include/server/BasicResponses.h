#ifndef COMREDSERVER_BASICRESPONSES_H
#define COMREDSERVER_BASICRESPONSES_H

#include "BeastServerHeader.h"

#include <memory>
#include <iostream>

namespace server {
namespace BasicResponses {
inline http::response <http::string_body> badRequest(
    const http::request <http::string_body> &req,
    const string &why) {
  http::response<http::string_body> res{http::status::bad_request, req.version()};
  res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
  res.keep_alive(req.keep_alive());
  res.body() = std::string(why);
  res.prepare_payload();
  return res;
}

inline http::response <http::string_body> serverError(
    const http::request <http::string_body> &req,
    const string &what) {
  http::response<http::string_body> res{http::status::internal_server_error, req.version()};
  res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
  res.keep_alive(req.keep_alive());
  res.body() = "An error occurred: '" + std::string(what) + "'";
  res.prepare_payload();
  return res;
}
};
}

#endif
