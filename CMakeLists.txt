cmake_minimum_required(VERSION 3.13)
project(Game)

set(CMAKE_CXX_STANDARD 14)
link_libraries(curl)
add_executable(Game main.cpp Transaction.h UserDatabase.h User.h AddUserTransaction.h Role.h Player.h Questioner.h ListAllTransaction.h Receiver.h PlayerDatabase.h ChangeRoleTransactino.h QuestionerDatabase.h LoginTransaction.h GetInfoTransaction.h RankPlayerByExpTransaction.h RankQuestionerByExpTransaction.h InitialProcess.h)