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
    typedef ParseTreeNode  Node;
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



    void match( int token_type,Node* parent ){
        if(token == tokens.end()) return;
        if( ct == token_type){
            string nameType = tag_value[token_type];
            cout<<nameType<<" ";
            tree->insert(nameType,parent);
            scanToken();
        }else{
            cout<<"\n >Syntatic error : Expected token "<<tag_name[token_type];
        }
    }


    void Assign(Node *node){
        if(token == tokens.end()) return;
        if( ct == ID ){
            match(ID,node);
            match(ASSIGN, node);
            Expr(tree->insert("<Expr>",node));
            match(SEMICOLON,node);
        }
    }

    void Expr(Node *node){
        if(token == tokens.end()) return;
        if( ct == NOT){
            match(NOT,node);
            Expr(tree->insert("<Expr>",node));
            _Expr(tree->insert("<Expr'>",node));
        }
        else if( ct == ID || ct == OPEN_PAREN || ct == STRING || ct == REAL || ct == INTEGER ){
            Expr2(tree->insert("<Expr2>",node));
            _Expr(tree->insert("<Expr'>",node));
        }
    }

    void _Expr(Node* node){
        if(token == tokens.end()) return;
        if( ct == AND || ct == OR){
            BooleanOp(tree->insert("<BooleanOp>",node));
            Expr2(tree->insert("<Expr2>",node));
            _Expr(tree->insert("<Expr'>",node));
        }
//        else if(ct == SEMICOLON || ct == AND || ct == OR || ct == CLOSE_PAREN){
//            match(ct);
//        }
    }

    void Expr2(Node* node){
        if(token == tokens.end()) return;
        if( ct == ID || ct == OPEN_PAREN || ct == STRING || ct == REAL || ct == INTEGER ){
            Expr3(tree->insert("<Expr3>",node));
            _Expr2(tree->insert("<Expr2'>",node));
        }
    }


    void _Expr2(Node* node){
        if(token == tokens.end()) return;
        if( ct == EQ || ct == NE || ct == LT || ct == LE || ct == GE || ct == GT ){
            RelOp(tree->insert("<RelOp>",node));
            Expr3(tree->insert("<Expr3>",node));
            _Expr2(tree->insert("<Expr2'>",node));
        }
//        else if(ct == SEMICOLON || ct == AND || ct == OR ){
//            match(ct);
//        }
    }

    void Expr3(Node* node){
        if(token == tokens.end()) return;
        if(ct == ID || ct == OPEN_PAREN || ct == STRING || ct == REAL || ct == INTEGER ){
            Term(tree->insert("<Term>",node));
            _Expr3(tree->insert("<Expr3'>",node));
        }
    }

    void _Expr3(Node* node){
        if(token == tokens.end()) return;
        if(ct == PLUS ){
            match(PLUS,node);
            Term(tree->insert("<Term>",node));
            _Expr3(tree->insert("<Expr3'>",node));
        }
        else if(ct == MINUS){
            match(MINUS,node);
            Term(tree->insert("<Term>",node));
            _Expr3(tree->insert("<Expr3'>",node));
        }
//        else if(ct == SEMICOLON || ct == AND || ct == OR || ct == CLOSE_PAREN || ct == EQ || ct == NE || ct == LT || ct == LE || ct == GE || ct == GT){
//            match(ct);
//        }
    }


    void Term(Node* node){
        if(token == tokens.end()) return;
        if(ct == ID || ct == OPEN_PAREN || ct == STRING || ct == REAL || ct == INTEGER ){
            Factor(tree->insert("<Factor>",node));
            _Term(tree->insert("<Term'>",node));
        }
    }

    void _Term(Node* node){
        if(token == tokens.end()) return;
        if( ct == TIMES || ct == DIVIDE || ct == DIV || ct == MOD ){
            match(ct,node);
            Factor(tree->insert("<Factor>",node));
            _Term(tree->insert("<Term'>",node));
        }
//        else if(ct == SEMICOLON || ct == AND || ct == OR || ct == CLOSE_PAREN || ct == EQ || ct == NE || ct == LT || ct == LE || ct == GE || ct == GT){
//            match(ct);
//        }
    }

    void Factor(Node* node){
        if(token == tokens.end()) return;
        if(ct == ID  ){
            match(ct,node);
        }
        else if( ct == STRING || ct == REAL || ct == INTEGER ){
            Value(tree->insert("<Value>",node));
        }
        else if( ct == OPEN_PAREN ){
            match(OPEN_PAREN, node);
            Expr(tree->insert("<Expr>",node));
            match(CLOSE_PAREN,node);
        }
    }

    void RelOp(Node* node){
        if(token == tokens.end()) return;
        if(ct == EQ || ct == NE || ct == LT || ct == LE || ct == GE || ct == GT ){
            match(ct,node);
        }
    }

    void BooleanOp(Node* node){
        if(token == tokens.end()) return;
        if(ct == AND || ct == OR){
            match(ct,node);
        }
    }

    void Value(Node* node){
        if(token == tokens.end()) return;
        if( ct == STRING || ct== REAL || ct == INTEGER){
            match(ct,node);
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

        tree->root = new Node("<Assign>");
        Assign(tree->root);
//        cout<<"\n\ngraphic:\n";
        tree->print();

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
