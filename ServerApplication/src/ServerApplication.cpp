#include "ServerApplication.h"

std::pair<ApplicationErrors, std::string> ServerApplication::createDocument(int editorId, std::string documentName) {
    Document doc;
    try {
        docRepository->createDoc(doc);
    } catch(const std::exception& error) {
        std::cout << error.what() << std::endl;
        return std::make_pair(ApplicationErrors::failure, "Error with creating document");;
    };

    std::cout << "Document was successfully created with id " + std::to_string(doc.getId()) << std::endl;
    return std::make_pair(ApplicationErrors::success, std::to_string(doc.getId()));
}

std::pair<ApplicationErrors, std::string> ServerApplication::updateDocument(int editorId, int docId, int cursorPosition, std::string operations) {
    for (auto i = sessions.cbegin(); i != sessions.cend(); i++) {
        if ((*i)->getIdDocument() == docId) {
            // TODO:- From std::string to Operation
            std::shared_ptr<Operation> operation = std::shared_ptr<Operation>(new Operation());
            operation->setIdEditor(editorId);
            operation->makeOpFromString(operations);
            (*i)->manageOperation(editorId, operation);
            
            if ((*i)->getCounter() >= 5) {
                (*i)->setCounter(0);
                this->saveDocument(docId);
            }

            return std::make_pair(ApplicationErrors::success, "Change sent successfully");
        }
    }
    return std::make_pair(ApplicationErrors::failure, "Document is not open");
}

std::pair<ApplicationErrors, std::string> ServerApplication::getTextDocument(int docId) {
    for (auto i = sessions.cbegin(); i != sessions.cend(); i++) {
        if ((*i)->getIdDocument() == docId) {

            return std::make_pair(ApplicationErrors::success, (*i)->getDocumentText());
        }
    }
    return std::make_pair(ApplicationErrors::failure, "Document is not open");
}

std::pair<ApplicationErrors, std::string> ServerApplication::deleteDocument(int editorId, int docId) {
    for (auto i = sessions.cbegin(); i != sessions.cend(); i++) {
        if ((*i)->getIdDocument() == docId) {
            i = sessions.erase(i);
            return std::make_pair(ApplicationErrors::success, "Document was successfully deleted");
        }
    }
    return std::make_pair(ApplicationErrors::failure, "This document does not exist");
}

std::pair<ApplicationErrors, std::string> ServerApplication::readDocument(std::string userData, int docId) {
    return std::make_pair(ApplicationErrors::success, "Success");
}

std::pair<ApplicationErrors, std::string> ServerApplication::connectDocument(int editorId, int docId) {
    for (auto i = sessions.cbegin(); i != sessions.cend(); i++) {
        if ((*i)->getIdDocument() == docId) {
            (*i)->addEditor(editorId);
            return std::make_pair(ApplicationErrors::success, (*i)->getDocumentText());
        }
    }

    std::shared_ptr<Document> document;
    try {
        std::cout << docRepository->getById(docId)->getId() << " " << docRepository->getById(docId)->getText() << std::endl;
        document = docRepository->getById(docId);
    } catch(const std::exception& error) {
        std::cout << "Document was not created" << std::endl;
        return std::make_pair(ApplicationErrors::failure, "Document was not created");;
    };
    std::shared_ptr<EditorManager> editorManager(new EditorManager(document));
    std::shared_ptr<Session> session(new Session(document->getId(), editorManager));
    session->addEditor(editorId);
    this->addSession(session);
    return std::make_pair(ApplicationErrors::success, session->getDocumentText());
}

std::pair<ApplicationErrors, std::string> ServerApplication::disconnectDocument(int editorId, int docId) {
    for (auto i = sessions.begin(); i != sessions.end(); i++) {
        if ((*i)->getIdDocument() == docId) {
            (*i)->removeEditor(editorId);
//            if ((*i)->counterConnectedEditors() == 0) {
//                if (sessions.size() == 1) {
//                    sessions.clear();
//                } else {
//                    i = sessions.erase(i);
//                }
//                std::cout << "Session " << docId << " has been removed" << std::endl;
//            }
            return std::make_pair(ApplicationErrors::success, "Editor was successfully disconnected");
        }
    }
    return std::make_pair(ApplicationErrors::failure, "This session does not exist");
}

std::pair<ApplicationErrors, std::string> ServerApplication::saveDocument(int docId) {
    for (auto i = sessions.cbegin(); i != sessions.cend(); i++) {
        if ((*i)->getIdDocument() == docId) {
            // Some id editor
            Document document((*i)->getIdDocument(), (*i)->getDocumentText());
            docRepository->changeDoc(document);
            return std::make_pair(ApplicationErrors::success, "Document has been saved");
        }
    }
    return std::make_pair(ApplicationErrors::failure, "Document does not exist");
}

std::pair<ApplicationErrors, std::string> ServerApplication::loginUser(std::string userData) {
    return std::make_pair(ApplicationErrors::success, "User was successfully logined");
}

std::pair<ApplicationErrors, std::string> ServerApplication::registerUser(std::string userData) {
    return std::make_pair(ApplicationErrors::success, "User was successfully registred");
}

std::pair<ApplicationErrors, std::string> ServerApplication::logoutUser(std::string userData){
    return std::make_pair(ApplicationErrors::success, "User was successfully logouted");
}

std::pair<ApplicationErrors, std::string> ServerApplication::updateUser(std::string userData, std::string newUserData) {
    return std::make_pair(ApplicationErrors::success, "User was successfully updated");
}

void ServerApplication::addSession(std::shared_ptr<Session> session) {
    sessions.push_back(std::move(session));
}

std::shared_ptr<ServerApplication> ServerApplication::instance;
