#include "EditorManager.h"
#include "Editor.h"

Operation EditorManager::changeOperationRelativelyOthers(Operation operation) {
    return Operation();
}

void EditorManager::addOperationToLog(std::shared_ptr<Operation> operation) {


}

void EditorManager::changeServerDocument() {
    while(!waitingForProcessing.empty()) {

        auto operation = waitingForProcessing.front();
        waitingForProcessing.pop_front();
        std::cout << ">>" << (operation)->getChanges()[0].number << std::endl;

        for (auto iter = waitingForProcessing.begin(); iter != waitingForProcessing.end(); iter++) {
            //iter = operation->transform(*iter)[1];
            if ((*iter)->getRevision() >= operation->getRevision()) {

                int revision = (*iter)->getRevision() + 1;
                int idEditor = (*iter)->getIdEditor();

                *(iter->get()) = operation->transform(*(iter->get()))[1];

//                std::cout << ">>" << (iter->get())->getChanges()[0].str << " " << (iter->get())->getChanges()[1].str << std::endl;

                (*iter)->setRevision(revision);
                (*iter)->setIdEditor(idEditor);
            }
        }

        document->updateText(operation);

        std::cout << "\nSERVER[" << document->getId() << "] DOCUMENT: " << document->getText() << std::endl;
        for (auto iter = editors.cbegin(); iter != editors.cend(); iter++) {
            if ((*iter).expired() == 0) {
                if (operation->getIdEditor() == (*iter).lock()->getId()) {
                    (*iter).lock()->hearSubmitFromServer();
                } else {
                    (*iter).lock()->hearChangesFromServer(operation);
                }
            }
        }

        std::cout << "\n---------------------" << std::endl;
    }

//
//    logRevision.push_back(operation);
}

void EditorManager::sendOperationToClient(Operation operation) {

}

void EditorManager::sendAnswerToOriginalClient(Operation operation) {

}

void EditorManager::addOperationToQueue(std::shared_ptr<Operation> operation)  {
    waitingForProcessing.push_back(operation);
    changeServerDocument();
}

int EditorManager::getLastRevision() {
    return 0;
}

std::string EditorManager::getCurrentTextOfDocument() {
    return document->getText();
}

std::shared_ptr<Document> EditorManager::getCurrentVersionOfDocument() {
    return std::make_shared<Document>(document);
}

void EditorManager::addEeditor(const std::shared_ptr<Editor>& editor) {
    std::weak_ptr<Editor> weakEditor(editor);
    editors.push_back(weakEditor);
}
