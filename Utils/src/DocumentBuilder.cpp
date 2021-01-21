#include "DocumentBuilder.h"
#include <string>

DocumentBuilder::DocumentBuilder() {
    this->id = 0;
    this->text = "";
    this->name = "";
}

DocumentBuilder::~DocumentBuilder() {

}

DocumentBuilder* DocumentBuilder::setId(int newId) {
    if (newId >= 0) {
        this->id = newId;
    }
    return this;
}

DocumentBuilder* DocumentBuilder::updateText(std::shared_ptr<Operation> operation) {
    this->text = operation->applyToString(this->text);
    return this;
}

DocumentBuilder* DocumentBuilder::setName(std::string pass) {
    this->name = pass;
    return this;
}

Document* DocumentBuilder::build() {
    return new Document(this->id, this->name, this->text);
}

std::string gen_random(const int len) {
    std::string tmp_s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    
    srand((unsigned) time(NULL) * getpid());

    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) 
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    
    
    return tmp_s;
    
}

DocumentBuilder* DocumentMother::one() {
    std::shared_ptr<Operation> oper = std::make_shared<Operation>();
    DocumentBuilder *doc = new DocumentBuilder();
    doc->setId(1)->updateText(oper)->setName(gen_random(5).c_str());
    return doc;
}

DocumentBuilder* DocumentMother::two() {
    std::shared_ptr<Operation> oper = std::make_shared<Operation>();
    DocumentBuilder *doc = new DocumentBuilder();
    doc->setId(2)->updateText(oper)->setName(gen_random(5).c_str());
    return doc;
}

DocumentBuilder* DocumentMother::three() {
    DocumentBuilder *doc = new DocumentBuilder;
    doc->setId(3)->setName("");
    return doc;
}

DocumentBuilder* DocumentMother::four() {
    std::shared_ptr<Operation> oper = std::make_shared<Operation>();
    DocumentBuilder *doc = new DocumentBuilder();
    doc->setId(20)->updateText(oper)->setName(gen_random(5).c_str());
    return doc;
}
