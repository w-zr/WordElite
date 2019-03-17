//
// Created by wey on 19-3-17.
//

#ifndef GAME_USERDATABASE_H
#define GAME_USERDATABASE_H

#include <map>
class User;

class UserDatabase {
public:
    virtual ~UserDatabase();

    User *GetUser(int UID);

    void PrintAllUser();

    std::map<int, User *> GetUsers() { return Users; };

    void addUser(int UID, User *);

    void clear() { Users.clear(); }

private:
    std::map<int, User *> Users;
};


#endif //GAME_USERDATABASE_H
