#ifndef STRUCTS_H
#define STRUCTS_H

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


#endif //STRUCTS_H
