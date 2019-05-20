//
// Created by wei on 19-5-18.
//

#ifndef GAME_CHALLENGETRANSACION_HPP
#define GAME_CHALLENGETRANSACION_HPP

#include <sstream>
#include "Transaction.h"
#include "rio.hpp"
#include "GameTable.hpp"

class ChallengeTransaction : public Transaction {
    ~ChallengeTransaction() override = default;

    void Execute(int fd, const std::string &parameters) override;

    void Caster(int callerID);  //发词
};

void ChallengeTransaction::Execute(int fd, const std::string &parameters) {
    std::stringstream sstr(parameters);
    int UID, callerID, calleeID, value;
    std::string param;

    sstr >> UID >> callerID >> calleeID >> param >> value;
    printf("%d\n", value);
    auto caller = GUserDatabase.FindByUID(callerID);
    auto callee = GUserDatabase.FindByUID(calleeID);
    if (param == "invite") {
        if (callee == nullptr) {
            rio::writen(fd, "400\n", 4);
            return;
        } else if (callee->GetFd() == -1) {
            rio::writen(fd, "401\n", 4);
            return;
        } else if (caller->GetRole() == nullptr || callee->GetRole() == nullptr) {
            rio::writen(fd, "402\n", 4);
            return;
        }
        auto data = "100 " + std::to_string(UID) + " " + caller->GetName() + '\n';
        rio::writen(callee->GetFd(), data.data(), data.size());
    } else if (param == "ack") {
        if (value == 200) {
            rio::writen(caller->GetFd(), "101\n", 4);
            GGameTable.addGame(callerID, calleeID);
        }
        else {
            rio::writen(caller->GetFd(), "102\n", 4);
            return;
        }
    }
    else if (param == "check") {
        GGameTable.updateGame(UID, callerID, calleeID, value);
        auto t = GGameTable.FindByCallerID(callerID);
        if (!(t->callerTime == 0 || t->calleeTime == 0)) {
            if (t->callerTime == -100 && t->calleeTime != -100) {
                t->callerScore -= 20;
                t->calleeScore += 50;
                rio::writen(caller->GetFd(), "601\n", 4);
                rio::writen(callee->GetFd(), "601\n", 4);
                return;
            }
            if (t->callerTime == -100 && t->calleeTime == -100) {
                t->callerScore -= 20;
                t->calleeScore -= 20;
                rio::writen(caller->GetFd(), "600\n", 4);
                rio::writen(callee->GetFd(), "600\n", 4);
                return;
            }
            if (t->callerTime != -100 && t->calleeTime == -100) {
                t->callerScore += 50;
                t->calleeScore -= 20;
                rio::writen(caller->GetFd(), "602\n", 4);
                rio::writen(callee->GetFd(), "602\n", 4);
                return;
            }
            if (t->callerTime > t->calleeTime) {
                t->callerScore -= 10;
                t->calleeScore += 50;
                t->callerTime = 0;
                t->calleeTime = 0;
                rio::writen(caller->GetFd(), "201\n", 4);
                std::cout << "caller fd: " << caller->GetFd() << std::endl;
                rio::writen(callee->GetFd(), "200\n", 4);
                std::cout << "callee fd: " << callee->GetFd() << std::endl;
            } else if (t->callerTime < t->calleeTime) {
                t->callerScore += 50;
                t->calleeScore -= 10;
                t->callerTime = 0;
                t->calleeTime = 0;
                rio::writen(callee->GetFd(), "201\n", 4);
                std::cout << "callee fd: " << callee->GetFd() << std::endl;
                rio::writen(caller->GetFd(), "200\n", 4);
                std::cout << "caller fd: " << caller->GetFd() << std::endl;
            } else if (t->callerTime == t->calleeTime) {
                t->callerScore += 20;
                t->calleeScore += 20;
                t->callerTime = 0;
                t->calleeTime = 0;
                rio::writen(callee->GetFd(), "202\n", 5);
                std::cout << "callee fd: " << callee->GetFd() << std::endl;
                rio::writen(caller->GetFd(), "202\n", 4);
                std::cout << "caller fd: " << caller->GetFd() << std::endl;
            }
            Caster(callerID);
        }
    } else if (param == "difficulty") {
        auto t = GGameTable.FindByCallerID(callerID);
        t->difficulty = value;

        Caster(callerID);
    } else if (param == "over") {
        auto t = GGameTable.FindByCallerID(callerID);
        if(UID == callerID) {
            t->callerOver = true;
        } else if(UID == calleeID) {
            t->calleeOver = true;
        }

        if(t->callerOver && t->calleeOver) {
            auto callerP = dynamic_cast<Player *>(caller->GetRole().get());
            auto calleeP = dynamic_cast<Player *>(callee->GetRole().get());
            GPlayerDatabase.updatePlayer(callerID, callerP->GetExp() + t->callerScore,
                                         callerP->GetTotalPassedStage() + t->round);
            GPlayerDatabase.updatePlayer(calleeID, calleeP->GetExp() + t->callerScore,
                                         calleeP->GetTotalPassedStage() + t->round);
            GGameTable.eraseGame(callerID);
        }
    }
}

void ChallengeTransaction::Caster(int callerID) {
    auto t = GGameTable.FindByCallerID(callerID);
    auto caller = GUserDatabase.FindByUID(callerID);
    auto callee = GUserDatabase.FindByUID(t->calleeID);
    auto result = GWordDatabase.GetOneWordByDifficulty(t->difficulty);
    if (result == nullptr) {
        rio::writen(caller->GetFd(), "0\n", 2);
        rio::writen(callee->GetFd(), "0\n", 2);
        std::cout << "message sent\n";
        return;
    }
    auto question = result->word + " " + std::to_string(t->difficulty) + ' ' + std::to_string(t->round) + '\n';
    rio::writen(caller->GetFd(), question.data(), question.length());
    rio::writen(callee->GetFd(), question.data(), question.length());
    std::cout << "message sent: " << question << std::endl;
    if (t->round == t->difficulty) {
        t->round = 0;
        t->difficulty++;
    }
    t->round++;
}

#endif //GAME_CHALLENGETRANSACION_HPP
