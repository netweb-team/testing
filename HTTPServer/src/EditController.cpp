#include "server/controller/EditController.h"

namespace server {
ServerApplicationOut EditController::handle(const std::string &body) {
  std::istringstream ss(body);
  int editorId, documentId, cursorPosition;
  std::string operations;
  ss >> editorId >> documentId >> cursorPosition;
  ss.ignore(1);
  getline(ss, operations);
  return ServerApplication::get_instance()->updateDocument(editorId, documentId, cursorPosition, operations);
}
}
