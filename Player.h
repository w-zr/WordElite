//
// Created by wey on 19-3-17.
//

#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "Role.h"

class Player : public Role {
private:
    int exp;
    int totalPassedStage;
    int UID;
public:
    Player(int UID, int e, int s) : exp(e), totalPassedStage(s), UID(UID) {}

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

    void SetTotalPassedStage(int t) {
        totalPassedStage = t;
    }

    int GetTotalPassedStage() {
        return totalPassedStage;
    }
};


#endif //GAME_PLAYER_H
