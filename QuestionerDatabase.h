//
// Created by wey on 19-3-18.
//

#ifndef GAME_QUESTIONERDATABASE_H
#define GAME_QUESTIONERDATABASE_H

#include <memory>
#include <map>
#include "Questioner.h"

class QuestionerDatabase {
public:
    ~QuestionerDatabase() = default;

    std::shared_ptr<Questioner> FindByUID(int UID);

    void addQuestioner(int UID, std::shared_ptr<Questioner>);

    std::map<int, std::shared_ptr<Questioner>> GetPlayers() { return Questioners; };

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


#endif //GAME_QUESTIONERDATABASE_H
