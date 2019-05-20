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

    void Execute(int fd, const std::string &parameters) override {
        std::vector<std::shared_ptr<Player>> v;
        for (auto &it : GPlayerDatabase.GetPlayers())
            v.push_back(it.second);
        std::sort(v.begin(), v.end(), more_than_key());
        std::string data = "Rank\t\tPlayer\t\t\tExp#";
        int rank = 0;
        for (auto &it : v)
            data += std::to_string(++rank) + "\t\t" + GUserDatabase.FindByUID(it->GetUID())->GetName() + "\t\t\t" +
                    std::to_string(it->GetExp()) + "#";
        data += '\n';
        rio::writen(fd, data.data(), data.length());
    }

    struct more_than_key {
        inline bool operator()(const std::shared_ptr<Player> &player1, const std::shared_ptr<Player> &player2) {
            return (player1->GetExp() > player2->GetExp());
        }
    };
};


#endif //GAME_RANKPLAYERBYEXPTRANSACTION_H
