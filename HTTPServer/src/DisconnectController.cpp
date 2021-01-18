#include "server/controller/DisconnectController.h"

namespace server {
ServerApplicationOut DisconnectController::handle(const std::string &body) {
  std::istringstream is(body);
  int editorId, documentId;
  is >> editorId >> documentId;
  DocumentParams disconnect = { editorId, documentId };
  return ServerApplication::get_instance()->disconnectDocument(disconnect);
}
}
