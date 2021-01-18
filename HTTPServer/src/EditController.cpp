#include "server/controller/EditController.h"

namespace server {
ServerApplicationOut EditController::handle(const std::string &body) {
  std::istringstream ss(body);
  int editorId, documentId, cursorPosition;
  std::string operations;
  ss >> editorId >> documentId >> cursorPosition;
  ss.ignore(1);
  getline(ss, operations);
  DocumentParams edit = { editorId, documentId, NULL, cursorPosition };
  edit.p3.str = (char*) operations.c_str();
  return ServerApplication::get_instance()->updateDocument(edit);
}
}
