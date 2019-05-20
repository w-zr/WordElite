//
// Created by wei on 19-5-18.
//

#ifndef GAME_CLIENT_CHALLENGETRANSACTION_HPP
#define GAME_CLIENT_CHALLENGETRANSACTION_HPP

#include <iostream>
#include <sstream>
#include <chrono>
#include "transaction.hpp"
#include "ctoken.hpp"
#include "rio.hpp"

class Timer {
public:
    typedef std::chrono::high_resolution_clock Clock;

    void start() { epoch = Clock::now(); }

    Clock::duration time_elapsed() const { return Clock::now() - epoch; }

private:
    Clock::time_point epoch;
};

class rival {
public:
    int callerID, calleeID;

    std::string data() {
        return " " + std::to_string(callerID) + " " + std::to_string(calleeID) + " ";
    }

    rival() : callerID(0), calleeID(0) {}
};

static rival Grival; // NOLINT(cert-err58-cpp)

class challengeTransaction : public transaction {
    ~challengeTransaction() override = default;

    void Execute() override;
};

class rivalGame : public transaction {
public:
    ~rivalGame() override = default;

    void Execute() override;
};

void rivalGame::Execute() {
    Timer T;
    ctoken &CTOKEN = ctoken::getInstance();
    char buf[MAXLINE];
    rio_t rio;
    rio_readinitb(&rio, CTOKEN.fd);
    rio_readlineb(&rio, buf, MAXLINE);
    std::stringstream sstr(buf);
    std::string data, question;
    int round, difficulty;
    sstr >> question >> difficulty >> round;
    COUNT_BACKWARD(3, "Game starts in ");
    while (true) {
        std::system("clear");
        std::cout << "\tRound " << round << "/" << difficulty << "\tDifficulty: " << difficulty << std::endl
                  << std::endl << "Your Question: " << question << std::endl << std::endl;
        COUNT_BACKWARD(std::max(MAX_TIME - difficulty + 1, 1), "You have ");
        std::system("clear");
        std::cout << question << " Input your answer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        T.start();
        std::string answer;
        std::getline(std::cin, answer);
        const auto elapsed = T.time_elapsed();
        const auto time = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

        if (answer == question) {
            data = "challenge " + std::to_string(CTOKEN.UID) + Grival.data() + "check " + std::to_string(time) + '\n';
            rio_writen(CTOKEN.fd, data.data(), data.size());
            std::cout << "client: message sent: " + data + '\n';
        } else {
            data = "challenge " + std::to_string(CTOKEN.UID) + Grival.data() + "check -100\n";
            rio_writen(CTOKEN.fd, data.data(), data.size());
            std::cout << "client: message sent: " + data + '\n';
        }

        rio_readlineb(&rio, buf, MAXLINE);
        std::cout << buf;
        if (strcmp(buf, "601\n") == 0) {
            std::cout << "Caller wins\nGame Over\n";
            goto over;
        } else if (strcmp(buf, "602\n") == 0) {
            std::cout << "Callee wins\nGame Over\n";
            goto over;
        } else if (strcmp(buf, "600\n") == 0) {
            std::cout << "Draw\nGame Over\n";
            goto over;
        } else if (strcmp(buf, "200\n") == 0) {
            std::cout << "You win\n";
            goto next;
        } else if (strcmp(buf, "201\n") == 0) {
            std::cout << "You lost\n";
            goto next;
        } else if (strcmp(buf, "202\n") == 0) {
            std::cout << "Draw.\n";
            goto next;
        }

        over:
        data = "challenge " + std::to_string(CTOKEN.UID) + Grival.data() + "over 0\n";
        rio_writen(CTOKEN.fd, data.data(), data.size());
        return;

        next:
        COUNT_BACKWARD(3, "The next round will start in ");
        rio_readlineb(&rio, buf, MAXLINE);
        std::cout << buf;
        sstr.str(std::string());
        sstr << buf;
        sstr >> question >> difficulty >> round;
        std::cout << question;
    }
}

void challengeTransaction::Execute() {
    ctoken &CTOKEN = ctoken::getInstance();

    std::cout << "enter the player UID you want to challenge: ";
    int rivalID;
    std::cin >> rivalID;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (rivalID == CTOKEN.UID) {
        std::cout << "It is you.\n";
        return;
    }

    auto data = "challenge " + std::to_string(CTOKEN.UID) + " " + std::to_string(CTOKEN.UID) + " " +
                std::to_string(rivalID) + " invite " + std::to_string(rivalID) + '\n';
    rio_writen(CTOKEN.fd, data.data(), data.size());

    char buf[MAXLINE];
    rio_t rio;
    rio_readinitb(&rio, CTOKEN.fd);
    rio_readlineb(&rio, buf, MAXLINE);

    std::stringstream sstr(buf);
    int repcode;
    sstr >> repcode;
    if (repcode == 102) {
        std::cout << "Player " << rivalID << " refused your invitation.\n";
        return;
    } else if (repcode == 101) {
        std::cout << "Player " << rivalID << " accepted your invitation.\n";
        Grival.callerID = CTOKEN.UID;
        Grival.calleeID = rivalID;
        std::cout << "Choose difficulty(1-10):";
        int difficulty = 1;
        std::cin >> difficulty;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        data = "challenge " + std::to_string(CTOKEN.UID) + Grival.data() + "difficulty "
               + std::to_string(difficulty) + '\n';
        rio_writen(CTOKEN.fd, data.c_str(), data.size());
        std::cout << "client: message sent: " << data;
        rivalGame rG;
        rG.Execute();
    }
}

#endif //GAME_CLIENT_CHALLENGETRANSACTION_HPP
