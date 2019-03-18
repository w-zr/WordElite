//
// Created by wey on 19-3-17.
//

#include "UserDatabase.h"

UserDatabase GUserDatabase;
UserDatabase::~UserDatabase() = default;

std::shared_ptr<User> UserDatabase::GetUser(int UID) {
    return Users.find(UID)->second;
}

void UserDatabase::addUser(int UID, std::shared_ptr<User> e) {
    Users[UID] = std::move(e);
}

std::shared_ptr<User> UserDatabase::FindByUsername(const std::string &username) {
    for (auto &it : GUserDatabase.GetUsers())
        if (it.second->GetName() == username)
            return it.second;
    return nullptr;
}
