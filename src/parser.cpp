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
    string errors;


    Parser(){
        //get tokens
        Scanner lexer;
        lexer.get_tokens();
        tokens = lexer.tokens;
        token = tokens.begin();
        tree = new ParseTree();
        errors = "";
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
            if(ct == SEMICOLON) cout<<"\n";
            tree->insert(nameType,parent);
            scanToken();
        }else{
            string tagName = tag_name[token_type];
            string lastTagName = tag_name[(*(token))->type];
            errors += "\n >Syntatic error : Expected token " + tagName ;
            cout<<"\n > Syntatic error [token: "+ lastTagName +"] : Expected token " + tagName + " "<<parent->Value<<endl;
//            cout<<"\n > Syntatic error : Expected token " + tagName + "\n";
        }
    }


    void Program(Node* node){
        if(token == tokens.end()) return;
        if(ct == PROGRAM){
            match(PROGRAM,node);
            match(ID,node);
            match(SEMICOLON,node);
            ConstBlock(tree->insert("<ConstBlock>",node));
            VarBlock(tree->insert("<VarBlock>",node));
            MainCode(tree->insert("<MainCode>",node));
        }

    }

    void MainCode(Node* node){
        if(token == tokens.end()) return;
        if(ct == BEGIN){
            match(BEGIN,node);
            StatementList(tree->insert("<StatementList>",node));
            match(END,node);
            match(DOT,node);
        }
    }

    void ConstBlock(Node* node){
        if(token == tokens.end()) return;
        if(ct == CONST){
            match(CONST,node);
            ConstList(tree->insert("<ConstList>",node));
        }
    }

    void ConstList(Node* node){
        if(token == tokens.end()) return;
        if(ct == ID){
            match(ID,node);
            match(EQ,node);
            Value(tree->insert("<Value>",node));
            match(SEMICOLON,node);
            ConstList(tree->insert("<ConstList>",node));
        }
    }


    void VarBlock(Node* node){
        if(token == tokens.end()) return;
        if(ct == VAR){
            match(VAR,node);
            VarList(tree->insert("<VarList>",node));
        }
    }

    void VarList(Node* node){
        if(token == tokens.end()) return;
        if(ct == ID){
            VarDecl(tree->insert("<VarDecl>",node));
            match(COLON,node);
            Type(tree->insert("<Type>",node));
            match(SEMICOLON,node);
            VarList(tree->insert("<VarList>",node));
        }
    }

    void VarDecl(Node* node){
        if(token == tokens.end()) return;
        if(ct == ID){
            match(ID,node);
            _VarDecl(tree->insert("<VarDecl'>",node));
        }
    }

    void _VarDecl(Node* node){
        if(token == tokens.end()) return;
        if(ct == COMMA){
            match(COMMA,node);
            VarDecl(tree->insert("<VarDecl>",node));
        }
    }

    void Type(Node* node){
        if(token == tokens.end()) return;
        if( ct == STRING || ct== REAL || ct == INTEGER){
            match(ct,node);
        }
    }

    void StatementList(Node* node){
        if(token == tokens.end()) return;
        if(ct == BREAK || ct == CONTINUE || ct == FOR || ct == IF || ct == ID || ct == WRITE || ct ==  WRITELN){
           Statement(tree->insert("<Statement>",node));
           _StatementList(tree->insert("<StatementList'>",node));
        }
    }

    void _StatementList(Node* node){
        if(token == tokens.end()) return;
        if(ct == BREAK || ct == CONTINUE || ct == FOR || ct == IF || ct == ID || ct == WRITE || ct ==  WRITELN){
            StatementList(tree->insert("<StatementList>",node));
        }

    }

    void Statement(Node* node){
        if(token == tokens.end()) return;
        if(  ct == FOR ){
            ForStatement(tree->insert("<ForStatement>",node));
        }
        else if(  ct == IF ){
            IfStatement(tree->insert("<IfStatement>",node));
        }
        else if(  ct == ID ){
            Assign(tree->insert("<Assign>",node));
        }
        else if(ct == WRITELN){
            WriteLn(tree->insert("<WriteLn>",node));
        }
        else if(ct == WRITE){
            Write(tree->insert("<Write>",node));
        }
        else if(ct == BREAK || ct == CONTINUE){
            match(ct,node);
        }
    }

    void BlockStatement(Node* node){
        if(token == tokens.end()) return;
        if(ct == BEGIN){
            match(BEGIN,node);
            StatementList(tree->insert("<StatementList>",node));
            match(END,node);
        }
        else if(ct == BREAK || ct == CONTINUE || ct == FOR || ct == IF || ct == ID || ct == WRITE || ct ==  WRITELN){
            StatementList(tree->insert("<StatementList>",node));
        }
    }

    void ForStatement(Node* node){
        if(token == tokens.end()) return;
        if(ct == FOR){
            match(FOR,node);
            match(ID,node);
            match(ASSIGN,node);
            Value(tree->insert("<Value>",node));
            To(tree->insert("<To>",node));
            Expr(tree->insert("<Expr>",node));
            match(DO,node);
            BlockStatement(tree->insert("<BlockStatement>",node));
            match(SEMICOLON,node);
        }
    }

    void IfStatement(Node* node){
        if(token == tokens.end()) return;
        if(ct == IF){
            match(IF,node);
            match(OPEN_PAREN,node);
            Expr(tree->insert("<Expr>",node));
            match(CLOSE_PAREN,node);
            match(THEN,node);
            BlockStatement(tree->insert("<BlockStatement>",node));
            _IfStatement(tree->insert("<IfStatement'>",node));
        }
    }

    void _IfStatement(Node* node){
        if(token == tokens.end()) return;
        if( ct == ELSE){
            match(ELSE,node);
            BlockStatement(tree->insert("<BlockStatement>",node));
            match(SEMICOLON,node);
        }
        else if(ct == SEMICOLON){
            match(SEMICOLON,node);
        }
    }

    void WriteLn(Node* node){
        if(token == tokens.end()) return;
        if(ct == WRITELN){
            match(WRITELN,node);
            match(OPEN_PAREN,node);
            match(V_STRING,node);
            match(CLOSE_PAREN,node);
        }
    }


    void Write(Node* node){
        if(token == tokens.end()) return;
        if(ct == WRITE){
            match(WRITE,node);
            match(OPEN_PAREN,node);
            Expr(tree->insert("<Expr>",node));
            match(CLOSE_PAREN,node);
        }
    }


    void To(Node* node){
        if(token == tokens.end()) return;
        if(ct == TO || ct == DOWNTO){
            match(ct,node);
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
        else if( ct == ID || ct == OPEN_PAREN || ct == V_STRING || ct== V_REAL || ct == V_INTEGER ){
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
        if( ct == ID || ct == OPEN_PAREN || ct == V_STRING || ct== V_REAL || ct == V_INTEGER ){
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
        if(ct == ID || ct == OPEN_PAREN || ct == V_STRING || ct== V_REAL || ct == V_INTEGER ){
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
//            match(EMPTY,node);
//        }
    }


    void Term(Node* node){
        if(token == tokens.end()) return;
        if(ct == ID || ct == OPEN_PAREN || ct == V_STRING || ct== V_REAL || ct == V_INTEGER ){
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
        else if( ct == V_STRING || ct== V_REAL || ct == V_INTEGER ){
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
        if( ct == V_STRING || ct== V_REAL || ct == V_INTEGER){
            match(ct,node);
        }
    }



    void parseTokens(){

        //print TOKENS
        for (int i = 0; i < tokens.size() ; ++i) {
            cout <<"\n < " <<  getNameTag(tokens[i]->type)
                 <<" , \'" << tokens[i]->value<<"\'  >";
        }

        cout<<"\n\nBNF:\n";

        tree->root = new Node("<Program>");
        Program(tree->root);


    }


};



int main(){


    Parser p;

    p.parseTokens();

//    cout<<"\n\nERRORS:\n";
//    cout<<p.errors;
    cout<<"\n\ngraphic:\n";
    p.tree->print();


}
