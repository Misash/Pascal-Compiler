
#ifndef COMPILATOR_TAG_H
#define COMPILATOR_TAG_H

#include <string>

//Tag defines constant for tokens
enum Tag {
    //operators
    EXPONENT,
    PLUS ,
    MINUS,
    DIVIDE,
    TIMES ,
    ASSIGN ,
    EQ ,
    NE ,
    LT ,
    GT ,
    LE ,
    GE ,
    AND ,
    OR ,
    NOT ,
    DIV ,
    MOD ,
    IN ,
    //delimiters
    COMMA ,
    SEMICOLON ,
    COLON ,
    OPEN_PAREN ,
    CLOSE_PAREN ,
    OPEN_BRACKET ,
    CLOSE_BRACKET ,
    //keywords
    ARRAY ,
    DOWNTO ,
    FUNCTION ,
    OF ,
    REPEAT ,
    UNTIL ,
    BEGIN ,
    ELSE ,
    GOTO ,
    PACKED ,
    SET ,
    VAR ,
    CASE ,
    END ,
    IF ,
    THEN ,
    WHILE ,
    CONST ,
    FILE_ ,
    LABEL ,
    PROGRAM ,
    TO ,
    WITH ,
    DO ,
    FOR ,
    NIL ,
    RECORD ,
    TYPE ,
    //identifier
    ID ,
    //string
    STRING ,
    //numbers
    NUM

};



#endif //COMPILATOR_TAG_H
