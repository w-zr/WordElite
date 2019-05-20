//
// Created by wei on 19-5-13.
//

#ifndef GAME_CLIENT_CHGRTRANSACTION_HPP
#define GAME_CLIENT_CHGRTRANSACTION_HPP

#include <iostream>
#include "transaction.hpp"
#include "ctoken.hpp"
#include "rio.hpp"

class chgrTransaction : public transaction {
public:
    ~chgrTransaction() override = default;

    void Execute() override;
};

void chgrTransaction::Execute() {
    ctoken &CTOKEN = ctoken::getInstance();
    if (CTOKEN.UID == -1) {
        std::cout << "You did not login.\n";
        return;
    }

    std::cout << "Input the role you want to be([P]layer/[Q]uestioner): ";
    std::string r, data;
    std::getline(std::cin, r);

    if (r == "P" || r == "Q" || r == "p" || r == "q" || r == "Player"
        || r == "Questioner" || r == "player" || r == "questioner") {
        data = "chgr " + std::to_string(CTOKEN.UID) + ' ' + r + '\n';
        rio_writen(CTOKEN.fd, data.c_str(), data.size());
        std::cout << "client: message sent: " << data;

        char buf[MAXLINE];
        rio_t rio;
        rio_readinitb(&rio, CTOKEN.fd);
        rio_readlineb(&rio, buf, MAXLINE);
        if (strcmp(buf, "201\n") == 0)
            CTOKEN.role = 'p';
        else if (strcmp(buf, "202\n") == 0)
            CTOKEN.role = 'q';
        else {
            std::cout << "failed\n";
            CTOKEN.role = 'n';
        }
        std::cout << "Your current role is " << CTOKEN.role << std::endl;
    }
}

#endif //GAME_CLIENT_CHGRTRANSACTION_HPP
