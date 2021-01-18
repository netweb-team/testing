#include "server/controller/CreateController.h"

namespace server {
ServerApplicationOut CreateController::handle(const string &body) {
  std::istringstream ss(body);
  int documentId;
  std::string documentName;
  ss >> documentId;
  ss.ignore(1);
  getline(ss, documentName);
  DocumentParams create = { documentId };
  create.p2.str = (char*) documentName.c_str();
  return ServerApplication::get_instance()->createDocument(create);
}
}
