#ifndef USER_PAR_BUILDER_H
#define USER_PAR_BUILDER_H

#include "structs.h"

class UserParBuilder {
public:
    UserParBuilder();
    ~UserParBuilder();
    
    UserParBuilder* setP1N(int num);
    UserParBuilder* setP2N(int num);
    
    UserParBuilder* setP1S(char *str);
    UserParBuilder* setP2S(char *str);
    
    struct UserParams build();
    struct UserParams params;
};

class UserParMother {
public:
    static UserParBuilder* one();
    static UserParBuilder* two();
};

#endif //DOCUMENT_PAR_BUILDER_H

