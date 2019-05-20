//
// Created by wei on 19-5-13.
//

#ifndef GAME_CLIENT_LOGOUTTRANSACTION_HPP
#define GAME_CLIENT_LOGOUTTRANSACTION_HPP

#include <cstdlib>
#include <iostream>
#include "transaction.hpp"
#include "rio.hpp"
#include "ctoken.hpp"

class logoutTransaction : public transaction {
    ~logoutTransaction() override = default;
    void Execute() override;
};

void logoutTransaction::Execute() {
    ctoken &CTOKEN = ctoken::getInstance();
    if (CTOKEN.UID == -1) {
        std::cout << "you are not login\n";
        return;
    }
    auto data = "exit " + std::to_string(CTOKEN.UID) + '\n';
    rio_writen(CTOKEN.fd, data.data(), data.size());
    std::cout << "client: message sent: " << data;
    prompt = "client >> ";
    CTOKEN.clean();
}


#endif //GAME_CLIENT_LOGOUTTRANSACTION_HPP
