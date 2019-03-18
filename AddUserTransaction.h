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
    AddUserTransaction(std::string name, std::string pass): name(std::move(name)),
                                                            pass(std::move(pass)) {};
    void Execute() override;

private:
    int UID = ++IN_UID;
    std::string name;
    std::string pass;
};

extern UserDatabase GUserDatabase;
void AddUserTransaction::Execute() {
    std::shared_ptr<User> e = GUserDatabase.FindByUsername(name);
    if (e != nullptr) {
        std::cout << "User " << name << " already exists." << std::endl;
        return;
    }
    e = std::make_shared<User>(UID, name, pass);
    GUserDatabase.addUser(UID, e);
}

#endif //GAME_ADDUSERTRANSACTION_H
