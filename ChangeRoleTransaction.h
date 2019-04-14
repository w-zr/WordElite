//
// Created by wey on 19-3-18.
//

#ifndef GAME_CHANGEROLETRANSACTION_H
#define GAME_CHANGEROLETRANSACTION_H

#include "Transaction.h"

class ChangeRoleTransaction : public Transaction {
public:
    ~ChangeRoleTransaction() override = default;

    void Execute() override {
        if (user == nullptr) {
            std::cout << "Please login!" << std::endl;
            return;
        }

        std::cout << "Input the role you want to be([P]layer/[Q]uestioner): ";
        std::string r;
        std::cin >> r;
        std::shared_ptr<Role> role;
        if (r == "Player" || r == "P" || r == "p")
            role = GPlayerDatabase.FindByUID(user->GetUID());
        else if (r == "Questioner" || r == "Q" || r == "q") {
            role = GQuestionerDatabase.FindByUID(user->GetUID());
        } else {
            std::cout << "invalid role! try again..." << std::endl;
            return;
        }

        user->SetRole(role);
        std::cout << "Your role is changed to " << role->GetRole() << std::endl;
    }
};


#endif //GAME_CHANGEROLETRANSACTION_H
