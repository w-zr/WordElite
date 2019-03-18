#include <unistd.h>
#include "Receiver.h"
#include "LoginTransaction.h"
#include "ChangeRoleTransactino.h"
#include "ListAllTransaction.h"
#include "AddUserTransaction.h"
#include "GetInfoTransaction.h"

constexpr unsigned int str2int(const char* str, int h = 0) {
    return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}
std::shared_ptr<User> user = nullptr;
std::string prompt;

int main() {
    std::unique_ptr<Receiver> receiver = std::make_unique<Receiver>();
    std::unique_ptr<Transaction> addUser(new AddUserTransaction());
    std::unique_ptr<Transaction> login(new LoginTransaction());
    std::unique_ptr<Transaction> getInfo(new GetInfoTransaction());
    std::unique_ptr<Transaction> changeRole(new ChangeRoleTransaction());
    std::unique_ptr<Transaction> findAllUsers(new ListAllTransaction());
    prompt = "Word Elite>";

    while (true) {
        std::cout << prompt;
        std::string s;
        std::cin >> s;
        switch (str2int(s.c_str())) {
            case str2int("signup"):
                if (user != nullptr) {
                    std::cout << "You are already logged in." << std::endl;
                    continue;
                }
                receiver->StoreAndExecute(addUser.get());
                continue;

            case str2int("login"):
                if (user != nullptr) {
                    std::cout << "You are already logged in." << std::endl;
                    continue;
                }
                receiver->StoreAndExecute(login.get());
                continue;

            case str2int("logout"):
                user = nullptr;
                std::cout << "logout succeeded" << std::endl;
                prompt = "Word Elite>";
                continue;

            case str2int("myinfo") :
                if (user == nullptr) {
                    std::cout << "Please login!" << std::endl;
                    continue;
                }
                receiver->StoreAndExecute(getInfo.get());
                continue;

            case str2int("changerole") :
                if (user == nullptr) {
                    std::cout << "Please login!" << std::endl;
                    continue;
                }
                receiver->StoreAndExecute(changeRole.get());
                continue;

            case str2int("listall") :
                if (user == nullptr) {
                    std::cout << "Please login!" << std::endl;
                    continue;
                }
                receiver->StoreAndExecute(findAllUsers.get());
                continue;
            case str2int("exit") :
                return 0;
            default:
                std::cout << "Invalid command..." << std::endl;
                continue;
        }
    }
}