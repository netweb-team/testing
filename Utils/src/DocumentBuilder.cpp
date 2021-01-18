#include "DocumentBuilder.h"

DocumentBuilder::DocumentBuilder() {
    this->id = 0;
    this->text = "";
    this->password = "";
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

DocumentBuilder* DocumentBuilder::setPass(std::string pass) {
    this->password = pass;
    return this;
}

Document* DocumentBuilder::build() {
    return new Document(this->id, this->password, this->text);
}

DocumentBuilder* DocumentMother::one() {
    std::shared_ptr<Operation> oper = std::make_shared<Operation>();
    DocumentBuilder *doc = new DocumentBuilder();
    doc->setId(1)->updateText(oper)->setPass("123");
    return doc;
}

DocumentBuilder* DocumentMother::two() {
    std::shared_ptr<Operation> oper = std::make_shared<Operation>();
    DocumentBuilder *doc = new DocumentBuilder();
    doc->setId(2)->updateText(oper)->setPass("456");
    return doc;
}
