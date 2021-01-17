#include "server/controller/ConnectController.h"

namespace server {
ServerApplicationOut ConnectController::handle(const string &body) {
  std::istringstream is(body);
  int editorId, documentId;
  is >> editorId >> documentId;
  return ServerApplication::get_instance()->connectDocument(editorId, documentId);
}
}
