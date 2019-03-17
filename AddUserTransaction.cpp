#include <utility>

#include <utility>

//
// Created by wey on 19-3-17.
//

#include "AddUserTransaction.h"
#include "User.h"
#include "UserDatabase.h"

extern UserDatabase GUserDatabase;

AddUserTransaction::~AddUserTransaction() = default;

AddUserTransaction::AddUserTransaction(int UID, std::string name, std::string pass) : UID(UID), name(std::move(name)),
                                                                                      pass(std::move(pass)) {}

void AddUserTransaction::Execute() {
    User *e = new User(UID, name, pass);
    GUserDatabase.addUser(UID, e);
}
