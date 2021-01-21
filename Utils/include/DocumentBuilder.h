#ifndef DOCUMENT_BUILDER_H_
#define DOCUMENT_BUILDER_H_

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "Document.h"
#include "Operation.h"

class DocumentBuilder {
public:
    DocumentBuilder();
    ~DocumentBuilder();
    
    DocumentBuilder* setId(int newId);
    DocumentBuilder* updateText(std::shared_ptr<Operation> operation);
    DocumentBuilder* setName(std::string pass);
    Document* build();
    
    int id;
    std::string text;
    std::string name;
};

class DocumentMother {
public:
    static DocumentBuilder* one();
    static DocumentBuilder* two();
    static DocumentBuilder* three();
    static DocumentBuilder* four();
};

#endif //DOCUMENT_BUILDER_H_
