//
// Created by wei on 19-5-6.
//

#ifndef GAME_CLIENT_LOGINTRANSACTION_HPP
#define GAME_CLIENT_LOGINTRANSACTION_HPP

#include <string>
#include <iostream>
#include <sstream>
#include "transaction.hpp"
#include "rio.hpp"
#include "ctoken.hpp"

extern std::string prompt;

class loginTransaction : public transaction{
public:
    ~loginTransaction() override = default;

    void Execute() override;
};

void loginTransaction::Execute() {
    ctoken &CTOKEN = ctoken::getInstance();

    std::string username;
    std::string password;
    std::cout << "Input username:";
    std::getline(std::cin, username);
    std::cout << "Input password:";
    std::getline(std::cin, password);

    auto data = "login " + username + " " + password + '\n';
    rio_writen(CTOKEN.fd, data.c_str(), data.size());
    std::cout << "client: message sent: " << data;

    char buf[MAXLINE];
    rio_t r;
    rio_readinitb(&r, CTOKEN.fd);
    rio_readlineb(&r, buf, MAXLINE);
    std::stringstream sstr(buf);
    int repcode, UID;
    double nonce;
    sstr >> repcode >> UID >> nonce;
    if (repcode == 200) {
        std::cout << std::to_string(repcode) << std::endl;
        CTOKEN.username = username;
        CTOKEN.nonce = nonce;
        CTOKEN.UID = UID;
        prompt = CTOKEN.username + ">> ";
        return;
    }
    std::cout << std::to_string(repcode) << std::endl;
}

#endif //GAME_CLIENT_LOGINTRANSACTION_HPP
