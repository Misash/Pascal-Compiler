

#ifndef COMPILATOR_TAG_H
#define COMPILATOR_TAG_H


//Tag defines constant for tokens
enum Tag {

    //operators
    EXPONENT,
    MINUS,
    DIVIDE,
    ASSIGN ,
    EQ ,
    NE ,
    TIMES ,
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
    PLUS ,
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
    STRING ,
    INTEGER ,
    ID ,
    FLOAT
};



#endif //COMPILATOR_TAG_H
