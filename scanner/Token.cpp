

#include "Tag.h"
#include <string>

#define to_string1(tag,value)  "< " + std::to_string(tag) + " , " + std::to_string(value) + " >"
#define to_string2(tag,value)  "< " + std::to_string(tag) + " , " + value + " >"


class Token{
public:
    int tag;
    Token(int t){
        tag = t;
    }
    Token() {}
};

//Class Integer manage lexemes for integers
class Integer : public Token {
public:
    int value;
    Integer( int v)  {
        tag = INTEGER;
        value = v;
    }
    std::string toString(){
        return to_string1(tag,value);
    }
};

//Class Integer manage lexemes for floats
class Float : public Token {
public:
    float value;
    Float( float v)  {
        tag = FLOAT;
        value = v;
    }
    std::string toString(){
        return to_string1(tag,value);
    }
};


//Class Word manages lexemes for strings
class String : public Token {
public:
    std::string lexeme;
    String( std::string s )  {
        tag = STRING;
        lexeme = s;
    }
    std::string toString(){
        return to_string2(tag,lexeme);
    }
};


//Class Word manages lexemes for reserved words and identifiers
class Word : public Token {
public:
    std::string lexeme;
    Word( std::string s , int t ) : Token(t) {
        lexeme = s;
    }
    std::string toString(){
        return to_string2(tag,lexeme);
    }
};
































