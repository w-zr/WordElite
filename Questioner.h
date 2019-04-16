//
// Created by wey on 19-3-17.
//

#ifndef GAME_QUESTIONER_H
#define GAME_QUESTIONER_H

#include "Role.h"

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


#endif //GAME_QUESTIONER_H
