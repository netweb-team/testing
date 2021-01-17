#ifndef COMREDSERVER_DISCONNECTCONTROLLER_H
#define COMREDSERVER_DISCONNECTCONTROLLER_H

#include "Controller.h"

namespace server {
class DisconnectController : public Controller {
public:
  DisconnectController() = default;
private:
  ServerApplicationOut handle(const string &body) override;
};
}

#endif
