#ifndef UNTITLED_SESSION_H
#define UNTITLED_SESSION_H

#include "Editor.h"

class BaseSession {
public:
    virtual ~BaseSession() = default;
    virtual void manageOperation(int idEditor, std::shared_ptr<Operation> operation) = 0;
    virtual std::vector<Operation> sendToServerBufOfhanger() = 0;
    virtual void addEditor(int idEditor) = 0;
    virtual void removeEditor(int idEditor) = 0;
};

class Session: public BaseSession {
public:
    Session(const Session&) = delete;
    Session(Session&&) = delete;
    Session(int idDocument, std::shared_ptr<EditorManager> editorManager): counter(0),
                            editorManager(std::move(editorManager)), idDocument(idDocument),
                            editors(0), bufferOfChanges(0)
    { }

    ~Session() { }

    void manageOperation(int idEditor, std::shared_ptr<Operation> operation) override;
    std::vector<Operation> sendToServerBufOfhanger() override;

    void addEditor(int idEditor) override;
    void removeEditor(int idEditor) override;

    int getIdDocument();
    std::string getDocumentText();

    const int getCounter();
    void setCounter(const int& num);

    const int counterConnectedEditors();

private:
    int counter;

    int idDocument;
    std::shared_ptr<EditorManager> editorManager;
    std::deque<std::shared_ptr<Editor>> editors;
    std::vector<Operation> bufferOfChanges;
};

#endif //UNTITLED_SESSION_H
