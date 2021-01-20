#include "ServerApplication.h"

std::pair<ApplicationErrors, std::string> ServerApplication::createDocument(const DocumentParams& prm) {
    Document doc;
    doc.setName(prm.p2.str);
    try {
        docRepository->create(doc);
    } catch(const std::exception& error) {
        std::cout << error.what() << std::endl;
        return std::make_pair(ApplicationErrors::failure, "Error with creating document");;
    };

    std::cout << "Document was successfully created with id " + std::to_string(doc.getId()) << std::endl;
    return std::make_pair(ApplicationErrors::success, std::to_string(doc.getId()));
}

std::pair<ApplicationErrors, std::string> ServerApplication::updateDocument(const DocumentParams& prm) {
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

std::pair<ApplicationErrors, std::string> ServerApplication::getTextDocument(const DocumentParams& prm) {
    for (auto i = sessions.cbegin(); i != sessions.cend(); i++) {
        if ((*i)->getIdDocument() == prm.p1.num) {

            return std::make_pair(ApplicationErrors::success, (*i)->getDocumentText());
        }
    }
    return std::make_pair(ApplicationErrors::failure, "Document is not open");
}

std::pair<ApplicationErrors, std::string> ServerApplication::deleteDocument(const DocumentParams& prm) {
    for (auto i = sessions.cbegin(); i != sessions.cend(); i++) {
        if ((*i)->getIdDocument() == prm.p1.num) {
            try
            {
                Document document((*i)->getIdDocument(), (*i)->getDocumentText());
                docRepository->deleteD(document);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                return std::make_pair(ApplicationErrors::failure, "Error with document delete");
            }
            i = sessions.erase(i);
            return std::make_pair(ApplicationErrors::success, "Document was successfully deleted");
        }
    }
    return std::make_pair(ApplicationErrors::failure, "This document does not exist");
}

std::pair<ApplicationErrors, std::string> ServerApplication::connectDocument(const DocumentParams& prm) {
    for (auto i = sessions.cbegin(); i != sessions.cend(); i++) {
        if ((*i)->getIdDocument() == prm.p2.num) {
            (*i)->addEditor(prm.p1.num);
            return std::make_pair(ApplicationErrors::success, (*i)->getDocumentText());
        }
    }

    std::shared_ptr<Document> document;
    try {
        std::cout << docRepository->getId(prm.p2.num)->getId() << " " << docRepository->getId(prm.p2.num)->getText() << std::endl;
        document = docRepository->getId(prm.p2.num);
    } catch(const std::exception& error) {
        std::cout << "Document was not created" << std::endl;
        return std::make_pair(ApplicationErrors::failure, "Document was not created");
    }
    std::shared_ptr<EditorManager> editorManager(new EditorManager(document));
    std::shared_ptr<Session> session(new Session(document->getId(), editorManager));
    session->addEditor(prm.p1.num);
    this->addSession(session);
    return std::make_pair(ApplicationErrors::success, session->getDocumentText());
}

std::pair<ApplicationErrors, std::string> ServerApplication::disconnectDocument(const DocumentParams& prm) {
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

std::pair<ApplicationErrors, std::string> ServerApplication::saveDocument(const DocumentParams& prm) {
    for (auto i = sessions.cbegin(); i != sessions.cend(); i++) {
        if ((*i)->getIdDocument() == prm.p1.num) {
            // Some id editor
            try
            {
                Document document((*i)->getIdDocument(), (*i)->getDocumentText());
                docRepository->change(document);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                return std::make_pair(ApplicationErrors::failure, "Error with document save");
            }
            return std::make_pair(ApplicationErrors::success, "Document has been saved");
        }
    }
    return std::make_pair(ApplicationErrors::failure, "Document does not exist");
}

std::pair<ApplicationErrors, std::string> ServerApplication::loginUser(const UserParams& prm) {
    User user;
    user.setName(prm.p1.str);
    user.setPassword(prm.p2.str);
    try {
        userRepository->check(user);
    } catch(const std::exception& error) {
        std::cout << error.what() << std::endl;
        return std::make_pair(ApplicationErrors::failure, "Error with user");
    };

    user.setIsLogin(true);
    try {
        userRepository->update(user);
    } catch(const std::exception& error) {
        std::cout << error.what() << std::endl;
        return std::make_pair(ApplicationErrors::failure, "Cannot login user");
    };
    return std::make_pair(ApplicationErrors::success, std::to_string(user.getId()));
}

std::pair<ApplicationErrors, std::string> ServerApplication::registerUser(const UserParams& prm) {
    if (!strcmp(prm.p2.str, "") || !strcmp(prm.p1.str, ""))
        return std::make_pair(ApplicationErrors::failure, "Error with user");

    User user;
    user.setName(prm.p1.str);
    user.setPassword(prm.p2.str);
    //cout << user.getName() << endl << user.getPassword() << endl;
    try {
        userRepository->create(user);
    } catch(const std::exception& error) {
        std::cout << error.what() << std::endl;
        return std::make_pair(ApplicationErrors::failure, "Error with creating user");
    }

    std::cout << "User was successfully created with id " + std::to_string(user.getId()) << std::endl;
    return std::make_pair(ApplicationErrors::success, std::to_string(user.getId()));
}

std::pair<ApplicationErrors, std::string> ServerApplication::logoutUser(const UserParams& prm) {
    shared_ptr<User> user;
    try {
        user = userRepository->get(prm.p1.num);
    } catch(const std::exception& error) {
        std::cout << error.what() << std::endl;
        return std::make_pair(ApplicationErrors::failure, "Error with user");
    };
    user->setIsLogin(false);
    try {
        userRepository->update(*user);
    } catch(const std::exception& error) {
        std::cout << error.what() << std::endl;
        return std::make_pair(ApplicationErrors::failure, "Cannot logout user");
    };
    return std::make_pair(ApplicationErrors::success, "User was successfully logouted");
}

std::pair<ApplicationErrors, std::string> ServerApplication::updateUser(const UserParams& prm) {
    if (!strcmp(prm.p2.str, ""))
        return std::make_pair(ApplicationErrors::failure, "Error with user");

    shared_ptr<User> user;
    try {
        user = userRepository->get(prm.p1.num);
    } catch(const std::exception& error) {
        std::cout << error.what() << std::endl;
        return std::make_pair(ApplicationErrors::failure, "Error with user");
    };

    string userData = string(prm.p2.str);
    int spacePos = userData.find(" ");
    user->setName(userData.substr(0, spacePos));
    user->setPassword(userData.substr(spacePos + 1));
    try {
        userRepository->update(*user);
    } catch(const std::exception& error) {
        std::cout << error.what() << std::endl;
        return std::make_pair(ApplicationErrors::failure, "Cannot update user");
    };
    return std::make_pair(ApplicationErrors::success, "User was successfully updated");
}

void ServerApplication::addSession(std::shared_ptr<Session> session) {
    sessions.push_back(std::move(session));
}

std::shared_ptr<ServerApplication> ServerApplication::instance;
