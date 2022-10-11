cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
project(AntichessAI)

add_executable(${PROJECT_NAME} src/main.cpp src/cpp-chess/chess.cpp src/search/search.cpp)
