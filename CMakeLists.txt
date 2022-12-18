cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
option(CLI_MODE "use cli mode")
option(LICHESS_MODE "pass ai color as first line of input (for lichess-bot)")
option(DEBUG "debug")
project(AntichessAI)

add_executable(${PROJECT_NAME} 
        src/main.cpp 
        src/cpp-chess/chess.cpp src/cpp-chess/chess.h
        src/search/search.cpp src/search/search.h
        src/evaluate/evaluate.cpp src/evaluate/evaluate.h
        src/timer/timer.cpp src/timer/timer.h
        src/memoization/transposition_table.cpp src/memoization/transposition_table.h)
if(CLI_MODE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE CLI_MODE)
endif()
if(LICHESS_MODE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LICHESS_MODE)
endif()
if(DEBUG)
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
endif()
