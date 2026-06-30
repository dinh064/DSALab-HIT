#ifndef MESSAGE_H
#define MESSAGE_H
#include "stack.h"
#include "bst.h"
#include <iostream>
#include <string>

using namespace std;

struct Message
{
    string sender;
    string receiver;
    string text;

    Message* next = NULL;
};

class MessageQueue
{
private:
    Message* front;
    Message* rear;

public:
    MessageQueue();

    void sendMessage(string sender, MessageStack& history, BST& tree);

    void viewInbox(string username);

    bool isEmpty();
};

#endif