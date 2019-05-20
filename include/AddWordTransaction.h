//
// Created by wei on 19-4-13.
//

#ifndef GAME_ADDWORDTRANSACTION_H
#define GAME_ADDWORDTRANSACTION_H

#include "Transaction.h"

class AddWordTransaction : public Transaction{
public:
    ~AddWordTransaction() override = default;
    void Execute(int fd, const std::string &parameters) override;
};

void AddWordTransaction::Execute(int fd, const std::string &parameters) {
    std::stringstream sstr(parameters);
    int uid;
    std::string word, data;
    sstr >> uid >> word;
    auto u = GUserDatabase.FindByUID(uid);

    if (u->GetRole() != nullptr && GWordDatabase.addWord(word)) {
        std::cout << "new Word added\n";
        GQuestionerDatabase.updateQuestioner(uid,
                                             dynamic_cast<Questioner *>(u->GetRole().get())->GetNumberOfQuestions() +
                                             1);
        std::cout << httpRequest("POST", "localhost", "8080", "/words", "word=" + word);
        data = "200\n";
    } else
        data = "500\n";
    rio::writen(fd, data.data(), data.size());
    std::cout << "message sent\n";
}

#endif //GAME_ADDWORDTRANSACTION_H
