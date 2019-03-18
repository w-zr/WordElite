//
// Created by wey on 19-3-17.
//

#ifndef GAME_USER_H
#define GAME_USER_H

#include <utility>
#include "Role.h"

class User {
private:
    int UID;
    std::string name;
    std::string pass;
    std::shared_ptr<Role> role{};
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

    User& operator=(const User &u) = default;
};


#endif //GAME_USER_H
