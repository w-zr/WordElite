//
// Created by wey on 19-3-18.
//

#ifndef GAME_QUESTIONERDATABASE_H
#define GAME_QUESTIONERDATABASE_H

#include <curl/curl.h>
#include "Questioner.h"

class QuestionerDatabase {
public:
    ~QuestionerDatabase() = default;

    std::shared_ptr<Questioner> FindByUID(int UID);

    void addQuestioner(int UID, std::shared_ptr<Questioner>);

    std::map<int, std::shared_ptr<Questioner>> GetQuestioners() { return Questioners; };

    void updateQuestioner(int UID, int level, int numberOfQuestions);

    void clear() { Questioners.clear(); }

private:
    std::map<int, std::shared_ptr<Questioner>> Questioners;
};

QuestionerDatabase GQuestionerDatabase;

std::shared_ptr<Questioner> QuestionerDatabase::FindByUID(int UID) {
    if (Questioners.find(UID) != Questioners.end())
        return Questioners.find(UID)->second;
    return nullptr;
}

void QuestionerDatabase::addQuestioner(int UID, std::shared_ptr<Questioner> questioner) {
    Questioners[UID] = std::move(questioner);
}

void QuestionerDatabase::updateQuestioner(int UID, int level, int numberOfQuestions) {
    std::shared_ptr<Questioner> q = FindByUID(UID);
    q.get()->SetLevel(level);
    q.get()->SetNumberOfQuestions(numberOfQuestions);

    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        using std::to_string;
        std::string url = "localhost:8080/questioners/" + to_string(UID);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        std::string params = "level=" + to_string(level) + "&numberOfQuestions=" +
                             to_string(numberOfQuestions);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}


#endif //GAME_QUESTIONERDATABASE_H
