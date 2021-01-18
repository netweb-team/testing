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
    DocumentBuilder* setPass(std::string pass);
    Document* build();
    
    int id;
    std::string text;
    std::string password;
};

class DocumentMother {
public:
    static DocumentBuilder* one();
    static DocumentBuilder* two();
};

#endif //DOCUMENT_BUILDER_H_
