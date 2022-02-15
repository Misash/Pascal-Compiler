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
    vector<Error*> errors;
    ParseTree * tree;
    vector<string> linesCode;
    string fileDir;
    string CPPCode;

    Parser(){
        //get tokens
        Scanner lexer;
        lexer.get_tokens();
        tokens = lexer.tokens;
        errors = lexer.errors;
        fileDir = lexer.fileDir;
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


    string declarationAtLine(int line){
        ifstream file;
        file.open(fileDir,ios::in);
        file.seekg(0,ios::beg);
        string sentence;

        while(line --){
            getline(file, sentence);
        }
        file.close();

        return sentence;
    }

    string printLocalizer(int size){
        string res;
        for (int i = 0; i < size ; ++i)
            res += (i == size - 1)? '^' : ' ';
        return res;
    }



    void match( int token_type,Node* parent ,string code=""){
        if(token == tokens.end()) return;
        if( ct == token_type){
            string nameType = tag_value[token_type];

            CPPCode += code;
//            cout<<nameType<<" ";
//            if(ct == SEMICOLON) cout<<"\n";
            tree->insert(nameType,parent);
            scanToken();
        }else{
            string tagValue = tag_value[token_type];
            string message = "Expected \'" + tagValue  + "\' at declaration "  ;
            token --;
            message += "\n\t" + declarationAtLine((*token)->line );
            message += "\n\t" + printLocalizer((*token)->line_row+1)  ;
            Error* error_ptr = new Error((*token)->line,(*token)->line_row  ,message);
            token++;
            errors.push_back(error_ptr);
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
            match(BEGIN,node,"\n");
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
            match(ID,node,"\nconst " + (*token)->value);
            match(EQ,node," = ");
            Value(tree->insert("<Value>",node));
            match(SEMICOLON,node," ; ");
            ConstList(tree->insert("<ConstList>",node));
        }
    }


    void VarBlock(Node* node){
        if(token == tokens.end()) return;
        if(ct == VAR){
            match(VAR,node,"\n");
            VarList(tree->insert("<VarList>",node));
        }
    }

    void VarList(Node* node){
        if(token == tokens.end()) return;
        if(ct == ID){
            VarDecl(tree->insert("<VarDecl>",node));
            match(COLON,node);
            Type(tree->insert("<Type>",node));
            match(SEMICOLON,node," ; ");
            VarList(tree->insert("<VarList>",node));
        }
    }

    void VarDecl(Node* node){
        if(token == tokens.end()) return;
        if(ct == ID){
            match(ID,node,"\nvar "+(*token)->value);
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
            match(ct,node , (*token)->value);
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
            match(FOR,node,"\nfor( ");
            match(ID,node,"var i");
            match(ASSIGN,node," = ");
            Value(tree->insert("<Value>",node));
            To(tree->insert("<To>",node));
            Expr(tree->insert("<Expr>",node));
            match(DO,node," ; i++ ){\n");
            BlockStatement(tree->insert("<BlockStatement>",node));
            match(SEMICOLON,node,"\n}\n");
        }
    }

    void IfStatement(Node* node){
        if(token == tokens.end()) return;
        if(ct == IF){
            match(IF,node,"\nif");
            match(OPEN_PAREN,node,"(");
            Expr(tree->insert("<Expr>",node));
            match(CLOSE_PAREN,node,")");
            match(THEN,node,"{\n");
            BlockStatement(tree->insert("<BlockStatement>",node));
            _IfStatement(tree->insert("<IfStatement'>",node));
        }
    }

    void _IfStatement(Node* node){
        if(token == tokens.end()) return;
        if( ct == ELSE){
            match(ELSE,node,"\n}\nelse{\n");
            BlockStatement(tree->insert("<BlockStatement>",node));
            match(SEMICOLON,node,"\n}\n");
        }
        else if(ct == SEMICOLON){
            match(SEMICOLON,node,"\n}\n");
        }
    }

    void WriteLn(Node* node){
        if(token == tokens.end()) return;
        if(ct == WRITELN){
            match(WRITELN,node,"\nconsole.log");
            match(OPEN_PAREN,node,"( ");
            Expr(tree->insert("<Expr>",node));
            match(CLOSE_PAREN,node," )");
            match(SEMICOLON,node,";\n");
        }
    }


    void Write(Node* node){
        if(token == tokens.end()) return;
        if(ct == WRITE){
            match(WRITE,node,"\nconsole.log");
            match(OPEN_PAREN,node,"( ");
            Expr(tree->insert("<Expr>",node));
            match(CLOSE_PAREN,node," )");
            match(SEMICOLON,node,";\n");
        }
    }


    void To(Node* node){
        if(token == tokens.end()) return;
        if(ct == TO || ct == DOWNTO){
            match(ct,node , "; i < ");
        }
    }



    void Assign(Node *node){
        if(token == tokens.end()) return;
        if( ct == ID ){
            match(ID,node,"\n" + (*token)->value);
            match(ASSIGN, node," = ");
            Expr(tree->insert("<Expr>",node));
            match(SEMICOLON,node," ;\n");
        }
    }

    void Expr(Node *node){
        if(token == tokens.end()) return;
        if( ct == NOT){
            match(NOT,node," not ");
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
            match(PLUS,node, " + ");
            Term(tree->insert("<Term>",node));
            _Expr3(tree->insert("<Expr3'>",node));
        }
        else if(ct == MINUS){
            match(MINUS,node," - ");
            Term(tree->insert("<Term>",node));
            _Expr3(tree->insert("<Expr3'>",node));
        }
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
            match(ct,node,(*token)->value);
            Factor(tree->insert("<Factor>",node));
            _Term(tree->insert("<Term'>",node));
        }
    }

    void Factor(Node* node){
        if(token == tokens.end()) return;
        if(ct == ID  ){
            match(ct,node, (*token)->value);
        }
        else if( ct == V_STRING || ct== V_REAL || ct == V_INTEGER ){
            Value(tree->insert("<Value>",node));
        }
        else if( ct == OPEN_PAREN ){
            match(OPEN_PAREN, node,"( ");
            Expr(tree->insert("<Expr>",node));
            match(CLOSE_PAREN,node," )");
        }
    }

    void RelOp(Node* node){
        if(token == tokens.end()) return;
        if(ct == EQ || ct == NE || ct == LT || ct == LE || ct == GE || ct == GT ){
            match(ct,node,(*token)->value);
        }
    }

    void BooleanOp(Node* node){
        if(token == tokens.end()) return;
        if(ct == AND || ct == OR){
            match(ct,node,(*token)->value);
        }
    }

    void Value(Node* node){
        if(token == tokens.end()) return;
        if(ct == V_STRING ){
            match(ct,node , "\""+(*token)->value+"\"");
        }
        else if(  ct== V_REAL || ct == V_INTEGER){
            match(ct,node , (*token)->value);
        }
    }



    void parseTokens(){

//        print TOKENS
//        for (int i = 0; i < tokens.size() ; ++i) {
//            cout <<"\n < " <<  getNameTag(tokens[i]->type)
//                 <<" , \'" << tokens[i]->value<<"\'  >";
//        }

        tree->root = new Node("<Program>");
        Program(tree->root);

    }

};


int main(){



    Parser p;
    p.parseTokens();


    if(p.errors.size()){
        for (int i = 0; i < p.errors.size(); ++i) {
            cout<<"\n"<<p.errors[i]->message;
        }
        return 0;
    }


    std::ofstream outfile;
    outfile.open("../test/code.js", std::ios::trunc);
    outfile <<p.CPPCode;



}
