
#ifndef COMPILATOR_TAG_CPP
#define COMPILATOR_TAG_CPP

#include <string>


#define TAGS \
X(EXPONENT ,"EXPONENT" , "^") \
X(PLUS ,"PLUS" , "+") \
X(MINUS ,"MINUS" , "-") \
X(DIVIDE ,"DIVIDE" , "/") \
X(TIMES ,"TIMES" , "*") \
X(ASSIGN ,"ASSIGN" , ":=") \
X(RANGE ,"RANGE" , "..") \
X(EQ ,"EQ" , "=") \
X(NE ,"NE" , "<>") \
X(LT ,"LT" , "<") \
X(GT ,"GT" , ">") \
X(LE ,"LE" , "<=") \
X(GE ,"GE" , ">=") \
X(COMMA ,"COMMA" , ",")       \
X(SEMICOLON ,"SEMICOLON" , ";") \
X(DOT,"DOT",".")             \
X(COLON ,"COLON" , ":") \
X(OPEN_PAREN ,"OPEN_PAREN" , "(") \
X(CLOSE_PAREN ,"CLOSE_PAREN" , ")") \
X(OPEN_BRACKET ,"OPEN_BRACKET" , "[") \
X(CLOSE_BRACKET ,"CLOSE_BRACKET" , "]") \
X(AND ,"AND" , "and") \
X(OR ,"OR" , "or") \
X(NOT ,"NOT" , "not") \
X(DIV ,"DIV" , "div") \
X(MOD ,"MOD" , "mod") \
X(IN ,"IN" , "in")            \
X(ARRAY ,"ARRAY" , "array")   \
X(WRITELN,"WRITELN" ,"Writeln")  \
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
X(PROCEDURE ,"PROCEDURE" , "procedure")  \
X(THEN ,"THEN" , "then") \
X(WHILE ,"WHILE" , "while") \
X(CONST ,"CONST" , "const") \
X(FILE_ ,"FILE_" , "file") \
X(LABEL ,"LABEL" , "label") \
X(PROGRAM ,"PROGRAM" , "program") \
X(BREAK ,"BREAK" , "break")  \
X(CONTINUE ,"CONTINUE" , "continue")  \
X(WRITE,"WRITE" , "Write")  \
X(TO ,"TO" , "to") \
X(WITH ,"WITH" , "with") \
X(DO ,"DO" , "do") \
X(FOR ,"FOR" , "for") \
X(NIL ,"NIL" , "nil") \
X(RECORD ,"RECORD" , "record") \
X(TYPE ,"TYPE" , "type") \
X(STRING ,"STRING" , "string") \
X(INTEGER ,"INTEGER" , "integer") \
X(REAL ,"REAL" , "real")      \
X(V_STRING ,"V_STRING" , "v_string") \
X(V_INTEGER ,"V_INTEGER" , "v_integer") \
X(V_REAL ,"V_REAL" , "v_real") \
X(ID ,"ID" , "id")   \
X(FINAL,"$" , "$")    \
X(EMPTY,"e" , "e")  \

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





#endif //COMPILATOR_TAG_CPP
