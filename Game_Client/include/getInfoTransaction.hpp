//
// Created by wei on 19-5-18.
//

#ifndef GAME_CLIENT_GETINFOTRANSACTION_HPP
#define GAME_CLIENT_GETINFOTRANSACTION_HPP

#include "transaction.hpp"
#include "ctoken.hpp"
#include "rio.hpp"

class getInfoTransaction : public transaction {
    ~getInfoTransaction() override = default;

    void Execute() override;
};

void getInfoTransaction::Execute() {
    ctoken &CTOKEN = ctoken::getInstance();

    auto data = "lsu " + std::to_string(CTOKEN.UID) + '\n';
    rio_writen(CTOKEN.fd, data.data(), data.size());
    char buf[MAXLINE];
    rio_t rio;
    rio_readinitb(&rio, CTOKEN.fd);
    rio_readlineb(&rio, buf, MAXLINE);
    for (auto &c : buf) {
        if (c == '#')
            c = '\n';
    }
    std::cout << buf << std::endl;
}

#endif //GAME_CLIENT_GETINFOTRANSACTION_HPP
