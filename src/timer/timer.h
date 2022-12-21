//
// Created by William Qin on 2022-12-17.
//

#ifndef ANTICHESSAI_TIMER_H
#define ANTICHESSAI_TIMER_H

#include <chrono>
#include <exception>

class Timer {
    constexpr static std::chrono::milliseconds ALLOTTED_TIME = std::chrono::milliseconds(3*60*1000);
    constexpr static std::chrono::milliseconds LEEWAY_TIME = std::chrono::milliseconds(100);

    std::chrono::milliseconds timePerTurn = std::chrono::milliseconds (20000);
    int turnCount = 0;
    std::chrono::milliseconds usedTime;
    std::chrono::steady_clock::time_point startTime;
public:
    class OutOfTime : public std::exception {
    public:
        int depth;
        explicit OutOfTime(int depth) : depth(depth) {}
    };

    explicit Timer() : usedTime(0) {};
    void startTurn();
    void endTurn();
    void checkOutOfTime(int depth);
    double getUsedTime();
};


#endif //ANTICHESSAI_TIMER_H
