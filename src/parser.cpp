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

//    Scanner lexer;
//
//    lexer.get_tokens();
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


    ParseTree t;

    vector<string> v;

    t.insert("<assign>");

    vector<string> v2 = {"<id>" , ":=" , "<expr>"};
    t.insert("<assign>",&v2);



    vector<string> v3 = {"<id>" , "*" , "<expr>"};
    t.insert("<expr>",&v3);


    vector<string> v4 = {"A"};
    t.insert("<id>",&v4);




    vector<string> v5 = {"C"};
    t.insert("<id>",&v5);

    t.insert("<expr>",&v3);

    t.insert("<expr>",&v3);



    cout<<"\n\nGRAFICO:\n\n";
    t.print();


}
