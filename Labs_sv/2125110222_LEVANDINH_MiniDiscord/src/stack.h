#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>

using namespace std;

struct StackNode
{
    string sender;
    string receiver;
    string message;

    StackNode* next;
};

class MessageStack
{
private:
    StackNode* top;

public:
    MessageStack();

    bool isEmpty();

    void push(string sender, string receiver, string message);

    void pop();

    void display();
};

#endif