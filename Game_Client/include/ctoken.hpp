//
// Created by wei on 19-4-24.
//

#ifndef GAME_CLIENT_CTOKEN_HPP
#define GAME_CLIENT_CTOKEN_HPP

#include <netdb.h>
#include <cstring>
#include <unistd.h>

class ctoken {
public:
    static ctoken &getInstance() {
        static ctoken instance;
        return instance;
    }

private:
    ctoken() = default;

public:
    ctoken(ctoken const &) = delete;

    void operator=(ctoken const &) = delete;

    int UID = -1;
    int fd = -1;
    std::string username;
    char role = 'n';
    const std::string hostname = "localhost";
    const std::string port = "8888";
    double nonce = 0;

    void openfd() {
        int clientfd = 0;
        struct addrinfo hints{}, *listp, *p;
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_NUMERICSERV;
        hints.ai_flags |= AI_ADDRCONFIG; // NOLINT(hicpp-signed-bitwise)
        getaddrinfo(hostname.c_str(), port.c_str(), &hints, &listp);
        for (p = listp; p; p = p->ai_next) {
            if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
                continue;
            if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1)
                break;
            close(clientfd);
        }
        freeaddrinfo(listp);
        if (p != nullptr)fd = clientfd;
    }

    void refresh() {
        close(fd);
        openfd();
    }

    void clean() {
        UID = -1;
        close(fd);
        fd = -1;
        username.clear();
        nonce = 0;
    }
};

#endif //GAME_CLIENT_CTOKEN_HPP
