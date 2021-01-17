#include "Session.h"

void Session::manageOperation(int idEditor, std::shared_ptr<Operation> operation) {
    for (auto iter = editors.cbegin(); iter != editors.cend(); iter++) {
        if ((*iter)->getId() == idEditor) {
            (*iter)->changeDocument(operation);
            counter++;
            break;
        }
    }
}

std::vector<Operation> Session::sendToServerBufOfhanger() {
    return std::vector<Operation>();
}

void Session::addEditor(int idEditor) {
    for (auto iter = editors.cbegin(); iter != editors.cend(); iter++) {
        if ((*iter)->getId() == idEditor) {
            return;
        }
    }
    std::shared_ptr<Editor> newEditor(new Editor(idEditor, editorManager));
    editors.push_back(newEditor);
    editorManager->addEeditor(newEditor);
    std::cout<< "Added editor with id: " << editors.back()->getId() << std::endl;
}

void Session::removeEditor(int idEditor) {
    for (auto iter = editors.begin(); iter != editors.end(); iter++) {
        if ((*iter)->getId() == idEditor) {
            if (editors.size() == 1) {
                editors.clear();
            } else {
                iter = editors.erase(iter);
            }
            std::cout<< "Removed editor with id: " << idEditor << std::endl;
            return;
        }
    }
    std::cout<< "Session[" << idDocument << "] " << "has no " << "Editor with id: " << idEditor << std::endl;
}


int Session::getIdDocument() {
    return idDocument;
}

std::string Session::getDocumentText() {
    return editorManager->getCurrentTextOfDocument();
}

const int Session::getCounter() {
    return counter;
}

void Session::setCounter(const int& num) {
    if (num >= 0) {
        counter = num;
    }
}

const int Session::counterConnectedEditors() {
    return editors.size();
}
