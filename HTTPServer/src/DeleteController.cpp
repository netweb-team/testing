#include "server/controller/DeleteController.h"

namespace server {

ServerApplicationOut DeleteController::handle(const string &body) {
  std::istringstream is;
  int editorId, documentId;
  is >> editorId >> documentId;
  DocumentParams del = { editorId, documentId };
  return ServerApplication::get_instance()->deleteDocument(del);
}
}
