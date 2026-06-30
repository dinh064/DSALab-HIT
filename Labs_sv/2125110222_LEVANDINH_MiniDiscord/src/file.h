#ifndef FILE_H
#define FILE_H

#include "user.h"
#include "bst.h"

void saveUsers(User* head);
void loadUsers(UserList& users, BST& tree);

#endif