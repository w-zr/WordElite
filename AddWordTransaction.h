//
// Created by wei on 19-4-13.
//

#ifndef GAME_ADDWORDTRANSACTION_H
#define GAME_ADDWORDTRANSACTION_H

#include "Transaction.h"

class AddWordTransaction : public Transaction{
public:
    ~AddWordTransaction() override = default;
    void Execute() override;
};

void AddWordTransaction::Execute() {
    if (user == nullptr) {
        std::cout << "Please login." << std::endl;
        return;
    }

    if (user->GetRole() == nullptr || user->GetRole()->GetRole() != "Questioner") {
        std::cout << "Please change your Role to Questioner." << std::endl;
        return;
    }

    std::string word;

    std::cout << "Input a new word: ";
    std::cin >> word;

    if (GWordDatabase.AddWord(word)) {
        GQuestionerDatabase.updateQuestioner(user->GetUID(),
                                             dynamic_cast<Questioner *>(user->GetRole().get())->GetNumberOfQuestions() +
                                             1);
        httpPost("localhost", "8080", "/words", "word=" + word, 11);
    } else
        std::cout << "The word already existed! Failed!" << std::endl;
}

#endif //GAME_ADDWORDTRANSACTION_H
