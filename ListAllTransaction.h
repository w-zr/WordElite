//
// Created by wey on 19-3-17.
//

#ifndef GAME_LISTALLTRANSACTION_H
#define GAME_LISTALLTRANSACTION_H

#include "Transaction.h"

class ListAllTransaction : public Transaction{
public:
    ~ListAllTransaction() override = default;
    void Execute() override {
        if (user == nullptr) {
            std::cout << "Please login!" << std::endl;
            return;
        }
        for (auto &it : GUserDatabase.GetUsers()) {
            std::cout << "UID: " << it.first << "\t\tusername: " << it.second->GetName() << std::endl;
        }
    }
};


#endif //GAME_LISTALLTRANSACTION_H
