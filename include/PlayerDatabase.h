#include <utility>

//
// Created by wey on 19-3-18.
//

#ifndef GAME_PLAYERDATABASE_H
#define GAME_PLAYERDATABASE_H

#include "HttpRequest.h"
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


class PlayerDatabase {
public:
    ~PlayerDatabase() = default;

    std::shared_ptr<Player> FindByUID(int UID);

    std::map<int, std::shared_ptr<Player>> GetPlayers() { return Players; };

    void addPlayer(int UID, std::shared_ptr<Player>);

    void updatePlayer(int UID, int exp, int totalPassedStage);

private:
    std::map<int, std::shared_ptr<Player>> Players;
};

PlayerDatabase GPlayerDatabase;

std::shared_ptr<Player> PlayerDatabase::FindByUID(int UID) {
    if (Players.find(UID) != Players.end())
        return Players.find(UID)->second;
    return nullptr;
}

void PlayerDatabase::addPlayer(int UID, std::shared_ptr<Player >e) {
    Players[UID] = std::move(e);
}

void PlayerDatabase::updatePlayer(int UID, int exp, int totalPassedStage) {
    std::shared_ptr<Player> p = FindByUID(UID);
    p.get()->SetExp(exp);
    p.get()->SetTotalPassedStage(totalPassedStage);

    using std::to_string;
    httpRequest("PUT", "localhost", "8080", "/players/" + to_string(UID), "exp=" + to_string(exp) + "&totalPassedStage=" +
                                                                          to_string(totalPassedStage));
}
#endif //GAME_PLAYERDATABASE_H
