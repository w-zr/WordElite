#include <utility>

#include <utility>

#include <utility>



//
// Created by wey on 19-3-17.
//

#ifndef GAME_USER_H
#define GAME_USER_H

#include <utility>
#include "Role.h"
#include "Player.h"

class User {
private:
    int UID;
    std::string name;
    std::string pass;
    Role *role{};
public:
    User(int UID, std::string name, std::string pass) : UID(UID), name(std::move(name)), pass(std::move(pass)) {}

    ~User() {
        delete role;
    }

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

    void SetRole(Role *r) {
        delete role;
        role = r;
    }

    Role *GetRole() {
        return role;
    }
};


#endif //GAME_USER_H
