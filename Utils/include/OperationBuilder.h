#ifndef OPERATION_BUILDER_H_
#define OPERATION_BUILDER_H_

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <iostream>
#include <vector>

#include "Change.h"
#include "Document.h"
#include "Operation.h"

class OperationBuilder {
public:
    OperationBuilder();
    ~OperationBuilder();
    
    OperationBuilder* setlenBef(size_t before);
    OperationBuilder* setlenAft(size_t after);
    OperationBuilder* setId(int idEditor);
    OperationBuilder* setRev(int revision);
    Operation* build();
    
    size_t lenBeforeOperation;
    size_t lenAfterOperation;
    int revision;
    int idEditor;
    std::vector<Change> ops;
};

class OperationMother {
public:
    static OperationBuilder* one();
    static OperationBuilder* two();
};

#endif //OPERATION_BUILDER_H_
