#ifndef COMREDSERVER_EDITCONTROLLER_H
#define COMREDSERVER_EDITCONTROLLER_H

#include "Controller.h"

namespace server {
class EditController : public Controller {
public:
  EditController() = default;
protected:
  ServerApplicationOut handle(const string &body) override;
};
}

#endif
