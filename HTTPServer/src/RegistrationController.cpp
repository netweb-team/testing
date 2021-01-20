#include "server/controller/RegistrationController.h"

namespace server {

ServerApplicationOut RegistrationController::handle(const string &body) {
  std::istringstream ss(body);
  std::string username = "", password = "";
  ss >> username >> password;
  UserParams registration = {};
  registration.p1.str = (char*) username.c_str();
  registration.p2.str = (char*) password.c_str();
  return ServerApplication::get_instance()->registerUser(registration);
}
}
