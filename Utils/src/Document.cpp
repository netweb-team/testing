#include "Document.h"

void Document::setId(int newId) {
    if (newId >= 0) {
        id = newId;
    }
}

int Document::getId() const {
    return id;
}

std::string Document::getText() {
    return text;
}

void Document::updateText(std::shared_ptr<Operation> operation) {
    text = operation->applyToString(text);
}

void Document::addOwner(int idEditor) {
    for (int i = 0; i < owners.size(); i++) {
        if (owners[i] == idEditor) {
            return;
        }
    }
    owners.push_back(idEditor);
}

std::string Document::getName(void) {
    return name;
}

void Document::setName(const std::string& newName) {
    name = newName;
}