#include "bst.h"
#include <iostream>
using namespace std;

BSTree::BSTree() : root_(nullptr), size_(0) {}
BSTree::~BSTree() 
{
    RecursiveDelete(root_);
}

void BSTree::RecursiveDelete(Node* root) 
{
    if (root == nullptr) 
    {
        return; 
    }

    RecursiveDelete(root->left);
    RecursiveDelete(root->right);
    delete root->p_acct;
    delete root;
}

bool BSTree::Insert(Account* acc) {
    if (acc->new_acc_id() < 0) 
    {
        cerr << "ERROR: Invalid Account ID: " << acc->new_acc_id() << endl;
        return false;
    }
    return RecursiveInsert(acc, root_);
}

bool BSTree::RecursiveInsert(Account* acc, Node*& root) 
{
    if (root == nullptr) 
    {
        root = new Node{acc, nullptr, nullptr};
        size_++;
        return true; 
    }
    int new_id = acc->new_acc_id();
    int curr_id = root->p_acct->new_acc_id();

    if (new_id < curr_id) 
    {
        return RecursiveInsert(acc, root->left);
    } 
    else if (new_id > curr_id) 
    {
        return RecursiveInsert(acc, root->right);
    }

    cerr << "ERROR: This Account ID " << new_id << " already exists." << endl;
    return false; 
}

void BSTree::Display() const 
{
    if (isEmpty()) 
    {
        cerr << "ERROR: The Binary Search Tree is Empty! " << endl;
    } else {

        RecursiveDisplay(root_);
    }
    cout << endl;
}

void BSTree::RecursiveDisplay(Node* root) const 
{
    if (root != nullptr) 
    {
        RecursiveDisplay(root->left);
        cout << *(root->p_acct) << endl;
        RecursiveDisplay(root->right);
    }
}

bool BSTree::Retrieve(int acc_id, Account*& new_acc) const 
{
    return RecursiveRetrieve(acc_id, new_acc, root_);
}

bool BSTree::RecursiveRetrieve(int acc_id, Account*& acc, Node* root) const 
{
    if (root == nullptr) 
    {
        return false; 
    }

    int root_account_id = root->p_acct->new_acc_id();

    if (acc_id == root_account_id) 
    {
        acc = root->p_acct;
        return true;
    }
    if (acc_id < root_account_id) 
    {
        return RecursiveRetrieve(acc_id, acc, root->left);
    } 
    else 
    {
        return RecursiveRetrieve(acc_id, acc, root->right);
    }
}

bool BSTree::isEmpty() const 
{
    return (root_ == nullptr);
}



