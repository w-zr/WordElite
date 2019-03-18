//
// Created by wey on 19-3-18.
//

#ifndef GAME_PLAYERDATABASE_H
#define GAME_PLAYERDATABASE_H

#include "Player.h"

class PlayerDatabase {
public:
    ~PlayerDatabase() = default;

    std::shared_ptr<Player> FindByUID(int UID);

    std::map<int, std::shared_ptr<Player>> GetPlayers() { return Players; };

    void addPlayer(int UID, std::shared_ptr<Player>);

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

#endif //GAME_PLAYERDATABASE_H
