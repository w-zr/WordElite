//
// Created by wei on 19-5-13.
//

#ifndef GAME_CLIENT_ADDWORDTRANSACTION_HPP
#define GAME_CLIENT_ADDWORDTRANSACTION_HPP

#include <string>
#include <iostream>

#include "transaction.hpp"
#include "ctoken.hpp"

class addWordTransaction : public transaction {
    ~addWordTransaction() override = default;

    void Execute() override {
        ctoken &CTOKEN = ctoken::getInstance();

        if (CTOKEN.role != 'q') {
            std::cout << "You need to be a questioner first.\n";
            return;
        }
        std::string word;
        std::cout << "Input a new word: ";
        std::getline(std::cin, word);

        std::string data = "addw " + std::to_string(CTOKEN.UID) + " " + word + '\n';
        std::cout << data << std::endl;

        rio_writen(CTOKEN.fd, data.c_str(), data.size());
        std::cout << "client: message sent: " << data << std::endl;
        char buf[MAXLINE];
        rio_t r;
        rio_readinitb(&r, CTOKEN.fd);
        rio_readlineb(&r, buf, MAXLINE);
        std::cout << buf << std::endl;
    }
};

#endif //GAME_CLIENT_ADDWORDTRANSACTION_HPP
