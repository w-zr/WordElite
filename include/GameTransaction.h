//
// Created by wei on 19-4-11.
//

#ifndef GAME_GAMETRANSACTION_H
#define GAME_GAMETRANSACTION_H

#include "Transaction.h"

class GameTransaction : public Transaction {
public:
    ~GameTransaction() override = default;

    void Execute(int fd, const std::string &parameters) override;
};

void GameTransaction::Execute(int fd, const std::string &parameters) {
    int uid, value;
    std::string param;
    std::stringstream sstr(parameters);
    sstr >> uid >> param >> value;
    auto u = GUserDatabase.FindByUID(uid);

    rio::initb(fd);
    if (param == "difficulty") {
        auto result = GWordDatabase.GetOneWordByDifficulty(value);
        if (result == nullptr) {
            rio::writen(fd, "0\n", 3);
            std::cout << "message sent\n";
            return;
        }
        auto question = result->word + '\n';
        rio::writen(fd, question.data(), question.length());
        std::cout << "message sent\n";
    } else if (param == "check") {
        if (value == 200) {
            std::cout << "Right answer\n";
            GPlayerDatabase.updatePlayer(uid, dynamic_cast<Player *>((u->GetRole().get()))->GetExp() + 50,
                                         dynamic_cast<Player *>((u->GetRole().get()))->GetTotalPassedStage() + 1);
        } else
            std::cout << "Wrong answer\n";
    }
}

#endif //GAME_GAMETRANSACTION_H
