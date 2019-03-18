cmake_minimum_required(VERSION 3.13)
project(Game)

set(CMAKE_CXX_STANDARD 14)

add_executable(Game main.cpp Transaction.h UserDatabase.cpp UserDatabase.h User.h AddUserTransaction.h Role.h Player.cpp Player.h Queser.cpp Queser.h ListAllTransaction.h Receiver.h LoginTransaction.h)