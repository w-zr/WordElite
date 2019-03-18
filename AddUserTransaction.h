//
// Created by wey on 19-3-17.
//

#ifndef GAME_ADDUSERTRANSACTION_H
#define GAME_ADDUSERTRANSACTION_H

#include "Transaction.h"
#include "QuestionerDatabase.h"

static auto IN_UID = 0;

class AddUserTransaction : public Transaction {
public:
    ~AddUserTransaction() override = default;
    AddUserTransaction(std::string name, std::string pass): name(std::move(name)),
                                                            pass(std::move(pass)) {};
    void Execute() override;

private:
    int UID = ++IN_UID;
    std::string name;
    std::string pass;
};

void AddUserTransaction::Execute() {
    if (GUserDatabase.FindByUsername(name) != nullptr) {
        std::cout << "User " << name << " already exists." << std::endl;
        return;
    }
    GUserDatabase.addUser(UID, std::make_shared<User>(UID, name, pass));
    GPlayerDatabase.addPlayer(UID, std::make_shared<Player>(0, 0, 0));
    GQuestionerDatabase.addQuestioner(UID, std::make_shared<Questioner>(0, 0));
}

#endif //GAME_ADDUSERTRANSACTION_H
