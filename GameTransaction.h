//
// Created by wei on 19-4-11.
//

#ifndef GAME_GAMETRANSACTION_H
#define GAME_GAMETRANSACTION_H

#include "Transaction.h"
#include <unistd.h>

const int MAXTIME = 5;
class GameTransaction : public Transaction {
public:
    ~GameTransaction() override = default;

    void Execute() override;
};

void GameTransaction::Execute() {
    if (user == nullptr) {
        std::cout << "Please login." << std::endl;
        return;
    }
    if (user->GetRole() == nullptr || user->GetRole()->GetRole() != "Player") {
        std::cout << "Please change your Role to Player." << std::endl;
        return;
    }

    int round = 1;
    int difficulty = 1;
    while (true) {
        if (!GWordDatabase.GetOneWordByDifficulty(difficulty)) {
            std::cout << "No word in wordbank." << std::endl;
            return;
        }

        std::system("clear");
        auto question = GWordDatabase.GetOneWordByDifficulty(difficulty)->word;
        std::cout << "\tRound " << round << "/" << difficulty << "\tDifficulty: " << difficulty << std::endl
                  << std::endl << "Your Question: " << question << std::endl << std::endl;

        for (auto i = std::max(MAXTIME - difficulty + 1, 1); i > 0; --i) {
            std::cout << "You have " << i << " seconds to remember.\r" << std::flush;
            sleep(1);
        }

        std::system("clear");
        std::cout << "Input your answer: ";
        std::string answer;
        std::cin >> answer;
        if (answer == question) {
            std::cout << "Right Answer" << std::endl << "Exp +50" << std::endl << "Next round will start in 3 seconds."
                      << std::endl;
            GPlayerDatabase.updatePlayer(player->GetUID(), player->GetExp() + 50, player->GetLevel(),
                                         player->GetTotalPassedStage() + 1);
            round++;
            if (round == difficulty) {
                round = 1;
                difficulty++;
            }

            sleep(3);
        } else {
            std::cout << "Wrong Answer!" << std::endl << "Game Failed." << std::endl
                      << "Return to main menu in 3 seconds." << std::endl;
            sleep(3);
            std::system("clear");
            break;
        }
    }
}

#endif //GAME_GAMETRANSACTION_H
