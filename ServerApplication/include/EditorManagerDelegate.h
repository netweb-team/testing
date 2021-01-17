#ifndef UNTITLED_EDITORMANAGERDELEGATE_H
#define UNTITLED_EDITORMANAGERDELEGATE_H

#include "../../Utils/include/Operation.h"

class EditorManagerDelegate {
public :
    virtual void addOperationToQueue(Operation operation) = 0;
};

#endif //UNTITLED_EDITORMANAGERDELEGATE_H
