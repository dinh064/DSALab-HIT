#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

using namespace std;

struct User
{
    string username;
    string password;

    User* next = NULL;
};

class UserList
{
private:
    User* head;

public:
    UserList();
    void clear();
    void addUser(string username, string password);
    bool registerUser(string& username);
    bool login(string& currentUser);

    bool checkUser(string username);

    void showUsers();

    User* getHead();
};

#endif