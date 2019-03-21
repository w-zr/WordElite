//
// Created by wey on 19-3-17.
//

#ifndef GAME_QUESTIONER_H
#define GAME_QUESTIONER_H

#include "Role.h"

class Questioner : public Role {
private:
    int numberOfQuestions;
    int level;
    int UID;
public:
    Questioner(int UID, int n, int l) : numberOfQuestions(n), level(l), UID(UID) {}

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

    void SetLevel(int l) {
        level = l;
    }

    int GetLevel() {
        return level;
    }
};


#endif //GAME_QUESTIONER_H
