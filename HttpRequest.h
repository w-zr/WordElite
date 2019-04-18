//
// Created by wei on 19-4-15.
//

#ifndef GAME_HTTPREQUEST_H
#define GAME_HTTPREQUEST_H

#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <netdb.h>

const char* httpRequest(const std::string& method, const std::string& host, const std::string& port, const std::string& target,
         const std::string& body) {
    struct addrinfo hints{}, *res;
    int sockfd;
    char buf[4096];
    size_t byte_count;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo(host.c_str(), port.c_str(), &hints, &res);
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    connect(sockfd, res->ai_addr, res->ai_addrlen);
    std::string request;
    if (!body.empty()) {
        request = method + " " + target + " HTTP/1.1\r\nContent-Type: application/x-www-form-urlencoded\r\nHost: " +
                  host + ":" + port + "\r\nContent-Length: " + std::to_string(body.length()) + "\r\n\r\n" + body;
    } else {
        request = method + " " + target + " HTTP/1.1\r\nHost: " + host + ":" + port + "\r\n\r\n";
    }

    send(sockfd, request.c_str(), request.length(), 0);
    byte_count = recv(sockfd, buf, sizeof(buf) - 1, 0);
    buf[byte_count] = 0;

    close(sockfd);
    return strstr(buf, "\r\n\r\n");
}

#endif //GAME_HTTPREQUEST_H
