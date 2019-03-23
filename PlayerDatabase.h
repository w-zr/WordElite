//
// Created by wey on 19-3-18.
//

#ifndef GAME_PLAYERDATABASE_H
#define GAME_PLAYERDATABASE_H

#include "Player.h"
#include <curl/curl.h>

class PlayerDatabase {
public:
    ~PlayerDatabase() = default;

    std::shared_ptr<Player> FindByUID(int UID);

    std::map<int, std::shared_ptr<Player>> GetPlayers() { return Players; };

    void addPlayer(int UID, std::shared_ptr<Player>);

    void updatePlayer(int UID, int exp, int level, int totalPassedStage);

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

void PlayerDatabase::updatePlayer(int UID, int exp, int level, int totalPassedStage) {
    std::shared_ptr<Player> p = FindByUID(UID);
    p.get()->SetExp(exp);
    p.get()->SetLevel(level);
    p.get()->SetTotalPassedStage(totalPassedStage);

    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        using std::to_string;
        std::string url = "localhost:8080/players/" + to_string(UID);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        std::string params = "exp=" + to_string(exp) + "&level=" + to_string(level) + "&totalPassedStage=" +
                             to_string(totalPassedStage);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

#endif //GAME_PLAYERDATABASE_H
