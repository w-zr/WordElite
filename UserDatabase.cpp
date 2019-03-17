//
// Created by wey on 19-3-17.
//

#include <iostream>
#include "UserDatabase.h"
#include "User.h"

UserDatabase GUserDatabase;
UserDatabase::~UserDatabase() = default;

User *UserDatabase::GetUser(int UID) {
    return Users.find(UID)->second;
}

void UserDatabase::addUser(int UID, User *e) {
    Users[UID] = e;
}

void UserDatabase::PrintAllUser() {
    for (auto &User : Users) {
        std::cout << "UID: " << User.first << " username: " << User.second->GetName() << std::endl;
    }
}
