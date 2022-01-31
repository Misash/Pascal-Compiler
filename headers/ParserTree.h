

#ifndef COMPILATOR_PARSERTREE_H
#define COMPILATOR_PARSERTREE_H

#include <bits/stdc++.h>
using namespace std;



struct ParseTreeNode{

    ParseTreeNode(const string &val ) : Value(val)  {}

    string Value;
    list<ParseTreeNode*> children;
};


class ParseTree{
public:

    typedef ParseTreeNode Node;
    Node * root;


    ParseTree(){
        root = 0;
    }


    Node * insert(string value , Node *& parent){
        Node* n = new Node(value);
        parent->children.push_back(n);
        return n;
    }

    void TraversePreOrder(string& sb,string padding, string pointer , Node * node){
        if(!node) return;

        sb += padding;
        sb += pointer;
        sb += node->Value;
        sb += "\n";

        string paddingForBoth = padding;
        paddingForBoth += "│  ";

        for (auto iter = node->children.begin(); iter != node->children.end() ; ++iter) {
           if(iter == --node->children.end()){
               pointer = "└── ";
           }else{
               pointer = "├── ";
           }
            TraversePreOrder(sb,paddingForBoth,pointer,*iter);
        }

    }

    void printLevelOrder(Node *n){

        if ( !n) return;
        queue<Node *> q;
        q.push(n);
        while ( !q.empty())
        {
            int nodeCount = q.size();
            while (nodeCount > 0)
            {
                Node *node = q.front();
                cout <<node->Value << " ";
                q.pop();
                for (auto iter = node->children.begin(); iter != node->children.end() ; ++iter) {
                    q.push(*iter);
                }
                nodeCount--;
            }
            cout << endl;
        }
    }

    void findTerminals(Node * n ){
        if( !n) return;

        if( !n->children.size() ){
//            t.push_back(n->Value);
            cout<<n->Value<<" ";
        }
        for (auto iter = n->children.begin(); iter != n->children.end() ; ++iter) {
            findTerminals(*iter );
        }
    }


    void print(){
        string parseTree;
        TraversePreOrder(parseTree,"","",root);
        cout<<parseTree;
    }


};




#endif //COMPILATOR_PARSERTREE_H
