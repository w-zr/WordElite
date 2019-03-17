//
// Created by wey on 19-3-17.
//

#ifndef GAME_FINDALLTRANSACTION_H
#define GAME_FINDALLTRANSACTION_H


#include <iostream>
#include "User.h"
#include "FindTransaction.h"
#include "UserDatabase.h"

class FindAllTransaction : public FindTransaction{
public:
    ~FindAllTransaction() override = default;
    FindAllTransaction() = default;
    void Execute() override {
        extern UserDatabase GUserDatabase;
        for (auto &it : GUserDatabase.GetUsers()) {
            std::cout << "UID: " << it.first << " username:" << it.second->GetName() << std::endl;
        }
    }
};


#endif //GAME_FINDALLTRANSACTION_H
