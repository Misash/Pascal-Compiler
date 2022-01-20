

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



class Tokens{
public:
    int tag;
    Tokens(int t){
        tag = t;

    }
    Tokens() {}
};



//Class Num manage lexemes for numbers


//
////Class Word manages lexemes for strings
//class String : public Tokens {
//public:
//    std::string lexeme;
//    String( std::string s )  {
//        tag = STRING;
//        lexeme = s;
//    }
//    std::string toString(){
//        return to_string2(tag,lexeme);
//    }
//};
//
//
////Class Word manages lexemes for reserved words and identifiers
//class Word : public Tokens {
//public:
//    std::string lexeme;
//    Word( std::string s , int t ) : Tokens(t) {
//        lexeme = s;
//    }
//    std::string toString(){
//        return to_string2(tag,lexeme);
//    }
//};



















