

#include "Tag.h"
#include <string>

#define to_string1(tag,value)  "< " + std::to_string(tag) + " , " + std::to_string(value) + " >"
#define to_string2(tag,value)  "< " + std::to_string(tag) + " , " + value + " >"


class Token{
public:
    int type;
    std::string value;
    Token(int type,std::string value){
        this->value = value;
        this->type = type;
    }
};




















