//
// Created by wey on 19-3-21.
//

#ifndef GAME_RANKQUESTIONERBYEXPTRANSACTION_H
#define GAME_RANKQUESTIONERBYEXPTRANSACTION_H

#include <vector>
#include <algorithm>
#include <iomanip>
#include "Transaction.h"

class RankQuestionerByExpTransaction : public Transaction {
public:
    ~RankQuestionerByExpTransaction() override = default;

    void Execute(int fd, const std::string &parameters) override {
        std::vector<std::shared_ptr<Questioner>> v;
        for (auto &it : GQuestionerDatabase.GetQuestioners())
            v.push_back(it.second);
        std::sort(v.begin(), v.end(), more_than_key());
        std::string data = "Rank\t\tQuestioner\t\t\tExp#";
        int rank = 0;
        for (auto &it : v)
            data += std::to_string(++rank) + "\t\t" + GUserDatabase.FindByUID(it->GetUID())->GetName() + "\t\t\t" +
                    std::to_string(it->GetNumberOfQuestions()) + "#";
        data += '\n';
        rio::writen(fd, data.data(), data.length());
    }

    struct more_than_key {
        inline bool operator()(const std::shared_ptr<Questioner> &questioner1,
                               const std::shared_ptr<Questioner> &questioner2) {
            return (questioner1->GetNumberOfQuestions() > questioner2->GetNumberOfQuestions());
        }
    };
};


#endif //GAME_RANKQUESTIONERBYEXPTRANSACTION_H
