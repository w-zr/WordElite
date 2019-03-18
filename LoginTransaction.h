#include <utility>

#include <utility>

//
// Created by wey on 19-3-17.
//

#ifndef GAME_LOGINTRANSACTION_H
#define GAME_LOGINTRANSACTION_H

#include "Transaction.h"

class LoginTransaction : public Transaction {
public:
    ~LoginTransaction() override = default;

    LoginTransaction(std::string username, std::string password) : username(std::move(username)), password(
            std::move(password)) {};
    void Execute() override;
private:
    std::string username;
    std::string password;
};

extern UserDatabase GUserDatabase;
void LoginTransaction::Execute() {
    User *u = GUserDatabase.FindByUsername(username);
    if(u == nullptr) {
        return;
    }
    if(u->GetPass() == password) {

    }
}


#endif //GAME_LOGINTRANSACTION_H
