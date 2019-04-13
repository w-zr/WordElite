//
// Created by wei on 19-4-11.
//

#ifndef GAME_GAMETRANSACTION_H
#define GAME_GAMETRANSACTION_H

#include "Transaction.h"
#include <unistd.h>

class GameTransaction : public Transaction {
public:
    ~GameTransaction() override = default;

    void Execute() override {
        if (user == nullptr) {
            std::cout << "Please login." << std::endl;
            return;
        }

        if (user->GetRole() == nullptr || user->GetRole()->GetRole() != "Player") {
            std::cout << "Please change your Role to Player." << std::endl;
            return;
        }
        std::system("clear");
        auto question = GWordDatabase.GetOneWordByDifficulty(1)->word;
        std::cout << "Your Question: " << question << std::endl;
        int x = 3;
        for (auto i = x; i > 0; --i) {
            std::cout << "You have " << i << " seconds to remember.\r" << std::flush;
            sleep(1);
        }
        std::system("clear");
        std::cout << "Input your answer: ";
        std::string answer;
        std::cin >> answer;
        if (answer == question) {
            std::cout << "Right Answer" << std::endl;
            GPlayerDatabase.updatePlayer(player->GetUID(), player->GetExp() + 50, player->GetLevel(),
                                         player->GetTotalPassedStage() + 1);
        } else
            std::cout << "Wrong Answer" << std::endl;
    }
};

#endif //GAME_GAMETRANSACTION_H
