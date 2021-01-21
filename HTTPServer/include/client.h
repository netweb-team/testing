#ifndef CLIENT_INCLUDE_CLIENT_H
#define CLIENT_INCLUDE_CLIENT_H

#include "httpClient.h"

namespace client {
enum class ClientErrors {
  success,
  failure
};

using ClientOut = std::pair<ClientErrors, std::string>;

class Client {
public:
  Client(std::string host, std::string port) : rs(host, port) {}

  ClientOut update(int editorId, int docId, int cursorPos, const std::string &operations);

  ClientOut connect(int editorId, int docId);

  ClientOut create(int editorId, const std::string &documentName);

  ClientOut getTextDocument(int docId);

  ClientOut disconnect(int editorId, int docId);

  ClientOut signup(const std::string& username, const std::string& password);

  ClientOut login(const std::string& username, const std::string& password);

  ClientOut logout(int userId);

private:
  ClientOut _getResponse(const http::verb &method, const std::string &target, std::string body);

private:
  RequestSender rs;
};
}

#endif
