#ifndef COMREDSERVER_LOGINCONTROLLER_H
#define COMREDSERVER_LOGINCONTROLLER_H

#include "Controller.h"

namespace server {
class LoginController : public Controller {
public:
  LoginController() = default;
private:
  ServerApplicationOut handle(const string &body) override;
};
}

#endif
