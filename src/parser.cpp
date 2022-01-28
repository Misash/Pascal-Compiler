//
// Created by misash on 27/01/22.
//

#include <iostream>
#include "Scanner.cpp"
#include "../headers/ParserTree.h"

using namespace std;


class Parser{
public:

    vector<Token*> :: iterator token;
    vector<Token*> tokens;

    Parser(){
        //get tokens
        Scanner lexer;
        lexer.get_tokens();
        tokens = lexer.tokens;
    }

//    int nextToken(){
//        if(token == tokens.end()) return;
//    }

    void scanToken(){

    }

    void Assign(){

    }


};



int main(){

    Scanner lexer;

    lexer.get_tokens();

    //print ERRORS

    for (int i = 0; i < lexer.errors.size(); ++i) {
        cout<<"\n"<<lexer.errors[i]->message;
    }

    cout<<"\n";

    //print TOKENS
    for (int i = 0; i < lexer.tokens.size() ; ++i) {
        cout <<"\n < " <<  getNameTag(lexer.tokens[i]->type)
             <<" , \'" << lexer.tokens[i]->value<<"\'  >";
    }


}
