#include "server/controller/GetTextController.h"

namespace server {
ServerApplicationOut GetTextController::handle(const string &body) {
  std::istringstream ss(body);
  int documentId;
  ss >> documentId;
  DocumentParams getText = { documentId };
  return ServerApplication::get_instance()->getTextDocument(getText);
}
}
