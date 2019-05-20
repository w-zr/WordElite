//
// Created by wei on 19-5-18.
//

#ifndef GAME_GAMETABLE_HPP
#define GAME_GAMETABLE_HPP

#include <map>
#include <memory>

class table {
public:
    int callerID, calleeID, callerScore{}, calleeScore{}, round = 1, difficulty{};
    std::string word;
    double callerTime{}, calleeTime{};
    bool callerOver = false, calleeOver = false;

    table(int id1, int id2) : callerID(id1), calleeID(id2) {}
};

class GameTable {
public:
    virtual ~GameTable() = default;

    std::shared_ptr<table> FindByCallerID(int);

    std::map<int, std::shared_ptr<table>> GetTable() { return tables; };

    void addGame(int, int);

    void eraseGame(int);

    void updateGame(int UID, int callerID, int calleeID, double time);
private:
    std::map<int, std::shared_ptr<table>> tables;
};

GameTable GGameTable;

void GameTable::addGame(int callerID, int calleeID) {
    tables[callerID] = std::make_shared<table>(callerID, calleeID);
}

std::shared_ptr<table> GameTable::FindByCallerID(int callerID) {
    if(tables.find(callerID) != tables.end()) {
        return tables.find(callerID)->second;
    }
    return nullptr;
}

void GameTable::eraseGame(int callerID) {
    if(tables.find(callerID) != tables.end()){
        tables.erase(callerID);
    }
}

void GameTable::updateGame(int UID, int callerID, int calleeID, double time) {
    std::shared_ptr<table> score = FindByCallerID(callerID);
    if (score == nullptr)
        return;
    if (UID == callerID)
        score->callerTime = time;
    else if (UID == calleeID)
        score->calleeTime = time;
}

#endif //GAME_GAMETABLE_HPP
