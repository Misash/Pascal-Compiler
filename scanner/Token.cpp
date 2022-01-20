

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
class Num : public Tokens {
public:
    int value;
    Num( int v)  {
        tag = NUM;
        value = v;
    }
    std::string toString(){
        return to_string1(tag,value);
    }
};



//Class Word manages lexemes for strings
class String : public Tokens {
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
class Word : public Tokens {
public:
    std::string lexeme;
    Word( std::string s , int t ) : Tokens(t) {
        lexeme = s;
    }
    std::string toString(){
        return to_string2(tag,lexeme);
    }
};


std::string Tag_Name(int n)
{
    std::string s("unknown");
    switch (n)
    {
        case 0: { s = "EXXPONENT"; } break;
        case 1: { s = "PLUS"; } break;
        case 2: { s = "MINUS"; } break;
        case 3: { s = "DIVIDE"; } break;
        case 4: { s = "TIMES"; } break;
        case 5: { s = "ASSIGN"; } break;
        case 6: { s = "EQ"; } break;
        case 7: { s = "NE"; } break;
        case 8: { s = "LT"; } break;
        case 9: { s = "GT"; } break;
        case 10: { s = "LE"; } break;
        case 11: { s = "GE"; } break;
        case 12: { s = "AND"; } break;
        case 13: { s = "OR"; } break;
        case 14: { s = "NOT"; } break;
        case 15: { s = "DIV"; } break;
        case 16: { s = "MOD"; } break;
        case 17: { s = "IN"; } break;
        case 18: { s = "COMMA"; } break;
        case 19: { s = "SEMICOLON"; } break;
        case 20: { s = "COLON"; } break;
        case 21: { s = "OPEN_PAREN"; } break;
        case 22: { s = "CLOSE_PAREN"; } break;
        case 23: { s = "OPEN_BRACKET"; } break;
        case 24: { s = "CLOSE_BRACKET"; } break;
        case 25: { s = "ARRAY"; } break;
        case 26: { s = "DOWNTO"; } break;
        case 27: { s = "FUNCTION"; } break;
        case 28: { s = "OF"; } break;
        case 29: { s = "REPEAT"; } break;
        case 30: { s = "UNTIL"; } break;
        case 31: { s = "BEGIN"; } break;
        case 32: { s = "ELSE"; } break;
        case 33: { s = "GOTO"; } break;
        case 34: { s = "PACKED"; } break;
        case 35: { s = "SET"; } break;
        case 36: { s = "VAR"; } break;
        case 37: { s = "CASE"; } break;
        case 38: { s = "END"; } break;
        case 39: { s = "IF"; } break;
        case 40: { s = "THEN"; } break;
        case 41: { s = "WHILE"; } break;
        case 42: { s = "CONST"; } break;
        case 43: { s = "FILE_"; } break;
        case 44: { s = "LABEL"; } break;
        case 45: { s = "PROGRAM"; } break;
        case 46: { s = "TO"; } break;
        case 47: { s = "WITH"; } break;
        case 48: { s = "DO"; } break;
        case 49: { s = "FOR"; } break;
        case 50: { s = "NIL"; } break;
        case 51: { s = "RECORD"; } break;
        case 52: { s = "TYPE"; } break;
        case 53: { s = "ID"; } break;
        case 54: { s = "STRING"; } break;
        case 55: { s = "NUM"; } break;
    }
    return s;
}





























