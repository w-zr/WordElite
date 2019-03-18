//
// Created by wey on 19-3-17.
//

#ifndef GAME_ROLE_H
#define GAME_ROLE_H

#include <iostream>
#include <string>
#include <memory>
#include <map>

class Role {
public:
    virtual ~Role() = default;
    virtual std::string GetRole() = 0;
};

#endif //GAME_ROLE_H
