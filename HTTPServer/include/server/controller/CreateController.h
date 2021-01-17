#ifndef COMREDSERVER_CREATECONTROLLER_H
#define COMREDSERVER_CREATECONTROLLER_H

#include "Controller.h"
namespace server {
class CreateController : public Controller {
public:
  CreateController() = default;
private:
  ServerApplicationOut handle(const string &body) override;
};
}

#endif