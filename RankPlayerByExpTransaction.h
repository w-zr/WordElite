//
// Created by wey on 19-3-21.
//

#ifndef GAME_RANKPLAYERBYEXPTRANSACTION_H
#define GAME_RANKPLAYERBYEXPTRANSACTION_H

#include <vector>
#include <algorithm>
#include <iomanip>
#include "Transaction.h"

class RankPlayerByExpTransaction : public Transaction {
public:
    ~RankPlayerByExpTransaction() override = default;

    void Execute() override {
        if (user == nullptr) {
            std::cout << "Please login!" << std::endl;
            return;
        }

        std::vector<std::shared_ptr<Player>> v;
        for (auto &it : GPlayerDatabase.GetPlayers())
            v.push_back(it.second);
        std::sort(v.begin(), v.end(), more_than_key());
        std::cout << std::setw(5) << "Rank";
        std::cout << std::setw(10) << "Player";
        std::cout << std::setw(10) << "Exp" << std::endl;
        int rank = 0;
        for (auto &it : v) {
            std::cout << std::setw(5) << ++rank;
            std::cout << std::setw(10) << GUserDatabase.FindByUID(it->GetUID())->GetName();
            std::cout << std::setw(10) << it->GetExp() << std::endl;
        }
    }

    struct more_than_key {
        inline bool operator()(const std::shared_ptr<Player> &player1, const std::shared_ptr<Player> &player2) {
            return (player1->GetExp() > player2->GetExp());
        }
    };
};


#endif //GAME_RANKPLAYERBYEXPTRANSACTION_H
