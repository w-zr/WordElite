//
// Created by wey on 19-3-17.
//

#ifndef GAME_USERDATABASE_H
#define GAME_USERDATABASE_H

#include <curl/curl.h>
#include "User.h"


class User;

class UserDatabase {
public:
    virtual ~UserDatabase() = default;

    std::shared_ptr<User> FindByUID(int UID);

    std::shared_ptr<User> FindByUsername(const std::string &username);

    std::map<int, std::shared_ptr<User>> GetUsers() { return Users; };

    void addUser(int UID, std::shared_ptr<User>, bool send);

    void clear() { Users.clear(); }

private:
    std::map<int, std::shared_ptr<User>> Users;
};

UserDatabase GUserDatabase;

std::shared_ptr<User> UserDatabase::FindByUID(int UID){
    if (Users.find(UID) != Users.end())
        return Users.find(UID)->second;
    return nullptr;
}

void UserDatabase::addUser(int UID, std::shared_ptr<User> e, bool send) {
    CURL *curl;
    CURLcode res;

    if (send) {
        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "localhost:8080/users");
            std::string s = "username=" + e->GetName() + "&password=" + e->GetPass();
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, s.c_str());

            res = curl_easy_perform(curl);
            if (res != CURLE_OK)
                std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            Users[UID] = std::move(e);
        }
        curl_global_cleanup();
    } else
        Users[UID] = std::move(e);
}

std::shared_ptr<User> UserDatabase::FindByUsername(const std::string &username) {
    for (auto &it : GUserDatabase.GetUsers())
        if (it.second->GetName() == username)
            return it.second;
    return nullptr;
}


#endif //GAME_USERDATABASE_H
