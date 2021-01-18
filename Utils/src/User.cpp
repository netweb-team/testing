#include "User.h"

User::User() {

}

User::~User() {

}

void User::setId(int newId) {
  Id = newId;
}

int User::getId() {
  return Id;
}

void User::setName(const std::string& newName) {
  name = newName;
}

std::string User::getName() {
  return name;
}

void User::setPassword(const std::string& newPassword) {
  password = newPassword;
}

std::string User::getPassword() {
  return password;
}

void User::addDocument(int id) {
  idDocument.push_back(id);
}

void User::deleteDocument(int id) {
  return;
}

bool User::getIsLogin(void) {
  return isLogin;
}

void User::setIsLogin(bool flag) {
  isLogin = flag;
}
