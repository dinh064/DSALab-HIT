#include "bst.h"

BST::BST()
{
    root = NULL;
}

BSTNode* BST::insert(BSTNode* node, string username)
{
    if (node == NULL)
    {
        BSTNode* temp = new BSTNode;

        temp->username = username;
        temp->left = NULL;
        temp->right = NULL;

        return temp;
    }

    if (username < node->username)
        node->left = insert(node->left, username);

    else if (username > node->username)
        node->right = insert(node->right, username);

    return node;
}

void BST::insertUser(string username)
{
    root = insert(root, username);
}

bool BST::search(BSTNode* node, string username)
{
    if (node == NULL)
        return false;

    if (node->username == username)
        return true;

    if (username < node->username)
        return search(node->left, username);

    return search(node->right, username);
}

bool BST::searchUser(string username)
{
    return search(root, username);
}

void BST::inorder(BSTNode* node)
{
    if (node == NULL)
        return;

    inorder(node->left);

    cout << node->username << endl;

    inorder(node->right);
}

void BST::destroy(BSTNode* node)
{
    if (node == NULL)
        return;

    destroy(node->left);
    destroy(node->right);

    delete node;
}

void BST::clear()
{
    destroy(root);
    root = NULL;
}

void BST::showTree()
{
    cout << "\n===== USER TREE =====\n";

    inorder(root);

    cout << endl;
}