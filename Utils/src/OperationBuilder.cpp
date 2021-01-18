#include "OperationBuilder.h"

OperationBuilder::OperationBuilder() {
    this->lenBeforeOperation = 0;
    this->lenAfterOperation = 0;
    this->revision = 0;
    this->idEditor = 0;
    Change *change = new Change();
    this->ops.push_back(*change);
}

OperationBuilder::~OperationBuilder() {

}

OperationBuilder* OperationBuilder::setlenBef(size_t before) {
    this->lenBeforeOperation = before;
    return this;
}

OperationBuilder* OperationBuilder::setlenAft(size_t after) {
    this->lenAfterOperation = after;
    return this;
}

OperationBuilder* OperationBuilder::setId(int idEditor) {
    this->idEditor = idEditor;
    return this;
}

OperationBuilder* OperationBuilder::setRev(int revision) {
    this->revision = revision;
    return this;
}

Operation* OperationBuilder::build() {
    return new Operation(this->idEditor, this->revision, this->lenBeforeOperation, this->lenAfterOperation, this->ops);
}

OperationBuilder* OperationMother::one() {
    OperationBuilder *opr = new OperationBuilder();
    opr->setId(1)->setRev(1)->setlenBef(1)->setlenAft(1);
    return opr;
}

OperationBuilder* OperationMother::two() {
    OperationBuilder *opr = new OperationBuilder();
    opr->setId(2)->setRev(2)->setlenBef(2)->setlenAft(2);
    return opr;
}
