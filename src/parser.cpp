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
    #define ct currentTokenType()


    TokenIter token;
    vector<Token*> tokens;
    ParseTree * tree;


    Parser(){
        //get tokens
        Scanner lexer;
        lexer.get_tokens();
        tokens = lexer.tokens;

        token = tokens.begin();

        tree = new ParseTree();
    }


    void scanToken(){
        token ++;
    }

    int nextToken(int increment=1){
        int currentPos = token - tokens.begin();
        return (*(tokens.begin() + currentPos + increment))->type;
    }

    int currentTokenType(){
        return (token != tokens.end())? (*token)->type : -1;
    }



    void match( int token_type){
        if(token == tokens.end()) return;
        if( ct == token_type){
            string nameType = tag_name[token_type];
            cout<<nameType<<" ";
            scanToken();
        }else{
            cout<<"\n >Syntatic error : Expected token "<<tag_name[token_type];
        }
    }


    void Assign(){
        if(token == tokens.end()) return;
        if( ct == ID ){
            match(ID);
            match(ASSIGN);
            Expr();
            match(SEMICOLON);
        }
    }

    void Expr(){
        if(token == tokens.end()) return;
        if( ct == NOT){
            scanToken();
            Expr();
            _Expr();
        }
        else if( ct == ID || ct == OPEN_PAREN || ct == STRING || ct == REAL || ct == INTEGER ){
            Expr2();
            _Expr();
        }
    }

    void _Expr(){
        if(token == tokens.end()) return;
        if( ct == AND || ct == OR){
            BooleanOp();
            Expr2();
            _Expr();
        }
//        else if(ct == SEMICOLON || ct == AND || ct == OR || ct == CLOSE_PAREN){
//            match(ct);
//        }
    }

    void Expr2(){
        if(token == tokens.end()) return;
        if( ct == ID || ct == OPEN_PAREN || ct == STRING || ct == REAL || ct == INTEGER ){
            Expr3();
            _Expr2();
        }
    }


    void _Expr2(){
        if(token == tokens.end()) return;
        if( ct == EQ || ct == NE || ct == LT || ct == LE || ct == GE || ct == GT ){
            RelOp();
            Expr3();
            _Expr2();
        }
//        else if(ct == SEMICOLON || ct == AND || ct == OR ){
//            match(ct);
//        }
    }

    void Expr3(){
        if(token == tokens.end()) return;
        if(ct == ID || ct == OPEN_PAREN || ct == STRING || ct == REAL || ct == INTEGER ){
            Term();
            _Expr3();
        }
    }

    void _Expr3(){
        if(token == tokens.end()) return;
        if(ct == PLUS ){
            match(PLUS);
            Term();
            _Expr3();
        }
        else if(ct == MINUS){
            match(MINUS);
            Term();
            _Expr3();
        }
//        else if(ct == SEMICOLON || ct == AND || ct == OR || ct == CLOSE_PAREN || ct == EQ || ct == NE || ct == LT || ct == LE || ct == GE || ct == GT){
//            match(ct);
//        }
    }


    void Term(){
        if(token == tokens.end()) return;
        if(ct == ID || ct == OPEN_PAREN || ct == STRING || ct == REAL || ct == INTEGER ){
            Factor();
            _Term();
        }
    }

    void _Term(){
        if(token == tokens.end()) return;
        if( ct == TIMES || ct == DIVIDE || ct == DIV || ct == MOD ){
            match(ct);
            Factor();
            _Term();
        }
//        else if(ct == SEMICOLON || ct == AND || ct == OR || ct == CLOSE_PAREN || ct == EQ || ct == NE || ct == LT || ct == LE || ct == GE || ct == GT){
//            match(ct);
//        }
    }

    void Factor(){
        if(token == tokens.end()) return;
        if(ct == ID  ){
            match(ct);
        }
        else if( ct == STRING || ct == REAL || ct == INTEGER ){
            Value();
        }
        else if( ct == OPEN_PAREN ){
            match(OPEN_PAREN);
            Expr();
            match(CLOSE_PAREN);
        }
    }

    void RelOp(){
        if(token == tokens.end()) return;
        if(ct == EQ || ct == NE || ct == LT || ct == LE || ct == GE || ct == GT ){
            match(ct);
        }
    }

    void BooleanOp(){
        if(token == tokens.end()) return;
        if(ct == AND || ct == OR){
            match(ct);
        }
    }

    void Value(){
        if(token == tokens.end()) return;
        if( ct == STRING || ct== REAL || ct == INTEGER){
            match(ct);
        }
    }



    void parseTokens(){

        //print TOKENS
        for (int i = 0; i < tokens.size() ; ++i) {
            cout <<"\n < " <<  getNameTag(tokens[i]->type)
                 <<" , \'" << tokens[i]->value<<"\'  >";
        }

        cout<<"\n\nPARSER:";

//        program();
            Assign();

    }


};



int main(){


    Parser p;

    p.parseTokens();





//    Scanner lexer;
//
//    lexer.get_tokens();
//
//    print ERRORS
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


//    ParseTree t;
//
//    vector<string> v;
//
//
//
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
//    cout<<"\n\nproduccion:\n";
//    t.printResul();
//
//







}
