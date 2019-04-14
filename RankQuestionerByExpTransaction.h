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

    void Execute() override {
        if (user == nullptr) {
            std::cout << "Please login!" << std::endl;
            return;
        }
        std::vector <std::shared_ptr<Questioner>> v;
        for (auto &it : GQuestionerDatabase.GetQuestioners())
            v.push_back(it.second);
        std::sort(v.begin(), v.end(), more_than_key());
        std::cout << std::setw(5) << "Rank";
        std::cout << std::setw(10) << "Questioner";
        std::cout << std::setw(10) << "Exp" << std::endl;
        int rank = 0;
        for (auto &it : v) {
            std::cout << std::setw(5) << ++rank;
            std::cout << std::setw(10) << GUserDatabase.FindByUID(it->GetUID())->GetName();
            std::cout << std::setw(10) << it->GetNumberOfQuestions() << std::endl;
        }
    }

    struct more_than_key {
        inline bool operator()(const std::shared_ptr <Questioner> &questioner1,
                               const std::shared_ptr <Questioner> &questioner2) {
            return (questioner1->GetNumberOfQuestions() > questioner2->GetNumberOfQuestions());
        }
    };
};


#endif //GAME_RANKQUESTIONERBYEXPTRANSACTION_H
