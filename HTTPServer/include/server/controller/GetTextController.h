#ifndef COMREDSERVER_GETTEXTCONTROLLER_H
#define COMREDSERVER_GETTEXTCONTROLLER_H

#include "Controller.h"

namespace server {
class GetTextController : public Controller {
public:
  GetTextController() = default;
private:
  ServerApplicationOut handle(const string &body) override;
};
}

#endif
