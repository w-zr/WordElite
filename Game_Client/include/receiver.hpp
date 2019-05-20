//
// Created by wey on 19-3-17.
//

#ifndef GAME_RECEIVER_H
#define GAME_RECEIVER_H

#include "transaction.hpp"
#include <vector>

class receiver {
public:
    virtual ~receiver() = default;
    receiver() = default;

    void StoreAndExecute(transaction *transaction){
        if(transaction) {
            _transactions.push_back(transaction);
            transaction->Execute();
        }
    }
private:
    std::vector<transaction *> _transactions;
};


#endif //GAME_RECEIVER_H
