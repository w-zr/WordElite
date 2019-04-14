//
// Created by wei on 19-4-13.
//

#ifndef GAME_ADDWORDTRANSACTION_H
#define GAME_ADDWORDTRANSACTION_H

#include <curl/curl.h>
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

    std::cout << "Add Word>";
    std::cin >> word;

    if (GWordDatabase.AddWord(word)) {
        GQuestionerDatabase.updateQuestioner(questioner->GetUID(), questioner->GetLevel(),
                                             questioner->GetNumberOfQuestions() + 1);

        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        if (curl) {
            using std::to_string;
            std::string url = "localhost:8080/word";
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
            std::string params = "word=" + word;
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());
            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            }
            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();

    } else {
        std::cout << "The word already existed! Failed!" << std::endl;
    }
}

#endif //GAME_ADDWORDTRANSACTION_H
