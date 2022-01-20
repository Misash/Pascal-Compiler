
#ifndef COMPILATOR_TAG_H
#define COMPILATOR_TAG_H

#include <string>
#include <iostream>

//#define ENUM_TO_STR(ENUM) std::string(#ENUM)
////
////Tag defines constant for tokens
//enum Tag {
//    //operators
//    EXPONENT,
//    PLUS ,
//    MINUS,
//    DIVIDE,
//    TIMES ,
//    ASSIGN ,
//    EQ ,
//    NE ,
//    LT ,
//    GT ,
//    LE ,
//    GE ,
//    AND ,
//    OR ,
//    NOT ,
//    DIV ,
//    MOD ,
//    IN ,
//    //delimiters
//    COMMA ,
//    SEMICOLON ,
//    COLON ,
//    OPEN_PAREN ,
//    CLOSE_PAREN ,
//    OPEN_BRACKET ,
//    CLOSE_BRACKET ,
//    //keywords
//    ARRAY ,
//    DOWNTO ,
//    FUNCTION ,
//    OF ,
//    REPEAT ,
//    UNTIL ,
//    BEGIN ,
//    ELSE ,
//    GOTO ,
//    PACKED ,
//    SET ,
//    VAR ,
//    CASE ,
//    END ,
//    IF ,
//    THEN ,
//    WHILE ,
//    CONST ,
//    FILE_ ,
//    LABEL ,
//    PROGRAM ,
//    TO ,
//    WITH ,
//    DO ,
//    FOR ,
//    NIL ,
//    RECORD ,
//    TYPE ,
//    //identifier
//    ID ,
//    //string
//    STRING ,
//    //numbers
//    INTEGER ,
//    FLOAT
//
//};
//




#define TAGS \
X(EXPONENT ,"EXPONENT" , "^") \
X(PLUS ,"PLUS" , "+") \
X(MINUS ,"MINUS" , "-") \
X(DIVIDE ,"DIVIDE" , "/") \
X(TIMES ,"TIMES" , "*") \
X(ASSIGN ,"ASSIGN" , ":=") \
X(EQ ,"EQ" , "=") \
X(NE ,"NE" , "<>") \
X(LT ,"LT" , "<") \
X(GT ,"GT" , ">") \
X(LE ,"LE" , "<=") \
X(GE ,"GE" , ">=") \
X(AND ,"AND" , "and") \
X(OR ,"OR" , "or") \
X(NOT ,"NOT" , "not") \
X(DIV ,"DIV" , "div") \
X(MOD ,"MOD" , "mod") \
X(IN ,"IN" , "in") \
X(COMMA ,"COMMA" , ",") \
X(SEMICOLON ,"SEMICOLON" , ";") \
X(COLON ,"COLON" , ":") \
X(OPEN_PAREN ,"OPEN_PAREN" , "(") \
X(CLOSE_PAREN ,"CLOSE_PAREN" , ")") \
X(OPEN_BRACKET ,"OPEN_BRACKET" , "[") \
X(CLOSE_BRACKET ,"CLOSE_BRACKET" , "]") \
X(ARRAY ,"ARRAY" , "array") \
X(DOWNTO ,"DOWNTO" , "downto") \
X(FUNCTION ,"FUNCTION" , "function") \
X(OF ,"OF" , "of") \
X(REPEAT ,"REPEAT" , "repeat") \
X(UNTIL ,"UNTIL" , "until") \
X(BEGIN ,"BEGIN" , "begin") \
X(ELSE ,"ELSE" , "else") \
X(GOTO ,"GOTO" , "goto") \
X(PACKED ,"PACKED" , "packed") \
X(SET ,"SET" , "set") \
X(VAR ,"VAR" , "var") \
X(CASE ,"CASE" , "case") \
X(END ,"END" , "end") \
X(IF ,"IF" , "if") \
X(THEN ,"THEN" , "then") \
X(WHILE ,"WHILE" , "while") \
X(CONST ,"CONST" , "const") \
X(FILE_ ,"FILE_" , "file") \
X(LABEL ,"LABEL" , "label") \
X(PROGRAM ,"PROGRAM" , "program") \
X(TO ,"TO" , "to") \
X(WITH ,"WITH" , "with") \
X(DO ,"DO" , "do") \
X(FOR ,"FOR" , "for") \
X(NIL ,"NIL" , "nil") \
X(RECORD ,"RECORD" , "record") \
X(TYPE ,"TYPE" , "TYPE") \
X(ID ,"ID" , "") \
X(STRING ,"STRING" , "") \
X(INTEGER ,"INTEGER" , "") \
X(FLOAT ,"FLOAT" , "") \


//get values by int
#define X(type, name, value) type,
enum tag_type : size_t
{
    TAGS
};
#undef X

//get name
#define X(type, name, value) name,
char const *tag_name[] =
        {
                TAGS
        };
#undef X

//get value
#define X(type, name, value) value,
char const *tag_value[] =
        {
                TAGS
        };
#undef X


//get type of tag
int getTypeTag(const std::string &str){
#define X(type, name, value) if ( str == value) return type; else
    TAGS
#undef X
    return -1;
}


//get name of tag
std::string getNameTag(int tag){
#define X(type, name, value) if ( tag == type) return name; else
    TAGS
#undef X
        return "unknown";
}


#endif //COMPILATOR_TAG_H
