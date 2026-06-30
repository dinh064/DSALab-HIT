#include "message.h"

MessageQueue::MessageQueue()
{
    front = NULL;
    rear = NULL;
}

bool MessageQueue::isEmpty()
{
    return front == NULL;
}

void MessageQueue::sendMessage(string sender, MessageStack& history, BST& tree)
{
    Message* temp = new Message;

    temp->sender = sender;

    cout << "Receiver: ";
    cin >> temp->receiver;

    if (temp->receiver == sender)
    {
        cout << "Khong the gui tin nhan cho chinh minh!\n";
        delete temp;
        return;
    }

    if (!tree.searchUser(temp->receiver))
    {
        cout << "Nguoi dung khong ton tai!\n";
        delete temp;
        return;
    }

    cin.ignore();

    cout << "Message: ";
    getline(cin, temp->text);

    temp->next = NULL;

    if (isEmpty())
    {
        front = rear = temp;
    }
    else
    {
        rear->next = temp;
        rear = temp;
    }

    history.push(
        sender,
        temp->receiver,
        temp->text
    );

    cout << "Gui thanh cong!\n";
}

void MessageQueue::viewInbox(string username)
{
    if (isEmpty())
    {
        cout << "Khong co tin nhan!\n";
        return;
    }

    Message* p = front;

    cout << "\n===== INBOX =====\n";

    while (p != NULL)
    {
        if (p->receiver == username)
        {
            cout << "From : " << p->sender << endl;
            cout << "Text : " << p->text << endl;
            cout << "----------------------\n";
        }

        p = p->next;
    }
}