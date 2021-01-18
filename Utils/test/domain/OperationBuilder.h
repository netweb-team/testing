#ifndef UTILS_INCLUDE_OPERATION_H_
#define UTILS_INCLUDE_OPERATION_H_

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <iostream>
#include <vector>

#include "Change.h"

class Operation {
private:
    

public:

    Operation();
    size_t lenBeforeOperation;
    size_t lenAfterOperation;
    int revision;
    int idEditor;
    std::vector<Change> ops;

};

#endif //UTILS_INCLUDE_OPERATION_H_
