//
// Created by wey on 19-3-18.
//

#ifndef GAME_CHANGEROLETRANSACTION_H
#define GAME_CHANGEROLETRANSACTION_H

#include "Transaction.h"

class ChangeRoleTransaction : public Transaction {
public:
    ~ChangeRoleTransaction() override = default;

    void Execute(int fd, const std::string &parameters) override {
        std::stringstream sstr(parameters);
        int uid;
        std::string r, data;
        sstr >> uid >> r;

        std::shared_ptr<Role> role;
        if (r == "Player" || r == "P" || r == "p" || r == "player") {
            std::cout << r << std::endl;
            role = GPlayerDatabase.FindByUID(uid);
            data = "201\n";
        }
        else if (r == "Questioner" || r == "Q" || r == "q" || r == "questioner") {
            std::cout << r << std::endl;
            role = GQuestionerDatabase.FindByUID(uid);
            data = "202\n";
        }
        else
            data = "500\n";
        GUserDatabase.FindByUID(uid)->SetRole(role);
        rio::writen(fd, data.data(), data.length());
        std::cout << "message sent\n";
    }
};


#endif //GAME_CHANGEROLETRANSACTION_H
