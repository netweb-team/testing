#ifndef OPERATION_BUILDER_H_
#define OPERATION_BUILDER_H_

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <iostream>
#include <vector>

#include "Change.h"
#include "Document.h"
#include "Operation.h"
#include "User.h"

class UserBuilder {
public:
    UserBuilder();
    ~UserBuilder();
    
    UserBuilder* setId(int Id);
    UserBuilder* setName(std::string name);
    UserBuilder* setPassword(std::string pass);
    UserBuilder* addIdDocument(int idDoc);
    UserBuilder* setIsLogin(bool flag);
    User* build();
    
    int Id;
    std::string name;
    std::string password;
    std::vector<int> idDocument;
    bool isLogin;
};

class UserMother {
public:
    static UserBuilder* one();
    static UserBuilder* two();
};

#endif //OPERATION_BUILDER_H_
