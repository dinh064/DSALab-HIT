#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>

using namespace std;

struct BSTNode
{
    string username;
    BSTNode* left = NULL;
    BSTNode* right = NULL;
};

class BST
{
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, string username);
    bool search(BSTNode* node, string username);
    void inorder(BSTNode* node);
    void destroy(BSTNode* node);

public:
    BST();

    void clear();

    void insertUser(string username);

    bool searchUser(string username);

    void showTree();
};

#endif