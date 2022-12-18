//
// Created by William Qin on 2022-12-17.
//

#include "timer.h"
#include <iostream>

void Timer::startTurn() {
    startTime = std::chrono::steady_clock::now();
}

void Timer::endTurn() {
    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    usedTime += diff + LEEWAY_TIME;

#ifdef DEBUG
    std::cout << "AI turn took " << diff.count() << "ms" << std::endl;
#endif
}

void Timer::checkOutOfTime() {
    std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
    std::chrono::milliseconds diff =
            std::chrono::duration_cast<std::chrono::milliseconds>(time - startTime);

    if (diff + LEEWAY_TIME > TIME_PER_TURN) {
        throw OutOfTime();
    }
}

double Timer::getUsedTime() {
    return usedTime.count() / 1000.0;
}