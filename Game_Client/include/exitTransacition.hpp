//
// Created by wei on 19-5-6.
//

#ifndef GAME_CLIENT_EXITTRANSACITION_HPP
#define GAME_CLIENT_EXITTRANSACITION_HPP

#include <iostream>
#include "transaction.hpp"
#include "rio.hpp"
#include "ctoken.hpp"

class exitTransaction : public transaction {
public:
    ~exitTransaction() override = default;

    void Execute() override;
};

void exitTransaction::Execute() {
    ctoken &CTOKEN = ctoken::getInstance();
    auto data = "exit " + std::to_string(CTOKEN.UID) + '\n';
    rio_writen(CTOKEN.fd, data.data(), data.size());
    std::cout << "client: message sent: " << data;
    CTOKEN.clean();
    exit(0);
}

#endif //GAME_CLIENT_EXITTRANSACITION_HPP
