cmake_minimum_required(VERSION 3.13)
project(Game)

set(CMAKE_CXX_STANDARD 14)
link_libraries(curl)

add_link_options(-pthread)
include_directories(/usr/local/boost/include)
link_directories(/usr/local/boost/lib)

add_executable(Game main.cpp Transaction.h UserDatabase.h User.h AddUserTransaction.h Role.h Player.h Questioner.h ListAllTransaction.h Receiver.h PlayerDatabase.h ChangeRoleTransaction.h QuestionerDatabase.h LoginTransaction.h GetInfoTransaction.h RankPlayerByExpTransaction.h RankQuestionerByExpTransaction.h InitialProcess.h GameTransaction.h WordDatabase.h AddWordTransaction.h HttpRequest.h)