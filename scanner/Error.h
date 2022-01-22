
#ifndef COMPILATOR_ERROR_H
#define COMPILATOR_ERROR_H

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

#endif //COMPILATOR_ERROR_H










