#include "Receiver.h"
#include "LoginTransaction.h"
#include "ChangeRoleTransactino.h"
#include "ListAllTransaction.h"
#include "AddUserTransaction.h"
#include "GetInfoTransaction.h"
#include "RankPlayerByExpTransaction.h"
#include "RankQuestionerByExpTransaction.h"
#include "InitialProcess.h"

std::shared_ptr<User> user = nullptr;
std::string prompt;

int main() {
    std::cout << "Initialising..." << std::endl;
    InitialProcess initialProcess;
    initialProcess.init_users();
    initialProcess.init_players();
    initialProcess.init_questioners();

    GQuestionerDatabase.updateQuestioner(1, 10, 10);
    GPlayerDatabase.updatePlayer(1, 20, 20, 30);
    GQuestionerDatabase.updateQuestioner(2, 5, 5);
    GPlayerDatabase.updatePlayer(2, 5, 5, 5);
    std::unique_ptr<Receiver> receiver = std::make_unique<Receiver>();

    std::map<std::string, std::unique_ptr<Transaction>> commands;
    commands.insert(std::pair<std::string, std::unique_ptr<Transaction>>("signup", new AddUserTransaction()));
    commands.insert(std::pair<std::string, std::unique_ptr<Transaction>>("login", new LoginTransaction()));
    commands.insert(std::pair<std::string, std::unique_ptr<Transaction>>("myinfo", new GetInfoTransaction()));
    commands.insert(std::pair<std::string, std::unique_ptr<Transaction>>("changerole", new ChangeRoleTransaction()));
    commands.insert(std::pair<std::string, std::unique_ptr<Transaction>>("listall", new ListAllTransaction()));
    commands.insert(
            std::pair<std::string, std::unique_ptr<Transaction>>("rankplayers", new RankPlayerByExpTransaction()));
    commands.insert(std::pair<std::string, std::unique_ptr<Transaction>>("rankquestioners",
                                                                         new RankQuestionerByExpTransaction()));

    prompt = "Word Elite>";
    while (true) {
        std::cout << prompt;
        std::string s;
        std::cin >> s;

        if (s == "logout") {
            user = nullptr;
            std::cout << "logout succeeded" << std::endl;
            prompt = "Word Elite>";
            continue;
        }
        if (s == "exit") {
            return 0;
        }

        auto result = commands.find(s);
        if (result == commands.end()) {
            std::cout << "Invalid command..." << std::endl;
            continue;
        }
        receiver->StoreAndExecute(result->second.get());
    }
}