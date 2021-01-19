#ifndef UNTITLED_SERVERAPPLICATION_H
#define UNTITLED_SERVERAPPLICATION_H

#include "ServerHeader.h"
#include "Session.h"
#include "../../DB/include/DBController.h"
#include "../../DB/include/DocumentRepository.h"
#include "../../DB/include/UserRepository.h"

enum class ApplicationErrors {
    failure,
    success,
};

union param
{
    int num;
    char *str;
};

struct DocumentParams 
{
    param p1;
    param p2;
    param p3;
    param p4;
};

struct UserParams
{
    param p1;
    param p2;
};

class BaseServerApplication {
public:
    BaseServerApplication() = default;
    virtual ~BaseServerApplication() { }
    virtual std::pair<ApplicationErrors, std::string> createDocument(DocumentParams& prm) = 0;
    virtual std::pair<ApplicationErrors, std::string> updateDocument(DocumentParams& prm) = 0;
    virtual std::pair<ApplicationErrors, std::string> getTextDocument(DocumentParams& prm) = 0;
    virtual std::pair<ApplicationErrors, std::string> deleteDocument(DocumentParams& prm) = 0;
    virtual std::pair<ApplicationErrors, std::string> connectDocument(DocumentParams& prm) = 0;
    virtual std::pair<ApplicationErrors, std::string> saveDocument(DocumentParams& prm) = 0;
    virtual std::pair<ApplicationErrors, std::string> loginUser(UserParams& prm) = 0;
    virtual std::pair<ApplicationErrors, std::string> registerUser(UserParams& prm) = 0;
    virtual std::pair<ApplicationErrors, std::string> logoutUser(UserParams& prm) = 0;
    virtual std::pair<ApplicationErrors, std::string> updateUser(UserParams& prm) = 0;

    virtual std::pair<ApplicationErrors, std::string> disconnectDocument(DocumentParams& prm) = 0;

};

class ServerApplication: public BaseServerApplication {
protected:
    std::shared_ptr<DocumentRepository> docRepository;
    std::shared_ptr<UserRepository> userRepository;

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
            instance =  std::shared_ptr<ServerApplication>(new ServerApplication) ;
        }
        return instance;
    }

    std::pair<ApplicationErrors, std::string> createDocument(DocumentParams& prm) override;
    std::pair<ApplicationErrors, std::string> updateDocument(DocumentParams& prm) override;
    std::pair<ApplicationErrors, std::string> getTextDocument(DocumentParams& prm) override;
    std::pair<ApplicationErrors, std::string> deleteDocument(DocumentParams& prm) override;
    std::pair<ApplicationErrors, std::string> connectDocument(DocumentParams& prm) override;
    std::pair<ApplicationErrors, std::string> saveDocument(DocumentParams& prm) override;
    std::pair<ApplicationErrors, std::string> loginUser(UserParams& prm) override;
    std::pair<ApplicationErrors, std::string> registerUser(UserParams& prm) override;
    std::pair<ApplicationErrors, std::string> logoutUser(UserParams& prm) override;
    std::pair<ApplicationErrors, std::string> updateUser(UserParams& prm) override;

    std::pair<ApplicationErrors, std::string> disconnectDocument(DocumentParams& prm) override;

private:
    static std::shared_ptr<ServerApplication> instance;
    std::deque<std::shared_ptr<Session>> sessions;

//    std::shared_ptr<DBController> controller;

    void addSession(std::shared_ptr<Session> session);
};


#endif //UNTITLED_SERVERAPPLICATION_H
