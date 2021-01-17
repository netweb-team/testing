#ifndef COMREDSERVER_BASECONTROLLER_H
#define COMREDSERVER_BASECONTROLLER_H

#include <iostream>
#include <utility>
#include <sstream>

#include "ServerApplication.h"
#include "server/BeastServerHeader.h"
#include "server/BasicResponses.h"

namespace server {
using ServerApplicationOut = std::pair<ApplicationErrors, std::string>;

class Controller {
public:
  Controller() = default;
  virtual http::response <http::string_body> handleRequest(http::request <http::string_body> &&request) {
    http::response <http::string_body> res;
    auto applicationResponse = handle(request.body());
    if (applicationResponse.first == ApplicationErrors::success) {
      res.body() = std::move(applicationResponse.second);
      res.keep_alive(request.keep_alive());
      res.prepare_payload();
    } else {
      return BasicResponses::serverError(request, applicationResponse.second);
    }
    return res;
  }
protected:
  virtual ServerApplicationOut handle(const string &body) = 0;
};
}

#endif //COMREDSERVER_BASECONTROLLER_H
