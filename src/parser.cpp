//
// Created by misash on 27/01/22.
//

#include <iostream>
#include "Scanner.cpp"
#include "../headers/ParserTree.h"

using namespace std;


class Parser{
public:

    typedef vector<Token*> :: iterator  TokenIter;

    TokenIter token;
    vector<Token*> tokens;
    ParseTree * tree;

    Parser(){
        //get tokens
        Scanner lexer;
        lexer.get_tokens();
        tokens = lexer.tokens;
        tree = new ParseTree();
    }


    void scanToken(){
        token ++;
    }

    int nextToken(int increment=1){
        int currentPos = token - tokens.begin();
        return (*(tokens.begin() + currentPos + increment))->type;
    }


    void match( int token_type){
        if(nextToken() == token_type){
            scanToken();
        }else{
            cout<<"\nmatching error";
        }
    }


    void Assign(){
        if(nextToken() == ID ){
            match(ID);
            match(ASSIGN);
            Expr();
            match(SEMICOLON);
        }
    }

    void Expr(){
        int next = nextToken();
        if(next == NOT){
            Expr();
            _Expr();
        }
        else if(next == ID || next == OPEN_PAREN || next == STRING || next == REAL || next == INTEGER ){
            Expr2();
            _Expr();
        }
    }

    void _Expr(){
        int next = nextToken();
        if(next == AND || next == OR){
            BooleanOp();
            Expr2();
            _Expr();
        }
        else if(next == CLOSE_PAREN){
            return;
        }
    }

    void Expr2(){
        int next = nextToken();
        if(next == ID || next == OPEN_PAREN || next == STRING || next == REAL || next == INTEGER ){
            Expr3();
            _Expr2();
        }
    }

    void _Expr2(){
        int next = nextToken();
        if(next == EQ || next == NE || next == LT || next == LE || next == GE || next == GT ){
            RelOp();
            Expr3();
            _Expr2();
        }
    }

    void Expr3(){
        int next = nextToken();
        if(next == ID || next == OPEN_PAREN || next == STRING || next == REAL || next == INTEGER ){
            Term();
            Expr3();
        }
    }

    void _Expr3(){
        int next = nextToken();
        if(next == PLUS ){
            match(PLUS);
            Term();
            _Expr3();
        }
        else if(next == MINUS){
            match(MINUS);
            Term();
            _Expr3();
        }
    }


    void Term(){
        int next = nextToken();
        if(next == ID || next == OPEN_PAREN || next == STRING || next == REAL || next == INTEGER ){
            Factor();
            _Term();
        }
    }

    void _Term(){
        int next = nextToken();
        if(next == TIMES || next == DIVIDE || next == DIV || next == MOD){
            match(next);
            Factor();
            _Term();
        }
    }

    void Factor(){
        int next = nextToken();
        if(next == ID  ){
            match(next);
        }
        else if( next == STRING || next == REAL || next == INTEGER ){
            Value();
        }
        else if( next == OPEN_PAREN ){
            match(OPEN_PAREN);
            Expr();
            match(CLOSE_PAREN);
        }
    }

    void RelOp(){
        int next = nextToken();
        if(next == EQ || next == NE || next == LT || next == LE || next == GE || next == GT ){
            match(next);
        }
    }

    void BooleanOp(){
        int next = nextToken();
        if(next == AND || next == OR){
            match(next);
        }
    }

    void Value(){
        int next = nextToken();
        if(next == STRING || next == REAL || next == INTEGER){
            match(next);
        }
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

//    t.insert("<assign>");

//    vector<string> v2 = {"<id>" , ":=" , "<expr>"};
//    t.insert("<assign>",&v2);
//
//
//
//    vector<string> v3 = {"<id>" , "*" , "<expr>"};
//    t.insert("<expr>",&v3);
//
//
//    vector<string> v4 = {"A"};
//    t.insert("<id>",&v4);
//
//
//
//
//    vector<string> v5 = {"C"};
//    t.insert("<id>",&v5);
//
//
//
//    vector<string> v6 = {"<expr>"};
//    t.insert("<expr>",&v6);
//
//    t.insert("<expr>",&v3);
//
//
//
//
//    cout<<"\n\nGRAFICO:\n\n";
//    t.print();
//
//
//    cout<<"\n\nRES:\n\n";
//    t.printResul();









}
