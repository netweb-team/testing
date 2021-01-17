#ifndef COMRED_UTILS_INCLUDE_CHANGE_H_
#define COMRED_UTILS_INCLUDE_CHANGE_H_

#include <iostream>

struct Change {
  int number;
  std::string str;

  Change();

  Change(const int& newNumber, const std::string& newString);

  Change& operator=(const Change& anotherChange) = default;

  bool isRetain() const;

  bool isInsert() const;

  bool isErase() const;
};

#endif //COMRED_UTILS_INCLUDE_CHANGE_H_
