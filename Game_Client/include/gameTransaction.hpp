//
// Created by wei on 19-5-15.
//

#ifndef GAME_CLIENT_GAMETRANSACTION_HPP
#define GAME_CLIENT_GAMETRANSACTION_HPP

#include <iostream>
#include <limits>
#include "transaction.hpp"
#include "ctoken.hpp"
#include "rio.hpp"

#define COUNT_BACKWARD(x, express)                                                      \
do{                                                                                     \
    for (auto i = (x); i > 0; --i) {                                                    \
        std::cout << (express) << i << " seconds.\r" << std::flush;            \
        sleep(1);                                                                       \
    }                                                                                   \
}while(0)

constexpr auto MAX_TIME = 3;



class gameTransaction : public transaction {
    ~gameTransaction() override = default;
    void Execute() override;
};

void gameTransaction::Execute() {
    ctoken &CTOKEN = ctoken::getInstance();

    if (CTOKEN.UID == -1) {
        std::cout << "Please login first\n";
        return;
    }
    if (CTOKEN.role != 'p') {
        std::cout << "You need to be a player\n";
        return;
    }
    std::cout << "Choose difficulty(1-10):";
    int round = 1, difficulty = 1;
    std::cin >> difficulty;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true) {
        std::string data = "game " + std::to_string(CTOKEN.UID) + " difficulty " + std::to_string(difficulty) + '\n';
        rio_writen(CTOKEN.fd, data.c_str(), data.size());
        std::cout << "client: message sent: " << data;

        char buf[MAXLINE];
        rio_t r;
        rio_readinitb(&r, CTOKEN.fd);
        rio_readlineb(&r, buf, MAXLINE);
        if (strcmp(buf, "0\n") == 0) {
            std::cout << "There is no word with chosen difficulty\n";
            break;
        }
        std::string question(buf);
        std::system("clear");
        std::cout << "\tRound " << round << "/" << difficulty << "\tDifficulty: " << difficulty << std::endl
                  << std::endl << "Your Question: " << buf << std::endl << std::endl;
        COUNT_BACKWARD(std::max(MAX_TIME - difficulty + 1, 1), "You have ");
        std::system("clear");
        std::cout << "Input your answer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::string answer;
        std::getline(std::cin, answer);
        if (answer == question.substr(0, question.length() - 1)) {
            std::cout << "Correct" << std::endl << "Exp +50" << std::endl;
            data = "game " + std::to_string(CTOKEN.UID) + " check 200\n";
            rio_writen(CTOKEN.fd, data.data(), data.size());
            std::cout << "client: message sent: 200\n";
            if (round == difficulty) {
                round = 0;
                difficulty++;
            }
            round++;
            COUNT_BACKWARD(3, "The next round will start in ");
            std::system("clear");
        } else {
            std::cout << "Wrong" << std::endl << std::endl << "\tGame Over" << std::endl;
            COUNT_BACKWARD(3, "Please wait for ");
            std::system("clear");
            data = "game " + std::to_string(CTOKEN.UID) + " check 500\n";
            rio_writen(CTOKEN.fd, data.data(), data.size());
            break;
        }
    }
}

#endif //GAME_CLIENT_GAMETRANSACTION_HPP
