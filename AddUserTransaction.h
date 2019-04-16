//
// Created by wey on 19-3-17.
//

#ifndef GAME_ADDUSERTRANSACTION_H
#define GAME_ADDUSERTRANSACTION_H

#include "Transaction.h"

static auto IN_UID = 0;

class AddUserTransaction : public Transaction {
public:
    ~AddUserTransaction() override = default;
    void Execute() override;
};

void AddUserTransaction::Execute() {
    if (user != nullptr) {
        std::cout << "You are already logged in." << std::endl;
        return;
    }

    std::string name;
    std::string pass;
    std::cout << "Input username:";
    std::cin >> name;
    std::cout << "Input password:";
    std::cin >> pass;

    if (GUserDatabase.FindByUsername(name) != nullptr) {
        std::cout << "User " << name << " already exists." << std::endl;
        return;
    }
    ++IN_UID;
    std::cout << httpPost("localhost", "8080", "/users", "username=" + name + "&password=" + pass, 11);
    GUserDatabase.addUser(IN_UID, std::make_shared<User>(IN_UID, name, pass));
    GPlayerDatabase.addPlayer(IN_UID, std::make_shared<Player>(IN_UID, 0, 0));
    GQuestionerDatabase.addQuestioner(IN_UID, std::make_shared<Questioner>(IN_UID, 0));
}

#endif //GAME_ADDUSERTRANSACTION_H
