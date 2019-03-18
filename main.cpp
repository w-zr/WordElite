#include <iostream>
#include <unistd.h>
#include <memory>
#include "User.h"
#include "AddUserTransaction.h"
#include "UserDatabase.h"
#include "ListAllTransaction.h"
#include "Receiver.h"
#include "ChangeRoleTransactino.h"
#include "QuestionerDatabase.h"


constexpr unsigned int str2int(const char* str, int h = 0) {
    return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

std::shared_ptr<User> user = nullptr;

int main() {
    std::string prompt = "Word Elite>";
    std::unique_ptr<Receiver> receiver = std::make_unique<Receiver>();

    while (true) {
        std::cout << prompt;
        std::string s;
        std::cin >> s;

        switch (str2int(s.c_str())) {
            case str2int("signup"): {
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
            }

            case str2int("login"): {
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
                if (u == nullptr) {
                    std::cout << "User does not exist!" << std::endl;
                    continue;
                }

                if (u->GetPass() == password) {
                    std::cout << "Login succeeded!" << std::endl;
                    prompt = u->GetName() + ">";
                    user = std::move(u);
                } else {
                    std::cout << "Password mismatch!" << std::endl;
                }
                continue;
            }

            case str2int("logout"): {
                user = nullptr;
                std::cout << "logout succeeded" << std::endl;
                prompt = "Word Elite>";
                continue;
            }

            case str2int("myinfo") : {
                if (user == nullptr) {
                    std::cout << "Please login!" << std::endl;
                    continue;
                }

                std::shared_ptr<Player> p = GPlayerDatabase.FindByUID(user->GetUID());
                std::shared_ptr<Questioner> q = GQuestionerDatabase.FindByUID(user->GetUID());
                if (user->GetRole() == nullptr)
                    std::cout << "You do not have a role now." << std::endl;
                else
                    std::cout << "Your current role is: " << user->GetRole()->GetRole() << std::endl;
                std::cout
                        << "As a Player: Your EXP: " << p->GetExp()
                        << ". Your Level: " << p->GetLevel() << ". Your PassedStage: " << p->GetTotalPassedStage()
                        << std::endl << "As a Questioner: Your questions: " << q->GetNumberOfQuestions()
                        << " . Your Level: " << q->GetLevel() << std::endl;

                continue;
            }

            case str2int("changerole") : {
                if (user == nullptr) {
                    std::cout << "Please login!" << std::endl;
                    continue;
                }

                std::cout << "Input the role you want to be(Player/Questioner): ";
                std::string r;
                std::cin >> r;
                std::shared_ptr<Role> role;
                if (r == "Player")
                    role = GPlayerDatabase.FindByUID(user->GetUID());
                else if (r == "Questioner") {
                    role = GQuestionerDatabase.FindByUID(user->GetUID());
                } else {
                    std::cout << "invalid role! try again..." << std::endl;
                    continue;
                }

                std::unique_ptr<Transaction> changeRole(new ChangeRoleTransaction(role));
                receiver->StoreAndExecute(changeRole.get());

                continue;
            }

            case str2int("list") : {
                if (user == nullptr) {
                    std::cout << "Please login!" << std::endl;
                    continue;
                }
                std::unique_ptr<Transaction> findAllUsers(new ListAllTransaction());
                receiver->StoreAndExecute(findAllUsers.get());
                continue;
            }
            case str2int("exit") : {
                return 0;
            }
            default:
                continue;
        }
    }
}