cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
option(CLI_MODE "use cli mode")
project(AntichessAI)

add_executable(${PROJECT_NAME} 
        src/main.cpp 
        src/cpp-chess/chess.cpp 
        src/search/search.cpp
        src/evaluate/evaluate.cpp
)
if(CLI_MODE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE CLI_MODE)
endif()
