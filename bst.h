#ifndef BS_TREE_H_
#define BS_TREE_H_

#include "account.h"
#include <iostream>
using namespace std;

class BSTree 
{
public:
    //constructors
    BSTree();
    BSTree(const BSTree& other);
    ~BSTree();

    //functions
    bool Insert(Account* acc);
    void Delete();
    bool Retrieve(int acc_id, Account*& acc) const;
    void Display() const;
    bool isEmpty() const;
    int Size() const;

private:
    //data members 
    struct Node 
    {
        Account* p_acct;
        Node* right = nullptr;
        Node* left = nullptr;
    };

    Node* root_ = nullptr;
    int size_; 

    bool RecursiveInsert(Account* new_acc, Node* &root);
    bool RecursiveRetrieve(int acct_ID, Account*& new_acc, Node* root) const;
    void RecursiveDelete(Node* root);
    void RecursiveDisplay(Node* root) const;
};
#endif




