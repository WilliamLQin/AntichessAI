//
// Created by William Qin on 2022-12-17.
//

#ifndef ANTICHESSAI_TIMER_H
#define ANTICHESSAI_TIMER_H

#include <chrono>

class Timer {
    constexpr static std::chrono::milliseconds ALLOTTED_TIME = std::chrono::milliseconds(3*60*1000);
    constexpr static std::chrono::milliseconds LEEWAY_TIME = std::chrono::milliseconds(100);
    constexpr static std::chrono::milliseconds TIME_PER_TURN = std::chrono::milliseconds (1000);
    std::chrono::milliseconds usedTime;
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point checkpointTime;
public:
    explicit Timer() : usedTime(0) {};
    void startTurn();
    void endTurn();
    bool checkpoint();
    double getUsedTime();
};


#endif //ANTICHESSAI_TIMER_H
