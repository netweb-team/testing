#include "Change.h"

Change::Change() {
  number = 0;
  str = "";
}

Change::Change(const int& newNumber, const std::string& newString) {
  number = newNumber;
  str = newString;
}

bool Change::isRetain() const {
  return number >= 0 && str.empty();

}

bool Change::isInsert() const {
  return !str.empty() && number == 0;
}

bool Change::isErase() const {
  return str.empty() && number < 0;
}