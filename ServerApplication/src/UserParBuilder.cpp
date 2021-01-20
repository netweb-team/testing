#include "UserParBuilder.h"

UserParBuilder::UserParBuilder() {
    this->params.p1.num = 0;
    this->params.p2.num = 1;
}

UserParBuilder::~UserParBuilder() {

}

UserParBuilder* UserParBuilder::setP1N(int num) {
    this->params.p1.num = num;
    return this;
}

UserParBuilder* UserParBuilder::setP2N(int num) {
    this->params.p2.num = num;
    return this;
}

UserParBuilder* UserParBuilder::setP1S(char *str) {
    this->params.p1.str = str;
    return this;
}

UserParBuilder* UserParBuilder::setP2S(char *str) {
    this->params.p2.str = str;
    return this;
}

struct UserParams UserParBuilder::build() {
    return this->params;
}

UserParBuilder* UserParMother::one() {
    UserParBuilder *doc = new UserParBuilder();
    doc->setP1S("")->setP2S("");
    return doc;
}

UserParBuilder* UserParMother::two() {
    UserParBuilder *doc = new UserParBuilder();
    doc->setP1S("username")->setP2S("password");
    return doc;
}

UserParBuilder* UserParMother::three() {
    UserParBuilder *doc = new UserParBuilder();
    doc->setP1S("name")->setP2S("pass");
    return doc;
}
