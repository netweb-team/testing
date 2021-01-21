#include "UserBuilder.h"

UserBuilder::UserBuilder() {
    this->Id = 0;
    this->name = "test";
    this->password = "test";
    //this->idDocument;
    this->isLogin = true;
}

 UserBuilder* setId(int Id);
    UserBuilder* setName(std::string name);
    UserBuilder* setPassword(std::string pass);
    UserBuilder* setIdDocument(int idDoc);
    UserBuilder* setIsLogin(bool flag);

UserBuilder::~UserBuilder() {

}

UserBuilder* UserBuilder::setId(int Id) {
    this->Id = Id;
    return this;
}

UserBuilder* UserBuilder::setName(std::string name) {
    this->name = name;
    return this;
}

UserBuilder* UserBuilder::setPassword(std::string pass) {
    this->password = pass;
    return this;
}

UserBuilder* UserBuilder::addIdDocument(int idDoc) {
    this->idDocument.push_back(idDoc);
    return this;
}

UserBuilder* UserBuilder::setIsLogin(bool flag) {
    this->isLogin = flag;
    return this;
}

User* UserBuilder::build() {
    return new User(this->Id, this->name, this->password, this->idDocument, this->isLogin);
}

UserBuilder* UserMother::one() {
    UserBuilder *user = new UserBuilder();
    user->setId(1)->setName("Test1")->setPassword("pass1")->addIdDocument(1)->setIsLogin(true);
    return user;
}

UserBuilder* UserMother::two() {
    UserBuilder *user = new UserBuilder();
    user->setId(2)->setName("Test2")->setPassword("pass2")->addIdDocument(1)->addIdDocument(2)->setIsLogin(true);
    return user;
}

UserBuilder* UserMother::three() {
    UserBuilder *user = new UserBuilder();
    user->setId(0)->setName("")->setPassword("")->setIsLogin(false);
    return user;
}