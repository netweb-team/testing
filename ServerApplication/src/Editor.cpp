#include "Editor.h"

Operation Editor::submitToServer(std::shared_ptr<Operation> operation) {
    if (!editorManager.expired()) {
        editorManager.lock()->addOperationToQueue(operation);
    }
    return Operation();
}

Operation Editor::makeNewOperation() {
    return Operation();
}

void Editor::changeDocument(std::shared_ptr<Operation> operation) {
    document->updateText(operation);
    std::cout << "\n---------------------" << std::endl;
    std::cout << "\nLocal change from request " << std::endl;
    std::cout << "EDITOR[" << id << "] DOCUMENT: " << document->getText() << std::endl;

    waitingForSendOperation.push_back(operation);

    Operation initPop = *waitingForSendOperation.front();
    waitingForSendOperation.pop_front();

    while(!waitingForSendOperation.empty()) {
        initPop = initPop.compose(*waitingForSendOperation.front());
        waitingForSendOperation.pop_front();
    }

    std::shared_ptr<Operation> oper = std::make_shared<Operation>(initPop);
    //std::cout << "EDTIOR " << id << ">" << oper->getChanges()[0].str << "<" << std::endl;
    if (sendedOperation == nullptr) {
        sendedOperation = oper;
        auto operationToSend = std::make_shared<Operation>(*oper);
        operationToSend->setIdEditor(operation->getIdEditor());
        submitToServer(operationToSend);
//        submitToServer(oper);
    } else {
        waitingForSendOperation.push_back(oper);
    }
}

// Observers Methods
void Editor::hearChangesFromServer(std::shared_ptr<Operation> operation) {
    // TODO: Make transform and compose waitingForSendOperation

    if (sendedOperation != nullptr) {
        auto transformFromOperation = operation->transform(*sendedOperation);
        document->updateText(std::make_shared<Operation>(transformFromOperation[0]));
        *sendedOperation = transformFromOperation[1];
        sendedOperation->setRevision(sendedOperation->getRevision() + 1);
    } else {
        document->updateText(operation);
    }

    for (auto iter = waitingForSendOperation.cbegin(); iter != waitingForSendOperation.cend(); iter++) {
        (*iter)->setRevision((*iter)->getRevision() + 1);
    }

    // TODO: Send to client
    std::cout << "\nChange from server " << operation->getIdEditor() << std::endl;
    std::cout << "EDITOR[" << id << "] DOCUMENT: " << document->getText() << std::endl;
}

void Editor::hearSubmitFromServer() {
    sendedOperation = nullptr;
    syncRevision++;

    // waitingForSendOperation
    for (auto iter = waitingForSendOperation.cbegin(); iter != waitingForSendOperation.cend(); iter++) {
        (*iter)->setRevision((*iter)->getRevision() + 1);
    }

    // TODO: Send to client
    std::cout << "\nSubmit from server " << std::endl;
    std::cout << "EDITOR[" << id << "] DOCUMENT: " << document->getText() << std::endl;
}

int Editor::getId() {
    return id;
}
