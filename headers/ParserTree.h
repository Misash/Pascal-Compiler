

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


    void find (Node * n , string x , bool &flag , Node*&p  ){
        if( !n) return;
        //check not termminal
        if(!flag && n->Value == x  && !(n->children.size())){
            p = n;
            flag = 1;
        }

        for (auto iter = n->children.begin(); iter != n->children.end() ; ++iter) {
            find(*iter , x , flag , p);
        }
    }

    void insert(string val , vector<string>* childs=0){
        bool flag = 0;
        Node*p = 0;
        Node *node = new Node(val);

        if(!root) { root = node; return;}

        find(root,val,flag,p);
        if(flag){

            cout<<"\nval: "<<val<<" valencontrado: "<<p->Value;
            for (auto i = (*childs).begin(); i != (*childs).end()  ; ++i) {
                node = new Node(*i);
                p->children.push_back(node);
            }
        }else{
            cout<<"\nnot valid insertion ParserTree with "<<val ;
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

    void findTerminals(Node * n ,vector<string>& t){
        if( !n) return;

        if( !n->children.size() && n->Value.size() <=2 )
            t.push_back(n->Value);

        for (auto iter = n->children.begin(); iter != n->children.end() ; ++iter) {
            findTerminals(*iter , t);
        }
    }


    void printBNF(Node *n){

        if ( !n) return;

        vector<string> terminals;
        queue<Node *> q;
        q.push(n);

        while ( !q.empty())
        {
            int nodeCount = q.size();


            if(terminals.size())
                for (int i = 0; i < terminals.size(); ++i)
                    cout<<terminals[i]<<" ";

            findTerminals(q.front(),terminals);

            while (nodeCount > 0)
            {
                Node *node = q.front();
//                if(node->Value.size() <= 2 ){
//                    terminals.push_back(node->Value);
//                }

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


    void print(){
//        printLevelOrder(root);
        printBNF(root);
    }





};








#endif //COMPILATOR_PARSERTREE_H
