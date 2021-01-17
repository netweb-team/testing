#ifndef COMREDSERVER_LOGOUTCONTROLLER_H
#define COMREDSERVER_LOGOUTCONTROLLER_H

#include "Controller.h"

namespace server {
class LogoutController : public Controller {
public:
  LogoutController() = default;
private:
  ServerApplicationOut handle(const string &body) override;
};
}

#endif