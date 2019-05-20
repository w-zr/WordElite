//
// Created by wei on 19-5-13.
//

#ifndef GAME_EXITTRANSACTION_HPP
#define GAME_EXITTRANSACTION_HPP

#include <sstream>
#include "Transaction.h"

class ExitTransaction : public Transaction {
    ~ExitTransaction() override = default;
    void Execute(int fd, const std::string& parameters) override;
};

void ExitTransaction::Execute(int fd, const std::string &parameters) {
    std::stringstream sstr(parameters);
    int uid;
    sstr >> uid;
    auto u = GUserDatabase.FindByUID(uid);
    if (u == nullptr)
        return;
    u->SetNonce(0);
    u->SetFd(-1);
    std::cout << "User [" << std::to_string(uid) << "] logout\n";
}

#endif //GAME_EXITTRANSACTION_HPP
