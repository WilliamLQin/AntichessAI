//
// Created by William Qin on 2022-12-17.
//

#include "timer.h"
#ifdef DEBUG
#include <iostream>
#endif

void Timer::startTurn() {
    startTime = std::chrono::steady_clock::now();
    if (turnCount == 0)
    {
        timePerTurn = std::chrono::milliseconds(3000);
    }
    else if (turnCount == 45)
    {
        timePerTurn = std::chrono::milliseconds(2000);
    }
    else if (turnCount == 60)
    {
        timePerTurn = std::chrono::milliseconds(1000);
    }
    else if (turnCount == 70)
    {
        timePerTurn = std::chrono::milliseconds(500);
    }
    turnCount += 1;
}

void Timer::endTurn() {
    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    usedTime += diff + LEEWAY_TIME;

#ifdef DEBUG
    std::cout << "AI turn took " << diff.count() << "ms" << std::endl;
#endif
}

void Timer::checkOutOfTime(int depth) {
    std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
    std::chrono::milliseconds diff =
            std::chrono::duration_cast<std::chrono::milliseconds>(time - startTime);

    if (diff + LEEWAY_TIME > timePerTurn) {
        throw OutOfTime(depth);
    }
}

double Timer::getUsedTime() {
    return usedTime.count() / 1000.0;
}