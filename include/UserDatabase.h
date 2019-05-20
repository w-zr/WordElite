//
// Created by wey on 19-3-17.
//

#ifndef GAME_USERDATABASE_H
#define GAME_USERDATABASE_H

#include "Role.h"
#include "HttpRequest.h"

class User {
private:
    int UID;
    std::string name;
    std::string pass;
    std::shared_ptr<Role> role{};
    int fd = -1;
    double nonce = 0;
public:
    User(int UID, std::string name, std::string pass) : UID(UID), name(std::move(name)), pass(std::move(pass)) {}
    ~User() = default;

    void SetUID(int u) {
        UID = u;
    }
    int GetUID() {
        return UID;
    }

    void SetName(std::string n) {
        name = std::move(n);
    }
    std::string GetName() {
        return name;
    }

    void SetPass(std::string p) {
        pass = std::move(p);
    }
    const std::string GetPass() {
        return pass;
    }

    void SetRole(std::shared_ptr<Role> r) {
        role = std::move(r);
    }
    std::shared_ptr<Role> GetRole() {
        return role;
    }

    double GetNonce() {
        return nonce;
    }

    void SetNonce(double d) {
        this->nonce = d;
    }

    int GetFd() {
        return fd;
    }

    void SetFd(int i) {
        this->fd = i;
    }

    User& operator=(const User &u) = default;
};

class UserDatabase {
public:
    virtual ~UserDatabase() = default;

    std::shared_ptr<User> FindByUID(int UID);

    std::shared_ptr<User> FindByUsername(const std::string &username);

    std::map<int, std::shared_ptr<User>> GetUsers() { return Users; };

    void addUser(int UID, std::shared_ptr<User> e);

private:
    std::map<int, std::shared_ptr<User>> Users;
};

UserDatabase GUserDatabase;

std::shared_ptr<User> UserDatabase::FindByUID(int UID){
    if (Users.find(UID) != Users.end())
        return Users.find(UID)->second;
    return nullptr;
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


#endif //GAME_USERDATABASE_H
