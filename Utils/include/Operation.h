#ifndef UTILS_INCLUDE_OPERATION_H_
#define UTILS_INCLUDE_OPERATION_H_

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <iostream>
#include <vector>

#include "Change.h"

class Operation {
private:
    size_t lenBeforeOperation;
    size_t lenAfterOperation;
    int revision;
    int idEditor;
    std::vector<Change> ops;

public:

    Operation();

    Operation(const Operation& newOp);

    Operation& operator=(const Operation& newOp);

    const int& getIdEditor() const;

    void setIdEditor(const int& newIdEditor);

    const int& getRevision() const;

    void setRevision(const int& newRevision);

    size_t getLenBeforeOperation() const;

    size_t getLenAfterOperation() const;

    void setLenBeforeOperation(const size_t& len);

    void setLenAfterOperation(const size_t& len);

    void addOperation(const Change& change);

    std::vector<Change> getChanges() const;

    // skip characters
    void retain(int newNumber);

    // insert a new string at the current position
    void insert(const std::string& newString);

    //delete characters
    void erase(int newNumber);

    bool isNoEffect() const;

    std::string applyToString(const std::string& anotherString) const;

    //for every string and pair of ops A, B must hold
    //apply(apply(S, A), B) = apply(S, compose(A, B))
    Operation compose (const Operation& operation2) const;

    //Transform takes two operations A and B that happened concurrently and
    // produces two operations A' and B' (in an array)
    std::vector<Operation> transform(const Operation& secondOp) const;

    void makeOpFromString(const std::string& opStr);

    std::string toString() const;
};

#endif //UTILS_INCLUDE_OPERATION_H_
