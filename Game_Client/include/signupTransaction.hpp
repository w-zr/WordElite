//
// Created by wei on 19-4-24.
//

#ifndef GAME_CLIENT_SIGNUPTRANSACTION_HPP
#define GAME_CLIENT_SIGNUPTRANSACTION_HPP

#include <iostream>
#include "transaction.hpp"
#include "rio.hpp"
#include "ctoken.hpp"

class signupTransaction : public transaction{
public:
    ~signupTransaction() override = default;
    void Execute() override;
};

void signupTransaction::Execute() {
    ctoken &CTOKEN = ctoken::getInstance();
    if (!CTOKEN.username.empty()) {
        std::cout << "You are already logged in.\nusername: " << CTOKEN.username << std::endl;
        return;
    }

    std::string username, password;
    std::cout << "Input username(do not use \'#\'): ";
    std::getline(std::cin, username);
    std::cout << "Input password: ";
    std::getline(std::cin, password);

    if(username.find('#') != std::string::npos) {
        std::cout << "cannot use \'#\'\n";
        return;
    }

    std::string data = "signup " + username + " " + password + '\n';
    rio_writen(CTOKEN.fd, data.data(), data.size());
    std::cout << "client: message sent: " << data;

    char buf[MAXLINE];
    rio_t r;
    rio_readinitb(&r, CTOKEN.fd);
    rio_readlineb(&r, buf, MAXLINE);
    std::cout << buf << std::endl;
}

#endif //GAME_CLIENT_SIGNUPTRANSACTION_HPP
