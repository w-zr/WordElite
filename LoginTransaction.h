//
// Created by wey on 19-3-18.
//

#ifndef GAME_LOGINTRANSACTION_H
#define GAME_LOGINTRANSACTION_H

#include "Transaction.h"

class LoginTransaction : public Transaction {
public:
    ~LoginTransaction() override = default;

    void Execute() override;
};

void LoginTransaction::Execute() {
    std::string username;
    std::string password;
    std::cout << "Input username:";
    std::cin >> username;
    std::cout << "Input password:";
    std::cin >> password;

    std::shared_ptr<User> u = GUserDatabase.FindByUsername(username);
    if (u == nullptr) {
        std::cout << "User does not exist!" << std::endl;
        return;
    }
    extern std::shared_ptr<User> user;
    extern std::string prompt;
    if (u->GetPass() == password) {
        std::cout << "Login succeeded!" << std::endl;
        prompt = u->GetName() + ">";
        user = std::move(u);
    } else
        std::cout << "Password mismatch!" << std::endl;
}


#endif //GAME_LOGINTRANSACTION_H
