#include <iostream>
#include <unistd.h>
#include <memory>
#include "User.h"
#include "AddUserTransaction.h"
#include "UserDatabase.h"
#include "ListAllTransaction.h"
#include "Receiver.h"

int main() {

    std::string prompt = "Word Elite>";
    std::shared_ptr<User> user = nullptr;
    std::unique_ptr<Receiver> receiver = std::make_unique<Receiver>();

    while (true) {
        if (isatty(STDIN_FILENO)) {
            std::cout << prompt;
        }
        std::string s;
        std::cin >> s;
        if (s == "signup") {
            if (user != nullptr) {
                std::cout << "You are already logged in." << std::endl;
                continue;
            }
            std::string username;
            std::string password;

            std::cout << "Input username:";
            std::cin >> username;
            std::cout << "Input password:";
            std::cin >> password;

            std::unique_ptr<Transaction> addUser(new AddUserTransaction(username, password));
            receiver->StoreAndExecute(addUser.get());

            continue;
        } else if (s == "login") {
            if (user != nullptr) {
                std::cout << "You are already logged in." << std::endl;
                continue;
            }
            std::string username;
            std::string password;

            std::cout << "Input username:";
            std::cin >> username;
            std::cout << "Input password:";
            std::cin >> password;

            std::shared_ptr<User> u = GUserDatabase.FindByUsername(username);
            if(u == nullptr) {
                std::cout << "User does not exist!" << std::endl;
                continue;
            }

            if (u->GetPass() == password) {
                std::cout << "Login succeded!" << std::endl;
                prompt = u->GetName() + ">";
                user = std::move(u);
            } else {
                std::cout << "Password dismatch!" << std::endl;
            }

            continue;
        } else if (s == "logout") {
            user = nullptr;
            prompt = "Word Elite>";
            continue;
        } else if (s == "list") {
            if (user == nullptr) {
                std::cout << "Please login!" << std::endl;
                continue;
            }
            std::unique_ptr<Transaction> findAllUsers(new ListAllTransaction());
            receiver->StoreAndExecute(findAllUsers.get());

            continue;
        } else if (s == "exit") {
            break;
        } else {
            std::cout << "please input legal commands." << std::endl;
        }
    }

    return 0;
}