#include "DocumentParBuilder.h"

DocumentParBuilder::DocumentParBuilder() {
    this->params.p1.num = 0;
    this->params.p2.num = 1;
    this->params.p3.num = 2;
    this->params.p4.num = 3;
}

DocumentParBuilder::~DocumentParBuilder() {

}

DocumentParBuilder* DocumentParBuilder::setP1N(int num) {
    this->params.p1.num = num;
    return this;
}

DocumentParBuilder* DocumentParBuilder::setP2N(int num) {
    this->params.p2.num = num;
    return this;
}

DocumentParBuilder* DocumentParBuilder::setP3N(int num) {
    this->params.p3.num = num;
    return this;
}

DocumentParBuilder* DocumentParBuilder::setP4N(int num) {
    this->params.p4.num = num;
    return this;
}

DocumentParBuilder* DocumentParBuilder::setP1S(char *str) {
    this->params.p1.str = str;
    return this;
}

DocumentParBuilder* DocumentParBuilder::setP2S(char *str) {
    this->params.p2.str = str;
    return this;
}

DocumentParBuilder* DocumentParBuilder::setP3S(char *str) {
    this->params.p3.str = str;
    return this;
}

DocumentParBuilder* DocumentParBuilder::setP4S(char *str) {
    this->params.p4.str = str;
    return this;
}

struct DocumentParams DocumentParBuilder::build() {
    return this->params;
}

DocumentParBuilder* DocumentParMother::one() {
    DocumentParBuilder *doc = new DocumentParBuilder();
    doc->setP1N(1)->setP2N(2)->setP3S("3")->setP4S("4");
    return doc;
}

DocumentParBuilder* DocumentParMother::two() {
    DocumentParBuilder *doc = new DocumentParBuilder();
    doc->setP1N(1)->setP2N(2)->setP3S("3")->setP4S("4");
    return doc;
}
