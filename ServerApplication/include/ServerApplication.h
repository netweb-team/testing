#ifndef UNTITLED_SERVERAPPLICATION_H
#define UNTITLED_SERVERAPPLICATION_H

#include "ServerHeader.h"
#include "Session.h"
#include "../../DB/include/DBController.h"
#include "../../DB/include/DocumentRepository.h"
#include "../../DB/include/UserRepository.h"
#include "structs.h"

enum class ApplicationErrors {
    failure,
    success,
};

class BaseServerApplication {
public:
    BaseServerApplication() = default;
    virtual ~BaseServerApplication() { }
    virtual std::pair<ApplicationErrors, std::string> createDocument(const DocumentParams& prm) = 0;
    virtual std::pair<ApplicationErrors, std::string> updateDocument(const DocumentParams& prm) = 0;
    virtual std::pair<ApplicationErrors, std::string> getTextDocument(const DocumentParams& prm) = 0;
    virtual std::pair<ApplicationErrors, std::string> deleteDocument(const DocumentParams& prm) = 0;
    virtual std::pair<ApplicationErrors, std::string> connectDocument(const DocumentParams& prm) = 0;
    virtual std::pair<ApplicationErrors, std::string> saveDocument(const DocumentParams& prm) = 0;
    virtual std::pair<ApplicationErrors, std::string> loginUser(const UserParams& prm) = 0;
    virtual std::pair<ApplicationErrors, std::string> registerUser(const UserParams& prm) = 0;
    virtual std::pair<ApplicationErrors, std::string> logoutUser(const UserParams& prm) = 0;
    virtual std::pair<ApplicationErrors, std::string> updateUser(const UserParams& prm) = 0;

    virtual std::pair<ApplicationErrors, std::string> disconnectDocument(const DocumentParams& prm) = 0;

};

class ServerApplication: public BaseServerApplication {
protected:
    std::shared_ptr<DocumentRepositoryI> docRepository;
    std::shared_ptr<UserRepositoryI> userRepository;

    ServerApplication(): sessions(0) {
        auto controller = std::make_shared<DBController>();
        docRepository = std::make_shared<DocumentRepository>(controller);
        userRepository = std::make_shared<UserRepository>(controller);
    }
    ServerApplication(const ServerApplication&) = default;
    ServerApplication& operator=(ServerApplication&) = default;

public:
    static std::shared_ptr<ServerApplication> get_instance() {
        if (instance == nullptr) {
            instance =  std::shared_ptr<ServerApplication>(new ServerApplication);
        }
        return instance;
    }

    std::pair<ApplicationErrors, std::string> createDocument(const DocumentParams& prm) override;
    std::pair<ApplicationErrors, std::string> updateDocument(const DocumentParams& prm) override;
    std::pair<ApplicationErrors, std::string> getTextDocument(const DocumentParams& prm) override;
    std::pair<ApplicationErrors, std::string> deleteDocument(const DocumentParams& prm) override;
    std::pair<ApplicationErrors, std::string> connectDocument(const DocumentParams& prm) override;
    std::pair<ApplicationErrors, std::string> saveDocument(const DocumentParams& prm) override;
    std::pair<ApplicationErrors, std::string> loginUser(const UserParams& prm) override;
    std::pair<ApplicationErrors, std::string> registerUser(const UserParams& prm) override;
    std::pair<ApplicationErrors, std::string> logoutUser(const UserParams& prm) override;
    std::pair<ApplicationErrors, std::string> updateUser(const UserParams& prm) override;

    std::pair<ApplicationErrors, std::string> disconnectDocument(const DocumentParams& prm) override;

private:
    static std::shared_ptr<ServerApplication> instance;
    std::deque<std::shared_ptr<Session>> sessions;

//    std::shared_ptr<DBController> controller;

    void addSession(std::shared_ptr<Session> session);
};


#endif //UNTITLED_SERVERAPPLICATION_H
