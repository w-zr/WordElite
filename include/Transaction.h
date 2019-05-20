//
// Created by wey on 19-3-17.
//

#ifndef GAME_TRANSACTION_H
#define GAME_TRANSACTION_H

#include "QuestionerDatabase.h"
#include "PlayerDatabase.h"
#include "UserDatabase.h"
#include "WordDatabase.h"

extern std::shared_ptr<User> user;

class Transaction {
public:
    virtual ~Transaction() = default;

    virtual void Execute(int fd, const std::string &parameters) = 0;

};
namespace Commands{
    std::map<std::string, Transaction* > commands;
}
#endif //GAME_TRANSACTION_H
