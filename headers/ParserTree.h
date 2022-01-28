

#ifndef COMPILATOR_PARSERTREE_H
#define COMPILATOR_PARSERTREE_H

#include <bits/stdc++.h>
using namespace std;


struct ParseTreeNode{

    enum{
        T , NT
    };

    ParseTreeNode(const string &val , int type) : Value(val) , Type(type) {}

    string Value;
    int Type;
    list<ParseTreeNode*> children;
};


class ParseTree{
public:

    typedef ParseTreeNode Node;
    Node * root;


    ParseTree(){
        root = 0;
    }

    void track (Node * n , string x , bool &flag , Node**&p ){
        if( !n) return;
        //check not termminal
        if(!flag && n->Value == x && n->Type && !(n->children.size())){
            p = &n;
            flag = 1;
            return;
        }
        for (auto iter = n->children.begin(); iter != n->children.end() ; ++iter) {
            track(*iter , x , flag , p);
        }
    }

    bool find(string x , Node**&p){
        bool flag = 0;
        track(root,x,flag,p);
        return flag;
    }

    void insert(string val , int type){
        Node**p = &root;
        Node *node = new Node(val , type);
        if(find(val , p)){
            (*p)->children.push_back(node);
        }
        else if(!root){
            *p = node;
        }
        else if(!root->children.size()){
            (*p)->children.push_back(node);
        }
        else{
            cout<<"not valid insertion ParserTree!";
        }
        return;
    }


    void Print(){

    }






};








#endif //COMPILATOR_PARSERTREE_H
