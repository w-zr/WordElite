//
// Created by wey on 19-3-21.
//

#ifndef GAME_INITIALPROCESS_H
#define GAME_INITIALPROCESS_H

#include <iostream>
#include <document.h>
#include "HttpRequest.h"

using namespace rapidjson;

class InitialProcess {
public:
    static void init_users() {
        Document document;
        document.Parse(httpRequest("GET", "localhost", "8080", "/users", ""));
        const Value &users = document["users"];
        for (auto &v : users.GetArray()) {

            int id = v["id"].GetInt();
            std::string username = v["username"].GetString();
            std::string password = v["password"].GetString();
            int exp = v["exp"].GetInt();
            int totalPassedStage = v["totalPassedStage"].GetInt();
            int numberOfQuestions = v["numberOfQuestions"].GetInt();

            GUserDatabase.addUser(id, std::make_shared<User>(id, username, password));
            GPlayerDatabase.addPlayer(id, std::make_shared<Player>(id, exp, totalPassedStage));
            GQuestionerDatabase.addQuestioner(id, std::make_shared<Questioner>(id, numberOfQuestions));
            IN_UID++;
        }
    }

    static void init_wordbank() {
        Document document;
        document.Parse(httpRequest("GET", "localhost", "8080", "/words", ""));
        const Value &words = document["words"];
        for (auto &v : words.GetArray()) {
            GWordDatabase.addWord(v["word"].GetString());
        }
    }
};

#endif //GAME_INITIALPROCESS_H
