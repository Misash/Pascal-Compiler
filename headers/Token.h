
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

    int line , line_row;
    int type;
    std::string value;
    Token(int type,std::string value,int line , int line_row){
        this->value = value;
        this->type = type;
        this->line = line;
        this->line_row = line_row;
    }

};

#endif //COMPILATOR_TOKEN_H
