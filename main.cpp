#include <iostream>
#include <unistd.h>
#include "User.h"
#include "AddUserTransaction.h"
#include "UserDatabase.h"
#include "FindAllTransaction.h"

int main() {
    while (true) {
        if (isatty(STDIN_FILENO)) {
            std::cout << "Word Elite>";
        }
        std::string s;
        std::cin >> s;
        if (s == "signup") {
            int UID;
            std::string username;
            std::string password;

            std::cout << "Input UID:";
            std::cin >> UID;
            std::cout << "Input username:";
            std::cin >> username;
            std::cout << "Input password:";
            std::cin >> password;

            Transaction *addUser(new AddUserTransaction(UID, username, password));
            addUser->Execute();
            delete addUser;

            continue;
        } else if (s == "list") {
            Transaction *findAllUsers(new FindAllTransaction());
            findAllUsers->Execute();
            delete (findAllUsers);

            continue;
        } else if (s == "exit") {
            break;
        } else {
            std::cout << "please input legal commands" << std::endl;
        }
    }

    return 0;
}