//
// Created by wey on 19-3-18.
//

#ifndef GAME_LOGINTRANSACTION_H
#define GAME_LOGINTRANSACTION_H

#include <sstream>
#include <random>
#include <poll.h>
#include "Transaction.h"
#include "rio.hpp"

class LoginTransaction : public Transaction {
public:
    ~LoginTransaction() override = default;

    void Execute(int fd, const std::string &parameters) override;
};

void LoginTransaction::Execute(int fd, const std::string &parameters) {
    std::stringstream sstr(parameters);
    std::string username, password, data;
    sstr >> username >> password;
    rio::initb(fd);
    std::shared_ptr<User> u = GUserDatabase.FindByUsername(username);
    if (u == nullptr) {
        data = "500\n";
        rio::writen(fd, data.data(), data.size());
        std::cout << "message sent\n";
        return;
    }

    if (u->GetPass() == password && u->GetFd() == -1) {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(1.0, 10.0);
        double nonce = dist(mt);
        data = "200 " + std::to_string(u->GetUID()) + " " + std::to_string(nonce) + "\n";
        rio::writen(fd, data.data(), data.size());
        std::cout << "message sent\n";
        u->SetNonce(nonce);
        u->SetFd(fd);
        return;
    }
    data = "500\n";
    rio::writen(fd, data.data(), data.size());
    std::cout << "message sent\n";
}


#endif //GAME_LOGINTRANSACTION_H
