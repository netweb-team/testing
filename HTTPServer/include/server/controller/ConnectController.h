#ifndef COMREDSERVER_CONNECTCONTROLLER_H
#define COMREDSERVER_CONNECTCONTROLLER_H

#include "Controller.h"


namespace server {
class ConnectController : public Controller {
public:
  ConnectController() = default;
private:
  ServerApplicationOut handle(const string &body) override;
};
}

#endif
