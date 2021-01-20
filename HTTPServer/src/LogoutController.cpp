#include "server/controller/LogoutController.h"

namespace server {

ServerApplicationOut LogoutController::handle(const string &body) {
  std::istringstream is(body);
  int userId;
  is >> userId;
  UserParams logout = { userId };
  return ServerApplication::get_instance()->logoutUser(logout);
}
}
