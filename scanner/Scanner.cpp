

#include<iostream>
#include<bits/stdc++.h> //stl
#include "Token.cpp"
#include "Error.h"
#include <fstream>

using namespace std;


class Scanner{

public:

//    Error* error ;


    string fileDir = "../test/main.pas";
    ifstream file;

    char peek = ' ';
    int line = 1;
    int line_row = 1;
    string line_context = "";
    map<int,string> words;

    Scanner(){
        //open pascal file and seek begin position
        file.open(fileDir,ios::in);
        file.seekg(0,ios::beg);


    }


    void reserve(int key,string value){
        words.insert(pair<int,string>(key,value));
    }

//
//
//    char get_char2(){
////        string texto;
////
////
////        for (int i = 1; !file.eof() ; ++i) {
////            getline(file,texto);
////            cout<<i<<" "<<texto<<endl;
////        }
////
////        file.close();
//
////        char c;
////        int i= 0;
////        file.get(c);
////        while( file.eof() == false){
////            cout<<i++<<" "<<c<<endl;
////            file.get(c);
////        }
//
//
////        typedef std::istreambuf_iterator<char> buf_iter;
////        std::fstream file(fileDir);
////        for(buf_iter i(file), e; i != e; ++i){
////            auto j = i++;
////            cout<<*i<<" "<<*(i--)<<endl;
//////            char c = *i;
////
////        }
//
//    }

    string get_char(){
        // consume and return the next char
        file.get(peek);
        return to_string(peek);
    }

    char peek_Char(){
        //return the next char , but not consume it
        return (char)file.peek() ;
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
                if(peek == '}'){get_char(); break;}
                get_char();
            }
        }
        else if(peek == '(' && peek_Char() == '*'){
            while(!file.eof()){
                if(peek == '*' && peek_Char() == ')'){
                    get_char() ,get_char(); break;
                }
                get_char();
            }
        }

    }

    void skip(){
        skipWhitespace();
        skipComments();
        skipWhitespace();
    }


    bool check_double_Token(char next){
        if(file.peek() == file.eof()) return 0;
        if( (peek == ':' || peek == '>') && peek_Char() == '=' ) return 1;
        if( peek == '<'  && (peek_Char() == '=' ||  peek_Char() == '>') ) return 1;
        return 0;
    }

    int get_value(string key){
        for (auto it = words.begin(); it != words.end()  ; ++it)
            if(it->second == key) return it->first;
    }



    string get_type(int type){
        return Tag_Name(type);
    }

    Token get_operator_and_delimiter(){
        Token *token_ptr = nullptr;
        string tokenValue = "";

        if (check_double_Token(peek)) {
            tokenValue += peek;
            tokenValue += peek_Char();
            token_ptr = new Token(get_value(tokenValue), tokenValue);
        } else{
            tokenValue += peek;
            token_ptr = new Token(get_value(tokenValue), tokenValue);
        }

        cout << line << "| type: " << get_type(token_ptr->type) << "  ,  val: " << token_ptr->value;
        return *token_ptr;
    }





    Token scan() {

        //skip comment and whitespace
        skip();


        //read operator and delimiter
        if(peek == '+' || peek == '-' || peek == '*' ||
           peek == '/' || peek == '=' || peek == '<' ||
           peek == '>' || peek == ',' || peek == ';' ||
           peek == '(' || peek == ')' || peek == '[' ||
           peek == ']' || peek == ':'){
//            return get_operator_and_delimiter();
        }


        //read number








//        if(!file.eof()) cout<<line<<"  "<<file.peek()<<endl;





    }






};



int main(){

    Scanner lexer;

//    lexer.scan();

//    cout<<endl<<ENUM_TO_STR(1);

    string x = tag_name[2];

//    std::cout << "Enum type: " <<  tag_type::PLUS<< std::endl;
//    std::cout << "Name name: " << x << std::endl;
//    std::cout << "Name value: " << tag_value[tag_type::PLUS] << std::endl;
//    std::cout << "Name type: " << tag_value[tag_type::PLUS] << std::endl;
    std::cout << "Name type: " << getType("-")<< std::endl;
//

//    for (int i = 0; i < 57; ++i) {
//        cout<<"\nX("<<Tag_Name(i)<<" ,\""<< Tag_Name(i)<<"\" , \""<<lexer.words[i]<<"\") \\";
//    }

//    for (int i = 0; i < 57; ++i) {
//        cout<<"\nX("<<Tag_Name(i)<<" ,\""<< Tag_Name(i)<<"\" , \""<<lexer.words[i]<<"\") \\";
//    }

}
