

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


//
//    void find (Node * n , string x , bool flag , Node*&p  ){
//        if( !n) return;
//        //check not termminal
////        if(!flag && n->Value == x  && !(n->children.size())){
////            p = n;
////            flag = 1;
////        }
//
//
//
//        for (auto iter = n->children.begin(); iter != n->children.end() ; ++iter) {
//            find(*iter , x , flag , p);
//        }
//    }
//
//    void insert(string val , Node* parent){
//
//


//        bool flag = 0;
//        Node*p;
//        Node**q;
//        Node *node = new Node(val);
//
//        find(root,val,flag,p);
//
//        if(!root) {
//            root = node;
//            q = &root;
//            flag = 1;
//        }else{
//            q = &p;
//        }
//
//        if(flag){
//            cout<<"\n";findTerminals(root); //PRINT
////            cout<<"\nval: "<<val<<" valencontrado: "<<p->Value;
//            for (auto i = (*childs).begin(); i != (*childs).end()  ; ++i) {
//                node = new Node(*i);
//                (*q)->children.push_back(node);
//            }
//        }else{
//            cout<<"\nnot valid insertion ParserTree with "<<val ;
//        }
//    }



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
