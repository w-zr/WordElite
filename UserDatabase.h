//
// Created by wey on 19-3-17.
//

#ifndef GAME_USERDATABASE_H
#define GAME_USERDATABASE_H

#include <iostream>
#include <memory>
#include <map>
#include "User.h"

class User;

class UserDatabase {
public:
    virtual ~UserDatabase();

    std::shared_ptr<User> GetUser(int UID);

    std::shared_ptr<User> FindByUsername(const std::string& username);

    std::map<int, std::shared_ptr<User>> GetUsers() { return Users; };

    void addUser(int UID, std::shared_ptr<User>);

    void clear() { Users.clear(); }

private:
    std::map<int, std::shared_ptr<User>> Users;
};


#endif //GAME_USERDATABASE_H
