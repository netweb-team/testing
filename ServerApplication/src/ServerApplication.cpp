#include "ServerApplication.h"

std::pair<ApplicationErrors, std::string> ServerApplication::createDocument(DocumentParams& prm) {
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

std::pair<ApplicationErrors, std::string> ServerApplication::updateDocument(DocumentParams& prm) {
    for (auto i = sessions.cbegin(); i != sessions.cend(); i++) {
        if ((*i)->getIdDocument() == prm.p2.num) {
            // TODO:- From std::string to Operation
            std::shared_ptr<Operation> operation = std::shared_ptr<Operation>(new Operation());
            operation->setIdEditor(prm.p1.num);
            operation->makeOpFromString(prm.p3.str);
            (*i)->manageOperation(prm.p1.num, operation);
            
            if ((*i)->getCounter() >= 5) {
                (*i)->setCounter(0);
                DocumentParams save = { prm.p2.num };
                this->saveDocument(save);
            }

            return std::make_pair(ApplicationErrors::success, "Change sent successfully");
        }
    }
    return std::make_pair(ApplicationErrors::failure, "Document is not open");
}

std::pair<ApplicationErrors, std::string> ServerApplication::getTextDocument(DocumentParams& prm) {
    for (auto i = sessions.cbegin(); i != sessions.cend(); i++) {
        if ((*i)->getIdDocument() == prm.p1.num) {

            return std::make_pair(ApplicationErrors::success, (*i)->getDocumentText());
        }
    }
    return std::make_pair(ApplicationErrors::failure, "Document is not open");
}

std::pair<ApplicationErrors, std::string> ServerApplication::deleteDocument(DocumentParams& prm) {
    for (auto i = sessions.cbegin(); i != sessions.cend(); i++) {
        if ((*i)->getIdDocument() == prm.p1.num) {
            i = sessions.erase(i);
            return std::make_pair(ApplicationErrors::success, "Document was successfully deleted");
        }
    }
    return std::make_pair(ApplicationErrors::failure, "This document does not exist");
}

std::pair<ApplicationErrors, std::string> ServerApplication::connectDocument(DocumentParams& prm) {
    for (auto i = sessions.cbegin(); i != sessions.cend(); i++) {
        if ((*i)->getIdDocument() == prm.p2.num) {
            (*i)->addEditor(prm.p1.num);
            return std::make_pair(ApplicationErrors::success, (*i)->getDocumentText());
        }
    }

    std::shared_ptr<Document> document;
    try {
        std::cout << docRepository->getById(prm.p2.num)->getId() << " " << docRepository->getById(prm.p2.num)->getText() << std::endl;
        document = docRepository->getById(prm.p2.num);
    } catch(const std::exception& error) {
        std::cout << "Document was not created" << std::endl;
        return std::make_pair(ApplicationErrors::failure, "Document was not created");;
    };
    std::shared_ptr<EditorManager> editorManager(new EditorManager(document));
    std::shared_ptr<Session> session(new Session(document->getId(), editorManager));
    session->addEditor(prm.p1.num);
    this->addSession(session);
    return std::make_pair(ApplicationErrors::success, session->getDocumentText());
}

std::pair<ApplicationErrors, std::string> ServerApplication::disconnectDocument(DocumentParams& prm) {
    for (auto i = sessions.begin(); i != sessions.end(); i++) {
        if ((*i)->getIdDocument() == prm.p2.num) {
            (*i)->removeEditor(prm.p1.num);
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

std::pair<ApplicationErrors, std::string> ServerApplication::saveDocument(DocumentParams& prm) {
    for (auto i = sessions.cbegin(); i != sessions.cend(); i++) {
        if ((*i)->getIdDocument() == prm.p1.num) {
            // Some id editor
            Document document((*i)->getIdDocument(), (*i)->getDocumentText());
            docRepository->changeDoc(document);
            return std::make_pair(ApplicationErrors::success, "Document has been saved");
        }
    }
    return std::make_pair(ApplicationErrors::failure, "Document does not exist");
}

std::pair<ApplicationErrors, std::string> ServerApplication::loginUser(UserParams& prm) {
    return std::make_pair(ApplicationErrors::success, "User was successfully logined");
}

std::pair<ApplicationErrors, std::string> ServerApplication::registerUser(UserParams& prm) {
    return std::make_pair(ApplicationErrors::success, "User was successfully registred");
}

std::pair<ApplicationErrors, std::string> ServerApplication::logoutUser(UserParams& prm){
    return std::make_pair(ApplicationErrors::success, "User was successfully logouted");
}

std::pair<ApplicationErrors, std::string> ServerApplication::updateUser(UserParams& prm) {
    return std::make_pair(ApplicationErrors::success, "User was successfully updated");
}

void ServerApplication::addSession(std::shared_ptr<Session> session) {
    sessions.push_back(std::move(session));
}

std::shared_ptr<ServerApplication> ServerApplication::instance;
