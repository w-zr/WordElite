//
// Created by wei on 19-4-11.
//

#ifndef GAME_GAMETRANSACTION_H
#define GAME_GAMETRANSACTION_H

#include "Transaction.h"

#define COUNT_BACKWARD(x, express)                                                      \
do{                                                                                     \
    for (auto i = (x); i > 0; --i) {                                                    \
        std::cout << (express) << i << " seconds.\r" << std::flush;            \
        sleep(1);                                                                       \
    }                                                                                   \
}while(0)

constexpr auto MAX_TIME = 5;

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
    std::cout << "Choose difficulty(1-10):";
    int round = 1;
    int difficulty;
    std::cin >> difficulty;
    while (true) {
        if (!GWordDatabase.GetOneWordByDifficulty(difficulty)) {
            std::cout << "There is no word with chosen difficulty" << std::endl;
            return;
        }

        std::system("clear");
        auto question = GWordDatabase.GetOneWordByDifficulty(difficulty)->word;
        std::cout << "\tRound " << round << "/" << difficulty << "\tDifficulty: " << difficulty << std::endl
                  << std::endl << "Your Question: " << question << std::endl << std::endl;

        COUNT_BACKWARD(std::max(MAX_TIME - difficulty + 1, 1), "You have ");

        std::system("clear");
        std::cout << "Input your answer: ";
        std::string answer;
        std::cin >> answer;
        if (answer == question) {
            std::cout << "Correct" << std::endl << "Exp +50" << std::endl;
            GPlayerDatabase.updatePlayer(user->GetUID(), dynamic_cast<Player *>((user->GetRole().get()))->GetExp() + 50,
                                         dynamic_cast<Player *>((user->GetRole().get()))->GetTotalPassedStage() + 1);
            if (round == difficulty) {
                round = 0;
                difficulty++;
            }
            round++;
            COUNT_BACKWARD(5, "The next round will start in ");
            std::system("clear");
        } else {
            std::cout << "Wrong" << std::endl<< std::endl << "\tGame Over" << std::endl;
            COUNT_BACKWARD(5, "Please wait for ");
            std::system("clear");
            break;
        }
    }
}

#endif //GAME_GAMETRANSACTION_H
