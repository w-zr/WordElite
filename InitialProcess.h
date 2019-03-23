//
// Created by wey on 19-3-21.
//

#ifndef GAME_INITIALPROCESS_H
#define GAME_INITIALPROCESS_H

#include <curl/curl.h>
#include <iostream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

using boost::property_tree::ptree;
using boost::property_tree::read_json;

class InitialProcess {
public:
    void init_users() {
        CURL *curl;
        CURLcode res;

        std::stringstream out;
        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "localhost:8080/users");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
            res = curl_easy_perform(curl);
            if (res != CURLE_OK)
                std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            ptree pt;
            read_json(out, pt);
            if (pt.count("users")) {
                ptree pchild = pt.get_child("users");
                for (auto pos = pchild.begin(); pos != pchild.end(); ++pos) {
                    GUserDatabase.addUser(pos->second.get<int>("id"), std::make_shared<User>(pos->second.get<int>("id"),
                                                                                             pos->second.get<std::string>(
                                                                                                     "username"),
                                                                                             pos->second.get<std::string>(
                                                                                                     "password")),
                                          false);
                    IN_UID++;
                }
            }
            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();
    }

    void init_players() {
        CURL *curl;
        CURLcode res;

        std::stringstream out;
        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "localhost:8080/players");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
            res = curl_easy_perform(curl);
            if (res != CURLE_OK)
                std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            ptree pt;
            read_json(out, pt);
            if (pt.count("players")) {
                ptree pchild = pt.get_child("players");
                for (auto pos = pchild.begin(); pos != pchild.end(); ++pos) {
                    GPlayerDatabase.addPlayer(pos->second.get<int>("id"),
                                              std::make_shared<Player>(pos->second.get<int>("id"),
                                                                       pos->second.get<int>(
                                                                               "exp"),
                                                                       pos->second.get<int>(
                                                                               "level"),
                                                                       pos->second.get<int>("totalPassedStage")));
                    std::cout << pos->second.get<int>("id") << std::endl;
                }
            }
            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();
    }

private:
    static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
        std::string data((const char *) ptr, (size_t) size * nmemb);
        *((std::stringstream *) stream) << data << std::endl;
        return size * nmemb;
    }
};


#endif //GAME_INITIALPROCESS_H
