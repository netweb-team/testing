#include "server/controller/LoginController.h"

namespace server {

ServerApplicationOut LoginController::handle(const string &body) {
  std::istringstream ss(body);
  std::string username = "", password = "";
  ss >> username >> password;
  UserParams login = {};
  login.p1.str = (char*) username.c_str();
  login.p2.str = (char*) password.c_str();
  return ServerApplication::get_instance()->loginUser(login);
}
}
