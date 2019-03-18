//
// Created by wey on 19-3-17.
//

#ifndef GAME_RECEIVER_H
#define GAME_RECEIVER_H

#include <vector>
#include "Transaction.h"

class Receiver {
public:
    virtual ~Receiver() = default;

    void StoreAndExecute(Transaction *transaction){
        if(transaction) {
            _transactions.push_back(transaction);
            transaction->Execute();
        }
    }
private:
    std::vector<Transaction *> _transactions;
};


#endif //GAME_RECEIVER_H
