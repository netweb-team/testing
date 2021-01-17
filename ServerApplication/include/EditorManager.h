#ifndef UNTITLED_EDITORMANAGER_H
#define UNTITLED_EDITORMANAGER_H

#include "ServerHeader.h"

#include "../../Utils/include/Document.h"
#include "../../Utils/include/Operation.h"

class Editor;

class BaseEditorManager {
public:
    virtual ~BaseEditorManager() = default;
    virtual Operation changeOperationRelativelyOthers(Operation operation) = 0;
    virtual void addOperationToLog(std::shared_ptr<Operation> operation) = 0;
    virtual void changeServerDocument() = 0;
    virtual void sendOperationToClient(Operation operation) = 0;
    virtual void sendAnswerToOriginalClient(Operation operation) = 0;
    virtual void addOperationToQueue(std::shared_ptr<Operation> operation) = 0;
    virtual int getLastRevision() = 0;
};

class EditorManager: public BaseEditorManager {
public:
    EditorManager(std::shared_ptr<Document> document): document(std::make_shared<Document>(document)), logRevision(0),
                                                       waitingForProcessing(), editors(0) {
//        waitingForProcessing
//        std::string line1 = "hello";
//        std::shared_ptr<Operation> operation1 = std::shared_ptr<Operation>(new Operation());
//        operation1->setIdEditor(-1);
//        operation1->makeOpFromString(line1);
//        waitingForProcessing.push_back(operation1);
//
//        std::string line2 = " world";
//        std::shared_ptr<Operation> operation2 = std::shared_ptr<Operation>(new Operation());
//        operation2->setIdEditor(-1);
//        operation2->makeOpFromString(line2);
//        waitingForProcessing.push_back(operation2);
    }

    EditorManager(std::shared_ptr<EditorManager> editorManager): document(editorManager->document), logRevision(editorManager->logRevision), waitingForProcessing(editorManager->waitingForProcessing), editors(0)
    { }

    ~EditorManager() {
        logRevision.clear();
        waitingForProcessing.clear();
    }

    Operation changeOperationRelativelyOthers(Operation operation) override;
    void addOperationToLog(std::shared_ptr<Operation> operation) override;
    void changeServerDocument() override;
    void sendOperationToClient(Operation operation) override;
    void sendAnswerToOriginalClient(Operation operation) override;

    // Delegate Method
    void addOperationToQueue(std::shared_ptr<Operation> operation) override;

    int getLastRevision() override;
    std::string getCurrentTextOfDocument();
    std::shared_ptr<Document> getCurrentVersionOfDocument();
    void addEeditor(const std::shared_ptr<Editor>& editor);

private:
    std::shared_ptr<Document> document;
    std::vector<std::shared_ptr<Operation>> logRevision;
    std::deque<std::shared_ptr<Operation>> waitingForProcessing;
    std::vector<std::weak_ptr<Editor>> editors;
};

#endif //UNTITLED_EDITORMANAGER_H
