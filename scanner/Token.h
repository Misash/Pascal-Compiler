

#ifndef COMPILATOR_TOKEN_H
#define COMPILATOR_TOKENH


#include <string>


class Token{
public:
    int type;
    std::string value;
    Token(int type,std::string value){
        this->value = value;
        this->type = type;
    }
};

#endif //COMPILATOR_TOKEN_TAG


















