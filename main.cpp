#include "Receiver.h"
#include "LoginTransaction.h"
#include "ChangeRoleTransaction.h"
#include "ListAllTransaction.h"
#include "AddUserTransaction.h"
#include "GetInfoTransaction.h"
#include "RankPlayerByExpTransaction.h"
#include "RankQuestionerByExpTransaction.h"
#include "InitialProcess.h"
#include "GameTransaction.h"
#include "AddWordTransaction.h"

#define HELP_INFO                               \
std::cout << std::endl;                         \
std::cout << "HELP LIST" << std::endl;          \
std::cout << "help\t--帮助信息" << std::endl;    \
std::cout << "signup\t--注册" << std::endl;      \
std::cout << "login\t--登录" << std::endl;       \
std::cout << "logout\t--注销" << std::endl;      \
std::cout << "myinfo\t--账户信息" << std::endl;   \
std::cout << "chgr\t--更改用户身份" << std::endl;  \
std::cout << "lsu\t--列出所有用户" << std::endl;   \
std::cout << "rkps\t--闯关者排行" << std::endl;    \
std::cout << "rkqs\t--出题者排行" << std::endl;    \
std::cout << "game\t--开始新游戏" << std::endl;    \
std::cout << "addw\t--添加新词" << std::endl;     \
std::cout << "clear\t--清屏" << std::endl;        \
std::cout << "exit\t--退出" << std::endl;         \
std::cout << std::endl;

#define BANNER                                                  \
"##      ##  #######  ########  ########  \n"                   \
"##  ##  ## ##     ## ##     ## ##     ## \n"                   \
"##  ##  ## ##     ## ##     ## ##     ## \n"                   \
"##  ##  ## ##     ## ########  ##     ## \n"                   \
"##  ##  ## ##     ## ##   ##   ##     ## \n"                   \
"##  ##  ## ##     ## ##    ##  ##     ## \n"                   \
" ###  ###   #######  ##     ## ########  \n"                   \
"######## ##       #### ######## ######## \n"                   \
"##       ##        ##     ##    ##       \n"                   \
"##       ##        ##     ##    ##       \n"                   \
"######   ##        ##     ##    ######   \n"                   \
"##       ##        ##     ##    ##       \n"                   \
"##       ##        ##     ##    ##       \n"                   \
"######## ######## ####    ##    ######## "

std::shared_ptr<User> user = nullptr;
std::string prompt;

#include "HttpRequest.h"
int main() {
    std::cout << BANNER<< std::endl;
    std::cout << httpGet("localhost", "8080", "/", 11) << std::endl;
    std::cout << "输入help获取帮助" << std::endl << std::endl;
    InitialProcess::init_users();
    InitialProcess::init_wordbank();

    std::unique_ptr<Receiver> receiver = std::make_unique<Receiver>();
    std::map<std::string, std::unique_ptr<Transaction>> commands;
    commands.insert(std::pair<std::string, std::unique_ptr<Transaction>>("signup", new AddUserTransaction()));
    commands.insert(std::pair<std::string, std::unique_ptr<Transaction>>("login", new LoginTransaction()));
    commands.insert(std::pair<std::string, std::unique_ptr<Transaction>>("myinfo", new GetInfoTransaction()));
    commands.insert(std::pair<std::string, std::unique_ptr<Transaction>>("chgr", new ChangeRoleTransaction()));
    commands.insert(std::pair<std::string, std::unique_ptr<Transaction>>("lsu", new ListAllTransaction()));
    commands.insert(
            std::pair<std::string, std::unique_ptr<Transaction>>("rkps", new RankPlayerByExpTransaction()));
    commands.insert(std::pair<std::string, std::unique_ptr<Transaction>>("rkqs", new RankQuestionerByExpTransaction()));
    commands.insert(std::pair<std::string, std::unique_ptr<Transaction>>("game", new GameTransaction()));
    commands.insert(std::pair<std::string, std::unique_ptr<Transaction>>("addw", new AddWordTransaction()));

    prompt = "Word Elite>";
    while (true) {
        std::cout << prompt;
        std::string s;
        std::cin >> s;

        if (s == "logout") {
            user = nullptr;
            std::cout << "注销成功" << std::endl;
            prompt = "Word Elite>";
            continue;
        }
        if (s == "help") {
            HELP_INFO
            continue;
        }
        if (s == "clear") {
            system("clear");
            continue;
        }
        if (s == "exit") {
            return 0;
        }

        auto result = commands.find(s);
        if (result == commands.end()) {
            std::cout << "无效指令..." << std::endl;
            continue;
        }
        receiver->StoreAndExecute(result->second.get());
    }
}