#ifndef DOCUMENT_PAR_BUILDER_H
#define DOCUMENT_PAR_BUILDER_H

#include "structs.h"

class DocumentParBuilder {
public:
    DocumentParBuilder();
    ~DocumentParBuilder();
    
    DocumentParBuilder* setP1N(int num);
    DocumentParBuilder* setP2N(int num);
    DocumentParBuilder* setP3N(int num);
    DocumentParBuilder* setP4N(int num);
    
    DocumentParBuilder* setP1S(char *str);
    DocumentParBuilder* setP2S(char *str);
    DocumentParBuilder* setP3S(char *str);
    DocumentParBuilder* setP4S(char *str);
    
    struct DocumentParams build();
    struct DocumentParams params;
};

class DocumentParMother {
public:
    static DocumentParBuilder* one();
    static DocumentParBuilder* two();
};

#endif //DOCUMENT_PAR_BUILDER_H
