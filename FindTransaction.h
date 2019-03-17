//
// Created by wey on 19-3-17.
//

#ifndef GAME_FINDTRANSACTION_H
#define GAME_FINDTRANSACTION_H

#include "Transaction.h"

class FindTransaction : public Transaction {
public:
    ~FindTransaction() override = default;

    void Execute() override = 0;
};


#endif //GAME_FINDTRANSACTION_H
