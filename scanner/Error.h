
#ifndef COMPILATOR_ERROR_H
#define COMPILATOR_ERROR_H

#include <string>

struct Error {
    int line , line_row ;
    std::string line_context , message;
    Error( ){
        line = line_row = 1;
        line_context = message = "";
    }
};

#endif //COMPILATOR_ERROR_H










