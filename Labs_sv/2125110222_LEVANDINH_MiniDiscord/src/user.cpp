#include "user.h"

UserList::UserList()
{
    head = NULL;
}

bool UserList::checkUser(string username)
{
    User* p = head;

    while (p != NULL)
    {
        if (p->username == username)
            return true;

        p = p->next;
    }

    return false;
}

bool UserList::registerUser(string& username)
{
    User* temp = new User;

    cout << "Username: ";
    cin >> temp->username;

    if (checkUser(temp->username))
    {
        cout << "Username da ton tai!\n";
        delete temp;
        return false;
    }

    cout << "Password: ";
    cin >> temp->password;

    temp->next = head;
    head = temp;

    username = temp->username;   // Trả về username vừa đăng ký

    cout << "Dang ky thanh cong!\n";

    return true;
}

bool UserList::login(string& currentUser)
{
    string user;
    string pass;

    cout << "Username: ";
    cin >> user;

    cout << "Password: ";
    cin >> pass;

    User* p = head;

    while (p != NULL)
    {
        if (p->username == user &&
            p->password == pass)
        {
            currentUser = user;

            cout << "Dang nhap thanh cong!\n";

            return true;
        }

        p = p->next;
    }

    cout << "Sai tai khoan hoac mat khau!\n";

    return false;
}

void UserList::showUsers()
{
    User* p = head;

    cout << "\n===== USER LIST =====\n";

    while (p != NULL)
    {
        cout << p->username << endl;
        p = p->next;
    }

    cout << endl;
}

void UserList::addUser(string username, string password)
{
    User* temp = new User;

    temp->username = username;
    temp->password = password;

    temp->next = head;
    head = temp;
}

void UserList::clear()
{
    while (head != NULL)
    {
        User* temp = head;

        head = head->next;

        delete temp;
    }
}

User* UserList::getHead()
{
    return head;
}

