//
// Created by wey on 19-3-17.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "Role.h"

class Player : public Role {
private:
    int exp;
    int level;
    int totalPassedStage;
    int UID;
public:
    Player(int UID, int exp, int level, int totalPassedStage) : exp(exp), level(level),
                                                                totalPassedStage(totalPassedStage), UID(UID) {}

    int GetUID() {
        return UID;
    };

    std::string GetRole() override {
        return "Player";
    }

    void SetExp(int e) {
        exp = e;
    }

    int GetExp() {
        return exp;
    }

    void SetLevel(int l) {
        level = l;
    }

    int GetLevel() {
        return level;
    }

    void SetTotalPassedStage(int t) {
        totalPassedStage = t;
    }

    int GetTotalPassedStage() {
        return totalPassedStage;
    }
};


#endif //GAME_PLAYER_H
