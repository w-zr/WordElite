#include <utility>

//
// Created by wey on 19-3-18.
//

#ifndef GAME_CHANGEROLETRANSACTION_H
#define GAME_CHANGEROLETRANSACTION_H

#include "Transaction.h"


extern std::shared_ptr<User> user;
class ChangeRoleTransaction : public Transaction {
public:
    ~ChangeRoleTransaction() override = default;

    explicit ChangeRoleTransaction(std::shared_ptr<Role> role) : role(std::move(role)) {}

    void Execute() override {
        user->SetRole(role);
    }

private:
    std::shared_ptr<Role> role;
};


#endif //GAME_CHANGEROLETRANSACTION_H
