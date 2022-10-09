cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 14)
project(AntichessAI)

add_subdirectory(src)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} Board)
