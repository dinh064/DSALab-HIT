#include "stack.h"

MessageStack::MessageStack()
{
    top = NULL;
}

bool MessageStack::isEmpty()
{
    return top == NULL;
}

void MessageStack::push(string sender, string receiver, string message)
{
    StackNode* temp = new StackNode;

    temp->sender = sender;
    temp->receiver = receiver;
    temp->message = message;

    temp->next = top;
    top = temp;
}

void MessageStack::pop()
{
    if (isEmpty())
    {
        cout << "\nKhong co tin nhan de Undo!\n";
        return;
    }

    cout << "\nDa Undo tin nhan:\n";
    cout << "From : " << top->sender << endl;
    cout << "To   : " << top->receiver << endl;
    cout << "Text : " << top->message << endl;

    StackNode* temp = top;

    top = top->next;

    delete temp;
}

void MessageStack::display()
{
    if (isEmpty())
    {
        cout << "\nLich su rong!\n";
        return;
    }

    StackNode* p = top;

    cout << "\n========== HISTORY ==========\n";

    while (p != NULL)
    {
        cout << "From : " << p->sender << endl;
        cout << "To   : " << p->receiver << endl;
        cout << "Text : " << p->message << endl;
        cout << "-----------------------------\n";

        p = p->next;
    }
}