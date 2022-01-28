

#include <iostream>
#include<bits/stdc++.h>
#include "../headers/Tag.h"
#include "../headers/Token.h"
#include <fstream>

using namespace std;


class Scanner{

public:

    string fileDir = "../test/main.pas";
    ifstream file;

    char peek = ' ';
    int line = 1;
    int line_row = 1;
    string line_context = "";
    vector<Token*> tokens;
    vector<Error*> errors;

    Scanner(){
        //open pascal file and seek begin position
        file.open(fileDir,ios::in);
        file.seekg(0,ios::beg);
    }


    string get_char(){
        // consume and return the next char
        if(peek != '\n') line_row++;
        else line_row = 1;
        file.get(peek);
        return to_string(peek);
    }

    char peek_Char(){
        //return the next char , but not consume it
        return (char)file.peek() ;
    }

    void consume(int i){
        while ( i--) get_char();
    }


    void skipWhitespace(){
        while( !file.eof()  &&  (peek == ' ' || peek == '\n' || peek == '\t')){
            if(peek == '\n') line++;
            get_char();
        }
    }


    void skipComments(){

        if(peek == '{'){
            while(!file.eof()){
                line +=(peek == '\n');
                if(peek == '}'){get_char(); break;}
                get_char();
            }
        }
        else if(peek == '(' && peek_Char() == '*'){
            consume(2);
            while(!file.eof()){
                line +=(peek == '\n');
                if(peek == '*' && peek_Char() == ')'){
                    consume(2); break;
                }
                get_char();
            }
        }

    }

    void skip(){
        skipWhitespace();
        skipComments();
    }


    bool check_double_Token(char next){
        if(file.peek() == file.eof()) return 0;
        if( (peek == ':' || peek == '>') && peek_Char() == '=' ) return 1;
        if( peek == '<'  && (peek_Char() == '=' ||  peek_Char() == '>') ) return 1;
        if(peek == '.' && peek_Char() == '.') return 1;
        return 0;
    }



    bool isNumberic(char c){
        return (int)c >= 48 && (int)c <=57;
    }

    bool isLetter(char c){
        return ((int)c >= 65 && (int)c <=90) || ((int)c >= 97 && (int)c <=122) ;
    }

    bool isKeyword(string tagVal){
        int tagType = getTypeTag(tagVal);
        return tagType >=AND && tagType <=REAL;
    }

    Token* createToken(int type , string value){
        Token* tkn = new Token(type , value);
        return tkn;
    }



    Token* get_operator_and_delimiter(){
        Token *token_ptr = nullptr;
        string tokenValue = "";

        if (check_double_Token(peek)) {
            tokenValue += peek;
            tokenValue += peek_Char();
            token_ptr = new Token(getTypeTag(tokenValue), tokenValue);
            get_char();
        } else{
            tokenValue += peek;
            token_ptr = new Token(getTypeTag(tokenValue), tokenValue);
        }
        get_char();
        return token_ptr;
    }

    void consume_Numbers(string &num){
        while(isNumberic(peek)){
            num += peek;
            get_char();
        }
    }

    Token* consume_scientificNotation(string &num){
        consume_Numbers(num);
        if(peek == 'e' && !file.eof() && ( peek_Char() == '+' || peek_Char() == '-' || isNumberic(peek_Char()))){
            num += peek; get_char(); num += peek; get_char();
            consume_Numbers(num);
            return createToken(REAL , num);
        }
    }

    Token* get_Number(){
        string num = "";
        consume_scientificNotation(num);
        if(  peek != '.' || ( peek == '.' && peek_Char() == '.') ) return createToken(INTEGER, num);
        num += peek; get_char();
        consume_scientificNotation(num);
        return createToken(REAL,num);
    }

    Token* get_KeyWord_or_ID(){
        string name;
        do{
            name += peek;
            get_char();
        }while(isLetter(peek) || isNumberic(peek));

        if(peek == '@' || peek == '#' || peek == '%' || peek == '_' || peek == '&'){
            return 0;
        }

        if(isKeyword(name))
            return createToken(getTypeTag(name),name);
        else
            return createToken(ID,name);
    }



    Token* get_String(){
        string txt = "";
        get_char();
        while (!file.eof() && peek != '\n'){

            if(peek == '\'' && peek_Char() ==  '\'' ){
                get_char();
            }else if(peek == '\'' && peek_Char() != '\''){
                get_char();
                return createToken(STRING,txt);
            }

            txt += peek;
            get_char();
        }
        if(peek == '\n'){
            return 0;
        }
    }



    Token* scan() {

        if(file.eof()) return 0;

        //skip comment and whitespace
        while(!file.eof() && ( peek == ' ' || peek == '\n' || peek == '\t'))
            skip();

        //read operator and delimiter
        if(peek == '+' || peek == '-' || peek == '*' ||
           peek == '/' || peek == '=' || peek == '<' ||
           peek == '>' || peek == ',' || peek == ';' ||
           peek == '(' || peek == ')' || peek == '[' ||
           peek == ']' || peek == ':' || peek == '.' || peek == '^'){
            return get_operator_and_delimiter();
        }

        //read number
        if(isNumberic(peek)) return get_Number();

        //read keyword or ID token
        if(isLetter(peek)) return get_KeyWord_or_ID();

        //read string
        if(peek == '\'') return get_String();

        return 0;
    }


    void get_tokens(){
        Token * token_ptr = 0;
        Error * error_ptr = 0;
        do{
            token_ptr = scan();
            if( token_ptr){
                tokens.push_back(token_ptr);
            }else if(!file.eof()){
                string message = "Error: reading Token ""at line " + to_string(line) + " and  row " + to_string(line_row);
                error_ptr = new Error(line,line_row ,message);
                errors.push_back(error_ptr);
                get_char();
            }

        } while (!file.eof());

    }

};

//int main(){
//
//    Scanner lexer;
//
//    lexer.run();
//
//    //print ERRORS
//
//    for (int i = 0; i < lexer.errors.size(); ++i) {
//        cout<<"\n"<<lexer.errors[i]->message;
//    }
//
//    cout<<"\n";
//
//    //print TOKENS
//    for (int i = 0; i < lexer.tokens.size() ; ++i) {
//        cout <<"\n < " <<  getNameTag(lexer.tokens[i]->type)
//             <<" , \'" << lexer.tokens[i]->value<<"\'  >";
//    }
//
//
//}




