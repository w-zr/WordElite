#include <utility>

#include <random>

//
// Created by wei on 19-4-12.
//

#ifndef GAME_WORDDATABASE_H
#define GAME_WORDDATABASE_H

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>

typedef struct {
    int difficulty{};
    std::string word;
} Word;

class WordDatabase {
public:
    ~WordDatabase() = default;
    std::shared_ptr<Word> GetOneWordByDifficulty(int difficulty);
    bool AddWord(const std::string& word);

private:
    std::map<int, std::shared_ptr<Word>> Words;
};

WordDatabase GWordDatabase;

std::shared_ptr<Word> WordDatabase::GetOneWordByDifficulty(int difficulty) {
    std::vector<std::shared_ptr<Word>> words;
    for (const auto &word : Words) {
        if (word.second.get()->difficulty == difficulty) {
            words.push_back(word.second);
        }
    }
    if(words.empty()) {
        return nullptr;
    }
    std::shuffle(words.begin(), words.end(), std::mt19937(std::random_device()()));
    return std::make_shared<Word>(*words.begin()->get());
}

bool WordDatabase::AddWord(const std::string& word) {
    std::hash<std::string> hash_fn;
    size_t hash = hash_fn(word);
    if (Words.count(hash) == 0) {
        std::shared_ptr<Word> NewWord = std::make_shared<Word>();
        NewWord->word = word;
        NewWord->difficulty = word.length();
        Words[hash] = NewWord;
        return true;
    }
    return false;
}

#endif //GAME_WORDDATABASE_H
