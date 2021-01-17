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

 public:
  User();

  ~User();

  void setId(int newId);

  int getId();

  void setName(std::string newName);

  std::string getName();

  void setPassword(std::string newPassword);

  std::string getPassword();

  void addDocument(int id, std::string password);

  void deleteDocument(int id);

  Document getDocumentById(int id);

};

#endif //UTILS_INCLUDE_USER_H_
