//
// Created by wey on 19-3-18.
//

#ifndef GAME_QUESTIONERDATABASE_H
#define GAME_QUESTIONERDATABASE_H

#include "Role.h"
#include "HttpRequest.h"

class Questioner : public Role {
private:
    int numberOfQuestions;
    int UID;
public:
    Questioner(int UID, int n) : numberOfQuestions(n), UID(UID) {}

    int GetUID() {
        return UID;
    }

    std::string GetRole() override {
        return "Questioner";
    }

    void SetNumberOfQuestions(int n) {
        numberOfQuestions = n;
    }

    int GetNumberOfQuestions() {
        return numberOfQuestions;
    }
};

class QuestionerDatabase {
public:
    ~QuestionerDatabase() = default;

    std::shared_ptr<Questioner> FindByUID(int UID);

    void addQuestioner(int UID, std::shared_ptr<Questioner>);

    std::map<int, std::shared_ptr<Questioner>> GetQuestioners() { return Questioners; };

    void updateQuestioner(int UID, int numberOfQuestions);

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

void QuestionerDatabase::updateQuestioner(int UID, int numberOfQuestions) {
    std::shared_ptr<Questioner> q = FindByUID(UID);
    q.get()->SetNumberOfQuestions(numberOfQuestions);
    httpRequest("PUT", "localhost", "8080", "/questioners/" + std::to_string(UID), "numberOfQuestions=" + std::to_string(numberOfQuestions));
}


#endif //GAME_QUESTIONERDATABASE_H
