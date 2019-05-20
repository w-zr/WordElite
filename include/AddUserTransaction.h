//
// Created by wey on 19-3-17.
//

#ifndef GAME_ADDUSERTRANSACTION_H
#define GAME_ADDUSERTRANSACTION_H

#include <sstream>
#include "Transaction.h"
#include "rio.hpp"
#include "wrap_socket.hpp"

static auto IN_UID = 0;

class AddUserTransaction : public Transaction {
public:
    ~AddUserTransaction() override = default;

    void Execute(int fd, const std::string &parameters) override;
};

void AddUserTransaction::Execute(int fd, const std::string &parameters) {
    std::stringstream sstr(parameters);
    std::string name, pass;
    sstr >> name >> pass;
    rio::initb(fd);
    std::cout << "fd: " << std::to_string(fd) << std::endl;
    if (GUserDatabase.FindByUsername(name) != nullptr) {
        std::string data = "User " + name + " already exists\n";
        rio::writen(fd, data.data(), data.size());
        std::cout << "message sent\n";
        return;
    }
    ++IN_UID;
    std::cout << httpRequest("POST", "localhost", "8080", "/users", "username=" + name + "&password=" + pass);
    GUserDatabase.addUser(IN_UID, std::make_shared<User>(IN_UID, name, pass));
    GPlayerDatabase.addPlayer(IN_UID, std::make_shared<Player>(IN_UID, 0, 0));
    GQuestionerDatabase.addQuestioner(IN_UID, std::make_shared<Questioner>(IN_UID, 0));
    auto data = "200\n";
    rio::writen(fd, data, strlen(data));
    std::cout << "message sent\n";
}

#endif //GAME_ADDUSERTRANSACTION_H
