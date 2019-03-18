//
// Created by wey on 19-3-17.
//

#ifndef GAME_TRANSACTION_H
#define GAME_TRANSACTION_H

#include "QuestionerDatabase.h"
#include "PlayerDatabase.h"
#include "UserDatabase.h"

class Transaction {
public:
    virtual ~Transaction() = default;

    virtual void Execute() = 0;
};


#endif //GAME_TRANSACTION_H
