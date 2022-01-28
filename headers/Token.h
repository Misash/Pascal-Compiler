
#ifndef COMPILATOR_TOKEN_H
#define COMPILATOR_TOKEN_H

#include <string>


struct Error {
    int line , line_row ;
    std::string  message;
    Error( int line , int line_row  , std::string message){
        this->line = line;
        this->line_row = line_row;
        this->message = message;
    }

};


class Token{
public:
    int type;
    std::string value;
    Token(int type,std::string value){
        this->value = value;
        this->type = type;
    }
};

#endif //COMPILATOR_TOKEN_H
