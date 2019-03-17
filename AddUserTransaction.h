//
// Created by wey on 19-3-17.
//

#ifndef GAME_ADDUSERTRANSACTION_H
#define GAME_ADDUSERTRANSACTION_H

#include <string>
#include "Transaction.h"

class AddUserTransaction : public Transaction {
public:
    ~AddUserTransaction() override;
    AddUserTransaction(int UID, std::string name, std::string pass);
    void Execute() override;

private:
    int UID;
    std::string name;
    std::string pass;
};


#endif //GAME_ADDUSERTRANSACTION_H
