cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 20)
project(AntichessAI)

add_library(Board src/Board/board.cpp)
add_library(cpp-chess src/cpp-chess/chess.cpp)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} Board cpp-chess)
