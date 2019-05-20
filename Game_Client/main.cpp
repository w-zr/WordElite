#include <iostream>
#include <memory>
#include <map>
#include <signal.h>
#include <poll.h>

#include "include/ctoken.hpp"
#include "include/rio.hpp"
#include "include/receiver.hpp"
#include "include/signupTransaction.hpp"
#include "include/loginTransaction.hpp"
#include "include/exitTransacition.hpp"
#include "include/addWordTransaction.hpp"
#include "include/logoutTransaction.hpp"
#include "include/chgrTransaction.hpp"
#include "include/gameTransaction.hpp"
#include "include/getInfoTransaction.hpp"
#include "include/challengeTransaction.hpp"
#include "include/rankPlayerTransaction.hpp"
#include "include/rankQuestionerTransaction.hpp"

#define HELP_INFO \
do{ \
std::cout <<"\nHELP LIST\nhelp\t\t--帮助信息\nsignup\t\t--注册\nlogin\t\t--登录\nlogout\t\t--注销\nmyinfo\t\t--账户信息\nchgr\t\t--更改用户身份\nlsu\t\t\t--列出所有用户\nrkps\t\t--闯关者排行\nrkqs\t\t--出题者排行\ngame\t\t--开始新游戏\naddw\t\t--添加新词\nclear\t\t--清屏\nexit/quit\t--退出\n\n"; \
} while(0)

#define BANNER   \
"##      ##  #######  ########  ########  \n"    \
"##  ##  ## ##     ## ##     ## ##     ## \n"    \
"##  ##  ## ##     ## ##     ## ##     ## \n"    \
"##  ##  ## ##     ## ########  ##     ## \n"    \
"##  ##  ## ##     ## ##   ##   ##     ## \n"    \
"##  ##  ## ##     ## ##    ##  ##     ## \n"    \
" ###  ###   #######  ##     ## ########  \n"    \
"######## ##       #### ######## ######## \n"    \
"##       ##        ##     ##    ##       \n"    \
"##       ##        ##     ##    ##       \n"    \
"######   ##        ##     ##    ######   \n"    \
"##       ##        ##     ##    ##       \n"    \
"##       ##        ##     ##    ##       \n"    \
"######## ######## ####    ##    ######## \n\n"

using std::pair;
using std::string;
using std::unique_ptr;

std::string prompt;

void SIGINTHANDLER(int s) {
    ctoken& CTOKEN = ctoken::getInstance();
    auto data = "exit " + std::to_string(CTOKEN.UID) + '\n';
    rio_writen(CTOKEN.fd, data.data(), data.size());
    std::cout << "caught signal " << s << std::endl;
    exit(1);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
int main() {
    struct sigaction sigIntHandler{};

    sigIntHandler.sa_handler = SIGINTHANDLER;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, nullptr);

    std::cout << BANNER << "输入help获取帮助\n\n";
    ctoken &CTOKEN = ctoken::getInstance();
    CTOKEN.openfd();
    std::cout << "server_fd: " << CTOKEN.fd << std::endl;

    struct pollfd poll_socket[2];
    poll_socket[0].fd = STDIN_FILENO;
    poll_socket[0].events = POLLIN;
    poll_socket[1].fd = CTOKEN.fd;
    poll_socket[1].events = POLLIN;

    auto receiver = std::make_unique<class receiver>();
    std::map<string, unique_ptr<transaction>> commands;
    commands.insert(pair<string, transaction *>("signup", new signupTransaction()));
    commands.insert(pair<string, transaction *>("login", new loginTransaction()));
    commands.insert(pair<string, transaction *>("logout", new logoutTransaction()));
    commands.insert(pair<string, transaction *>("exit", new exitTransaction()));
    commands.insert(pair<string, transaction *>("addw", new addWordTransaction()));
    commands.insert(pair<string, transaction *>("chgr", new chgrTransaction()));
    commands.insert(pair<string, transaction *>("game", new gameTransaction()));
    commands.insert(pair<string, transaction *>("lsu", new getInfoTransaction()));
    commands.insert(pair<string, transaction *>("challenge", new challengeTransaction()));
    commands.insert(pair<string, transaction *>("rkps", new rankPlayerTransaction()));
    commands.insert(pair<string, transaction *>("rkqs", new rankQuestionerTransaction()));

    string command;
    prompt = "client>> ";
    while (true) {
        std::cout << prompt << std::flush;
        if (poll(poll_socket, 2, -1) == -1) {
            perror("poll");
            exit(-1);
        }
        std::cout << "\ncin event: " << poll_socket[0].revents << " socket event: " << poll_socket[1].revents
                  << std::endl;
        if (poll_socket[0].revents & POLLIN) {
            std::getline(std::cin, command);
            if (command == "help") {
                HELP_INFO;
                continue;
            } else if (command == "clear") {
                system("clear");
                continue;
            }

            auto result = commands.find(command);
            if (!(result == commands.end())) {
                receiver->StoreAndExecute(result->second.get());
            } else
                std::cout << "无效指令" << std::endl;
        } else if (poll_socket[1].revents & POLLIN) {
            char buf[MAXLINE];
            rio_t r;
            rio_readinitb(&r, CTOKEN.fd);
            rio_readlineb(&r, buf, MAXLINE);
            std::cout << "received: " << buf;
            std::stringstream sstr(buf);
            int rivalID, code;
            std::string rivalName;
            sstr >> code >> rivalID >> rivalName;
            if (code != 100)
                continue;
            Grival.callerID = rivalID;
            Grival.calleeID = CTOKEN.UID;
            std::cout << "You received an invitation from user " << rivalName << " accept or not? (Y/N): ";
            char rep;
            std::cin >> rep;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            auto data = "challenge " + std::to_string(CTOKEN.UID) + " " + std::to_string(rivalID) + " " +
                        std::to_string(CTOKEN.UID) + " ack ";
            if (rep == 'y' || rep == 'Y') {
                data += "200\n";
                rio_writen(CTOKEN.fd, data.data(), data.size());
                std::cout << "client: message sent: " << data;
                std::cout << "Waiting for the caller to decide the difficulty...\n";
                rivalGame rG;
                rG.Execute();
            } else {
                data += "500\n";
                rio_writen(CTOKEN.fd, data.data(), data.size());
                std::cout << "client: message sent: " << data;
                std::cout << "You refused.\n";
            }

        } else if (poll_socket[1].revents & POLLNVAL) {
            std::cout << "socket is closed\n";
            CTOKEN.refresh();
        }

    }
}
#pragma clang diagnostic pop