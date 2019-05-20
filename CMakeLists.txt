cmake_minimum_required(VERSION 3.13)
project(Game)

set(CMAKE_CXX_STANDARD 14)

include_directories(./rapidjson)

add_executable(Game main.cpp include/rio.cpp)
