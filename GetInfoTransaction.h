//
// Created by wey on 19-3-18.
//

#ifndef GAME_GETINFOTRANSACTION_H
#define GAME_GETINFOTRANSACTION_H

#include "Transaction.h"

class GetInfoTransaction : public Transaction {
public:
    ~GetInfoTransaction() override = default;

    void Execute() override {
        if (user == nullptr) {
            std::cout << "Please login!" << std::endl;
            return;
        }
        if (user->GetRole() == nullptr)
            std::cout << "You do not have a role now." << std::endl;
        else
            std::cout << "Your current role is: " << user->GetRole()->GetRole() << std::endl;

        std::shared_ptr<Player> p = GPlayerDatabase.FindByUID(user->GetUID());
        std::shared_ptr<Questioner> q = GQuestionerDatabase.FindByUID(user->GetUID());
        std::cout
                << "As a Player: Your EXP: " << p->GetExp()
                << ". Your Level: " << p->GetLevel() << ". Your PassedStage: " << p->GetTotalPassedStage()
                << std::endl << "As a Questioner: Your questions: " << q->GetNumberOfQuestions()
                << " . Your Level: " << q->GetLevel() << std::endl;
    }
};


#endif //GAME_GETINFOTRANSACTION_H
