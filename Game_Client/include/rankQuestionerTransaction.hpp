//
// Created by wei on 19-5-18.
//

#ifndef GAME_CLIENT_RANKQUESTIONERTRANSACTION_HPP
#define GAME_CLIENT_RANKQUESTIONERTRANSACTION_HPP

#include <iostream>
#include "transaction.hpp"
#include "ctoken.hpp"
#include "rio.hpp"

class rankQuestionerTransaction : public transaction {
    ~rankQuestionerTransaction() override  = default;

    void Execute() override;
};

void rankQuestionerTransaction::Execute() {
    ctoken &CTOKEN = ctoken::getInstance();
    rio_writen(CTOKEN.fd, "rkqs all\n", strlen("rkqs all\n"));
    char buf[MAXLINE];
    rio_t rio;
    rio_readinitb(&rio, CTOKEN.fd);
    rio_readlineb(&rio, buf, MAXLINE);
    for (auto &c : buf)
        if (c == '#')
            c = '\n';
    std::cout << buf << std::endl;
}

#endif //GAME_CLIENT_RANKQUESTIONERTRANSACTION_HPP
