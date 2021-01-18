#include <stdexcept>

#include "Operation.h"

Operation::Operation() : lenBeforeOperation(0), lenAfterOperation(0), revision(0), idEditor(-1) {
}

Operation::Operation(const Operation& newOp) {
    lenAfterOperation = newOp.getLenAfterOperation();
    lenBeforeOperation = newOp.getLenBeforeOperation();
    revision = newOp.revision;
    idEditor = newOp.idEditor;
    ops = newOp.ops;
}

Operation::Operation(int id, int revision, size_t before, size_t after, std::vector<Change> ops) {
    this->lenAfterOperation = after;
    this->lenBeforeOperation = before;
    this->revision = revision;
    this->idEditor = id;
    this->ops = ops;
}


Operation& Operation::operator=(const Operation& newOp) {
    lenAfterOperation = newOp.getLenAfterOperation();
    lenBeforeOperation = newOp.getLenBeforeOperation();
    revision = newOp.revision;
    idEditor = newOp.idEditor;
    ops = newOp.ops;
    return *this;
}

const int& Operation::getIdEditor() const {
    return idEditor;
}

void Operation::setIdEditor(const int& newIdEditor) {
    idEditor = newIdEditor;
}

const int& Operation::getRevision() const {
    return revision;
}

void Operation::setRevision(const int& newRevision) {
    revision = newRevision;
}

size_t Operation::getLenBeforeOperation() const {
    return lenBeforeOperation;
}

size_t Operation::getLenAfterOperation() const {
    return lenAfterOperation;
}

void Operation::setLenBeforeOperation(const size_t& len) {
    lenBeforeOperation = len;
}

void Operation::setLenAfterOperation(const size_t& len) {
    lenAfterOperation = len;
}

void Operation::addOperation(const Change& change) {
    ops.push_back(change);
}

std::vector<Change> Operation::getChanges() const {
    return ops;
}

void Operation::retain(int newNumber) {
    if (newNumber <= 0) {
        return;
    }

    lenBeforeOperation += newNumber;
    lenAfterOperation += newNumber;

    if (!ops.empty() && ops[ops.size() - 1].isRetain()) {
        // merge into one operation
        ops[ops.size() - 1].number += newNumber;
    } else {
        // create new op
        Change newChange = Change(newNumber, "");
        ops.push_back(newChange);
    }
}

void Operation::insert(const std::string& newString) {
    if (newString.empty()) {
        return;
    }

    lenAfterOperation += newString.size();

    if (ops.size() > 1) {
        if (ops[ops.size() - 1].isInsert()) {
            // merge insert op
            ops[ops.size() - 1].str += newString;
        } else if (ops[ops.size() - 1].isErase()) {
            // make that insert op always before erase
            if (ops.size() > 2 && ops[ops.size() - 2].isInsert()) {
                ops[ops.size() - 2].str += newString;
            } else {
                Change newChange = Change(0, newString);
                ops.push_back(ops[ops.size() - 1]);
                ops[ops.size() - 2] = newChange;
            }
        }
    } else {
        Change newChange = Change(0, newString);
        ops.push_back(newChange);
    }
}

void Operation::erase(int newNumber) {
    if (newNumber == 0) {
        return;
    } else if (newNumber > 0) {
        newNumber = -newNumber;
    }

    lenBeforeOperation -= newNumber;

    if (!ops.empty() && ops[ops.size() - 1].isErase()) {
        ops[ops.size() - 1].number += newNumber;
    } else {
        Change newChange = Change(newNumber, "");
        ops.push_back(newChange);
    }
}

bool Operation::isNoEffect() const {
    return ops.empty() || (ops.size() == 1 && ops[ops.size() - 1].isRetain());
}

std::string Operation::applyToString(const std::string& anotherString) const {
    if (anotherString.size() != lenBeforeOperation) {
        throw std::length_error("Length Before Operation must be equal string's length");
    }

    std::string newString;
    int stringIdx = 0;

    for (const auto& op : ops) {
        if (op.isRetain()) {
            if (stringIdx + op.number > anotherString.size()) {
                throw std::length_error("Can't retain more char than left in the string");
            }
            newString += anotherString.substr(stringIdx, op.number);
            stringIdx += op.number;
        } else if (op.isInsert()) {
            newString += op.str;
        } else {
            stringIdx -= op.number;
        }
    }

    if (stringIdx != anotherString.size()) {
      throw std::logic_error("Did not operate the whole string");
    }

    return newString;

}

Operation Operation::compose (const Operation& operation2) const {
    if (lenAfterOperation != operation2.getLenBeforeOperation()) {
        throw std::length_error("The base length of the second operation has to be the target length of the first operation");
    }
    Operation newOp;
    int idx1 = 0;
    int idx2 = 0;

    std::vector<Change> ops2 = operation2.getChanges();

    Change op1 = ops[idx1++];
    Change op2 = ops2[idx2++];
    size_t op1Size = ops.size();
    size_t op2Size = operation2.getChanges().size();

    while (true) {
        if (idx1 > op1Size && idx2 > op2Size) {
            break;
        }

        if (op1.isErase()) {
            newOp.erase(op1.number);
          if (idx1 < op1Size) {
            op1 = ops[idx1++];
          } else {
            idx1++;
          }
        }

        if (op2.isInsert()) {
            newOp.insert(op2.str);
          if (idx2 < op2Size) {
            op2 = ops2[idx2++];
          } else {
            idx2++;
          }
        }

        if (idx1 > op1Size || idx2 > op2Size) {
            throw std::logic_error("Cannot compose operations");
        }

        if (op1.isRetain() && op2.isRetain()) {

            if (op1.number > op2.number) {
                newOp.retain(op2.number);
                op1.number = op1.number - op2.number;
              if (idx2 < op2Size) {
                op2 = ops2[idx2++];
              } else {
                idx2++;
              }
            } else if (op1.number == op2.number) {
                newOp.retain(op1.number);
              if (idx1 < op1Size) {
                op1 = ops[idx1++];
              } else {
                idx1++;
              }
              if (idx2 < op2Size) {
                op2 = ops2[idx2++];
              } else {
                idx2++;
              }
            } else {
                newOp.retain(op1.number);
                op2.number = op2.number - op1.number;
              if (idx1 < op1Size) {
                op1 = ops[idx1++];
              } else {
                idx1++;
              }
            }

        } else if (op1.isInsert() && op2.isErase()) {

            if (op1.str.size() > -op2.number) {
                op1.str = op1.str.substr(-op2.number);
                op2 = ops2[idx2++];
            } else if (op1.str.size() == -op2.number) {
              if (idx1 < op1Size) {
                op1 = ops[idx1++];
              } else {
                idx1++;
              }
              if (idx2 < op2Size) {
                op2 = ops2[idx2++];
              } else {
                idx2++;
              }
            } else {
                op2.number = op2.number + op1.str.size();
              if (idx1 < op1Size) {
                op1 = ops[idx1++];
              } else {
                idx1++;
              }
            }

        } else if (op1.isInsert() && op2.isRetain()) {

            if (op1.str.size() > op2.number) {
                newOp.insert(op1.str.substr(0, op2.number));
                op1.str = op1.str.substr(op2.number);
              if (idx2 < op2Size) {
                op2 = ops2[idx2++];
              } else {
                idx2++;
              }
            } else if (op1.str.size() == op2.number) {
                newOp.insert(op1.str);
              if (idx1 < op1Size) {
                op1 = ops[idx1++];
              } else {
                idx1++;
              }
              if (idx2 < op2Size) {
                op2 = ops2[idx2++];
              } else {
                idx2++;
              }
            } else {
                newOp.insert(op1.str);
                op2.number = op2.number - op1.str.size();
              if (idx1 < op1Size) {
                op1 = ops[idx1++];
              } else {
                idx1++;
              }
            }

        } else if (op1.isRetain() && op2.isErase()) {

            if (op1.number > -op2.number) {
                newOp.erase(op2.number);
                op1.number = op1.number + op2.number;
              if (idx2 < op2Size) {
                op2 = ops2[idx2++];
              } else {
                idx2++;
              }
            } else if (op1.number == -op2.number) {
                newOp.erase(op2.number);
              if (idx1 < op1Size) {
                op1 = ops[idx1++];
              } else {
                idx1++;
              }
              if (idx2 < op2Size) {
                op2 = ops2[idx2++];
              } else {
                idx2++;
              }
            } else {
                newOp.erase(op1.number);
                op2.number = op2.number + op1.number;
              if (idx1 < op1Size) {
                op1 = ops[idx1++];
              } else {
                idx1++;
              }
            }
        }
    }
    return newOp;
}

std::vector<Operation> Operation::transform(const Operation& secondOp) const {
    if (lenBeforeOperation != secondOp.getLenBeforeOperation()) {
      throw std::length_error("Both operations have to have the same lenBeforeOperation");
    }

    Operation newOpForFirst;
    Operation newOpForSecond;
    int idx1 = 0;
    int idx2 = 0;

  std::vector<Change> ops2 = secondOp.getChanges();

    Change op1 = ops[idx1++];
    Change op2 = ops2[idx2++];

    size_t op1Size = ops.size();
    size_t op2Size = secondOp.getChanges().size();

    while (true) {
        if (idx1 > op1Size || idx2 > op2Size) {
            break;
        }

        if (op1.isInsert()) {
            newOpForFirst.insert(op1.str);
            newOpForSecond.retain(op1.str.size());
            if (idx1 < op1Size) {
                op1 = ops[idx1++];
            } else {
                idx1++;
            }
        }

        if (op2.isInsert()) {
            newOpForFirst.retain(op2.str.size());
            newOpForSecond.insert(op2.str);
            if (idx2 < op2Size) {
                op2 = ops2[idx2++];
            } else {
                idx2++;
            }
        }

        if (idx1 > op1Size && idx2 > op2Size) {
          break;
        }

        int minLen = 0;
        if (op1.isRetain() && op2.isRetain()) {

            if (op1.number > op2.number) {
                minLen = op2.number;
                op1.number = op1.number - op2.number;
              if (idx2 < op2Size) {
                op2 = ops2[idx2++];
              } else {
                idx2++;
              }
            } else if (op1.number == op2.number) {
                minLen = op2.number;
              if (idx1 < op1Size) {
                op1 = ops[idx1++];
              } else {
                idx1++;
              }
              if (idx2 < op2Size) {
                op2 = ops2[idx2++];
              } else {
                idx2++;
              }
            } else {
                minLen = op1.number;
                op2.number = op2.number - op1.number;
              if (idx1 < op1Size) {
                op1 = ops[idx1++];
              } else {
                idx1++;
              }
            }

            newOpForFirst.retain(minLen);
            newOpForSecond.retain(minLen);

        } else if (op1.isErase() && op2.isErase()) {

            if (-op1.number > -op2.number) {
                op1.number = op1.number - op2.number;
              if (idx2 < op2Size) {
                op2 = ops2[idx2++];
              } else {
                idx2++;
              }
            } else if (op1.number == op2.number) {
              if (idx1 < op1Size) {
                op1 = ops[idx1++];
              } else {
                idx1++;
              }
              if (idx2 < op2Size) {
                op2 = ops2[idx2++];
              } else {
                idx2++;
              }
            } else {
                op2.number = op2.number - op1.number;
              if (idx1 < op1Size) {
                op1 = ops[idx1++];
              } else {
                idx1++;
              }
            }

        } else if (op1.isErase() && op2.isRetain()) {

            if (-op1.number > op2.number) {
                minLen = -op2.number;
                op1.number = op1.number + op2.number;
              if (idx2 < op2Size) {
                op2 = ops2[idx2++];
              } else {
                idx2++;
              }
            } else if (-op1.number == op2.number) {
                minLen = op1.number;
              if (idx1 < op1Size) {
                op1 = ops[idx1++];
              } else {
                idx1++;
              }
              if (idx2 < op2Size) {
                op2 = ops2[idx2++];
              } else {
                idx2++;
              }
            } else {
                minLen = op1.number;
                op2.number = op2.number + op1.number;
              if (idx1 < op1Size) {
                op1 = ops[idx1++];
              } else {
                idx1++;
              }
            }

            newOpForFirst.erase(minLen);

        } else if (op1.isRetain() && op2.isErase()) {

            if (op1.number > -op2.number) {
                minLen = op2.number;
                op1.number = op1.number + op2.number;
              if (idx2 < op2Size) {
                op2 = ops2[idx2++];
              } else {
                idx2++;
              }
            } else if (op1.number == -op2.number) {
                minLen = -op1.number;
              if (idx1 < op1Size) {
                op1 = ops[idx1++];
              } else {
                idx1++;
              }
              if (idx2 < op2Size) {
                op2 = ops2[idx2++];
              } else {
                idx2++;
              }
            } else {
                minLen = -op1.number;
                op2.number = op2.number + op1.number;
              if (idx1 < op1Size) {
                op1 = ops[idx1++];
              } else {
                idx1++;
              }
            }

            newOpForSecond.erase(minLen);
        }
    }
    return std::vector<Operation>{newOpForFirst, newOpForSecond};
}

void Operation::makeOpFromString(const std::string& opStr) {
    std::vector<std::string> opsFromStr;
    boost::split(opsFromStr, opStr, boost::is_any_of(","));

    for (auto & op : opsFromStr) {
        if (std::isdigit(op[0])) {
            retain(std::stoi(op));
        } else if (op[0] == '-') {
            erase(std::stoi(op)) ;
        } else {
            insert(op);
        }
    }
}

std::string Operation::toString() const {
  std::string strOp;

  for (auto & op : ops) {
    if (op.number) {
      strOp += std::to_string(op.number);
      strOp.push_back(',');
    } else {
      strOp += op.str ;
      strOp.push_back(',');
    }
  }

  strOp.erase(strOp.size()-1);
  return strOp;
}
