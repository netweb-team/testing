#ifndef UTILS_INCLUDE_DOCUMENT_H_
#define UTILS_INCLUDE_DOCUMENT_H_

#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "Operation.h"

class Document{
public:
    Document() {}
    Document(int idDocument,
             const std::string& textDocument): id(idDocument),
                                               name(std::string()),
                                               text{textDocument} { };

    Document(int idDocument, std::string&& textDocument):
            id(idDocument),
            name(std::string()),
            text{std::move(textDocument)} { };

    Document(std::shared_ptr<Document>& document) :
            id(document->getId()), text(document->getText()),
            name(document->getName()) {}

    ~Document() {
    }

    int getId() const;

    std::string getText();

    void updateText(std::shared_ptr<Operation> operation);

    void setId(int newId);

    void addOwner(int idEditor);

    std::string getName(void);

    void setName(const std::string& newName);

private:
    int id;
    std::string text;
    std::string name;
    std::vector<int> owners;
};

#endif //UTILS_INCLUDE_DOCUMENT_H_
