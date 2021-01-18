#ifndef UTILS_INCLUDE_USER_H_
#define UTILS_INCLUDE_USER_H_

#include <iostream>
#include <vector>

#include "Document.h"

class User {
 private:
  int Id;
  std::string name;
  std::string password;
  std::vector<int> idDocument;
  bool isLogin;

 public:
  User();

  ~User();

  void setId(int newId);

  int getId();

  void setName(const std::string& newName);

  std::string getName();

  void setPassword(const std::string& newPassword);

  std::string getPassword();

  void addDocument(int id);

  void deleteDocument(int id);

  bool getIsLogin(void);

  void setIsLogin(bool flag);

};

#endif //UTILS_INCLUDE_USER_H_
