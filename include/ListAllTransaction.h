//
// Created by wey on 19-3-17.
//

#ifndef GAME_LISTALLTRANSACTION_H
#define GAME_LISTALLTRANSACTION_H

#include "Transaction.h"

class ListAllTransaction : public Transaction {
public:
    ~ListAllTransaction() override = default;

    void Execute(int fd, const std::string &parameters) override {
        std::stringstream sstr(parameters);
        int uid;
        sstr >> uid;

        std::string data;
        for (auto &it : GUserDatabase.GetUsers()) {
            if (it.first == uid)
                data += "Your Account: \t";
            data += "UID: " + std::to_string(it.first) + "\t\tusername: " + it.second->GetName() + "\t\trole: " +
                    (it.second->GetRole() == nullptr ? "null" : it.second->GetRole()->GetRole()) + '#';
        }
        data += '\n';
        rio::writen(fd, data.data(), data.length());
    }
};


#endif //GAME_LISTALLTRANSACTION_H
