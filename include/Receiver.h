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

    void StoreAndExecute(const int fd, const std::string &command, const std::string &parameters) {
        std::cout << "command: " << command << " message: " << parameters << std::endl;
        auto transaction = Commands::commands.find(command);
        if (transaction != Commands::commands.end()) {
            std::cout << "command found\n";
            transaction->second->Execute(fd, parameters);
        }
    }

};


#endif //GAME_RECEIVER_H
