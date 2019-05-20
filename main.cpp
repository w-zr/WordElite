#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
#include "include/WordElite.h"
#include "include/rio.hpp"
#include "include/wrap_socket.hpp"
#include "include/ExitTransaction.hpp"
#include "include/ChallengeTransacion.hpp"
#include <poll.h>
#include <signal.h>

std::shared_ptr<User> user = nullptr;


using std::pair;
using std::string;
using std::unique_ptr;

constexpr int MAX_SOCKET = 128;
struct pollfd poll_fd[MAX_SOCKET];

int main() {
    signal(SIGPIPE, SIG_IGN);

    std::cout << httpRequest("GET", "localhost", "8080", "/", "") << std::endl;
    InitialProcess::init_users();
    InitialProcess::init_wordbank();

    Receiver receiver;
    Commands::commands.insert(pair<string, Transaction *>("signup", new AddUserTransaction()));
    Commands::commands.insert(pair<string, Transaction *>("login", new LoginTransaction()));
    Commands::commands.insert(pair<string, Transaction *>("addw", new AddWordTransaction()));
    Commands::commands.insert(pair<string, Transaction *>("exit", new ExitTransaction()));
    Commands::commands.insert(pair<string, Transaction *>("chgr", new ChangeRoleTransaction()));
    Commands::commands.insert(pair<string, Transaction *>("game", new GameTransaction()));
    Commands::commands.insert(pair<string, Transaction *>("lsu", new ListAllTransaction()));
    Commands::commands.insert(pair<string, Transaction *>("rkps", new RankPlayerByExpTransaction()));
    Commands::commands.insert(pair<string, Transaction *>("rkqs", new RankQuestionerByExpTransaction()));
    Commands::commands.insert(pair<string, Transaction *>("challenge", new ChallengeTransaction()));

    int connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr{};
    char client_hostname[MAXLINE], client_port[MAXLINE];

    poll_fd[0].fd = open_listenfd("8888");
    poll_fd[0].events = POLLIN;
    for (auto i = 1; i < MAX_SOCKET; i++) {
        poll_fd[i].fd = -1;
    }

    int sockNum = 0;
    while (true) {
        std::cout << "waiting for I/O activities...\n";
        int ret = poll(poll_fd, sockNum + 1, 30000);
        if (ret < 0) {
            std::cerr << "poll error\n";
            break;
        }
        if (poll_fd[0].revents & POLLIN) {
            clientlen = sizeof(struct sockaddr_storage);
            if ((connfd = accept(poll_fd[0].fd, (sockaddr *) &clientaddr, &clientlen)) == -1)
                std::cerr << "accept error\n";
            else {
                getnameinfo((sockaddr *) &clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
                std::cout << "Connected to (" << client_hostname << ", " << client_port << ")" << std::endl;
            }
            for (auto i = 1; i < MAX_SOCKET; i++) {
                if (poll_fd[i].fd < 0) {
                    poll_fd[i].fd = connfd;
                    poll_fd[i].events = POLLIN;
                    if (i > sockNum)
                        sockNum = i;
                    std::cout << "poll [" << i << "] fd: " << poll_fd[i].fd << std::endl;
                    break;
                }
            }
        }
        for (auto i = 1; i <= sockNum; i++) {
            std::cout << "checking poll [" << i << "]\n";
            if (poll_fd[i].revents & POLLIN) {
                std::cout << "poll [" << i << "] received message\n";
                char buf[MAXLINE];
                rio::initb(poll_fd[i].fd);
                rio::readlineb(buf, MAXLINE);
                string str(buf);
                auto command = str.substr(0, str.find(' '));
                auto parameters = str.substr(str.find(' ') + 1);
                receiver.StoreAndExecute(poll_fd[i].fd, command, parameters);
                std::cout << "command: " << command << std::endl;
                if (command == "exit" || command == "logout") {
                    close(poll_fd[i].fd);
                    poll_fd[i].fd = -1;
                }
            }

        }
    }
}
#pragma clang diagnostic pop