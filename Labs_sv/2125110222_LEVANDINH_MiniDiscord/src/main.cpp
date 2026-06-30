#include <iostream>
#include "user.h"
#include "bst.h"
#include "message.h"
#include "stack.h"
#include "file.h"

using namespace std;

int main()
{
    UserList users;
    BST tree;
    MessageQueue chat;
    MessageStack history;

    string currentUser = "";

    int choice;

    do
    {
        cout << "\n========== MINI DISCORD ==========\n";

        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Show Users\n";
        cout << "4. Search User\n";
        cout << "5. Show BST\n";
        cout << "6. Send Message\n";
        cout << "7. Inbox\n";
        cout << "8. Undo Message\n";
        cout << "9. Message History\n";
        cout << "10. Save Data\n";
        cout << "11. Load Data\n";
        cout << "0. Exit\n";

        cout << "Choose: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string username;

            if (users.registerUser(username))
            {
                tree.insertUser(username);
            }

            break;
        }

        case 2:
        {
            users.login(currentUser);
            break;
        }

        case 3:
        {
            users.showUsers();
            break;
        }

        case 4:
        {
            string name;

            cout << "Username: ";
            cin >> name;

            if (tree.searchUser(name))
                cout << "Tim thay!\n";
            else
                cout << "Khong tim thay!\n";

            break;
        }

        case 5:
        {
            tree.showTree();
            break;
        }

        case 6:
        {
            if (currentUser == "")
            {
                cout << "Hay dang nhap truoc!\n";
                break;
            }

            chat.sendMessage(currentUser, history, tree);

            break;
        }

        case 7:
        {
            if (currentUser == "")
            {
                cout << "Hay dang nhap truoc!\n";
                break;
            }

            chat.viewInbox(currentUser);

            break;
        }

        case 8:
        {
            history.pop();
            break;
        }

        case 9:
        {
            history.display();
            break;
        }

        case 10:
        {
            saveUsers(users.getHead());
            break;
        }

        case 11:
        {
            loadUsers(users, tree);
            break;
        }

        case 0:
            cout << "Goodbye!\n";
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);

    return 0;



}