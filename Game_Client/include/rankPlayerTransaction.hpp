//
// Created by wei on 19-5-18.
//

#ifndef GAME_CLIENT_RANKPLAYERTRANSACTION_HPP
#define GAME_CLIENT_RANKPLAYERTRANSACTION_HPP

#include <iostream>
#include "transaction.hpp"
#include "ctoken.hpp"
#include "rio.hpp"

class rankPlayerTransaction : public transaction {
    ~rankPlayerTransaction() override = default;

    void Execute() override;
};

void rankPlayerTransaction::Execute() {
    ctoken &CTOKEN = ctoken::getInstance();
    rio_writen(CTOKEN.fd, "rkps all\n", strlen("rkps all\n"));
    char buf[MAXLINE];
    rio_t rio;
    rio_readinitb(&rio, CTOKEN.fd);
    rio_readlineb(&rio, buf, MAXLINE);
    for (auto &c : buf)
        if (c == '#')
            c = '\n';
    std::cout << buf << std::endl;
}

#endif //GAME_CLIENT_RANKPLAYERTRANSACTION_HPP
