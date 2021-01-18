#include "server/controller/ConnectController.h"

namespace server {
ServerApplicationOut ConnectController::handle(const string &body) {
  std::istringstream is(body);
  int editorId, documentId;
  is >> editorId >> documentId;
  DocumentParams connect = { editorId, documentId };
  return ServerApplication::get_instance()->connectDocument(connect);
}
}
