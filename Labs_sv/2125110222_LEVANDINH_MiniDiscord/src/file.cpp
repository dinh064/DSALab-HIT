#include "file.h"
#include <fstream>

using namespace std;

// Lưu danh sách User
void saveUsers(User* head)
{
    ofstream fout("users.txt");

    User* p = head;

    while (p != NULL)
    {
        fout << p->username << " "
            << p->password << endl;

        p = p->next;
    }

    fout.close();

    cout << "Da luu users.txt\n";
}

void loadUsers(UserList& users, BST& tree)
{
    
    users.clear();
    tree.clear();

    ifstream fin("users.txt");

    if (!fin)
    {
        cout << "Khong tim thay file users.txt\n";
        return;
    }

    string username, password;

    while (fin >> username >> password)
    {
        users.addUser(username, password);
        tree.insertUser(username);
    }

    fin.close();

    cout << "Da tai du lieu!\n";
}