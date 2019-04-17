//
// Created by wey on 19-3-21.
//

#ifndef GAME_INITIALPROCESS_H
#define GAME_INITIALPROCESS_H

#include <iostream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "HttpRequest.h"

using boost::property_tree::ptree;
using boost::property_tree::read_json;

class InitialProcess {
public:
    static void init_users() {
        ptree pt;
        std::stringstream out(httpRequest("GET", "localhost", "8080", "/users", ""));
        read_json(out, pt);
        if (pt.count("users")) {
            ptree pchild = pt.get_child("users");
            for (auto pos = pchild.begin(); pos != pchild.end(); ++pos) {
                GUserDatabase.addUser(pos->second.get<int>("id"),
                                      std::make_shared<User>(pos->second.get<int>("id"),
                                                             pos->second.get<std::string>("username"),
                                                             pos->second.get<std::string>("password")));
                GPlayerDatabase.addPlayer(pos->second.get<int>("id"),
                                          std::make_shared<Player>(pos->second.get<int>("id"),
                                                                   pos->second.get<int>("exp"),
                                                                   pos->second.get<int>("totalPassedStage")));
                GQuestionerDatabase.addQuestioner(pos->second.get<int>("id"),
                                                  std::make_shared<Questioner>(pos->second.get<int>("id"),
                                                                               pos->second.get<int>(
                                                                                       "numberOfQuestions")));
                IN_UID++;
            }
        }
    }

    static void init_wordbank() {
        ptree pt;
        std::stringstream out(httpRequest("GET", "localhost", "8080", "/words", ""));
        read_json(out, pt);
        if (pt.count("words")) {
            ptree pchild = pt.get_child("words");
            for (auto pos = pchild.begin(); pos != pchild.end(); ++pos) {
                GWordDatabase.AddWord(pos->second.get<std::string>("word"));
            }
        }
    }
};


#endif //GAME_INITIALPROCESS_H
