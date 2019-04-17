//
// Created by wey on 19-3-18.
//

#ifndef GAME_PLAYERDATABASE_H
#define GAME_PLAYERDATABASE_H

#include "Player.h"
#include "HttpRequest.h"

class PlayerDatabase {
public:
    ~PlayerDatabase() = default;

    std::shared_ptr<Player> FindByUID(int UID);

    std::map<int, std::shared_ptr<Player>> GetPlayers() { return Players; };

    void addPlayer(int UID, std::shared_ptr<Player>);

    void updatePlayer(int UID, int exp, int totalPassedStage);

    void clear() { Players.clear(); }

private:
    std::map<int, std::shared_ptr<Player>> Players;
};

PlayerDatabase GPlayerDatabase;

std::shared_ptr<Player> PlayerDatabase::FindByUID(int UID) {
    if (Players.find(UID) != Players.end())
        return Players.find(UID)->second;
    return nullptr;
}

void PlayerDatabase::addPlayer(int UID, std::shared_ptr<Player> e) {
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
