//
// Created by William Qin on 2022-12-17.
//

#include "timer.h"
#ifdef DEBUG
#include <iostream>
#endif

void Timer::startTurn() {
    startTime = std::chrono::steady_clock::now();
    switch(turnCount)
    {
        case 0:
            timePerTurn = std::chrono::milliseconds (20000);
            break;
        case 1:
            timePerTurn = std::chrono::milliseconds (10000);
            break;
        case 2:
        case 3:
            timePerTurn = std::chrono::milliseconds (6000);
            break;
        case 4:
        case 5:
            timePerTurn = std::chrono::milliseconds (5000);
            break;
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
            timePerTurn = std::chrono::milliseconds (4000);
            break;
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
            timePerTurn = std::chrono::milliseconds (3000);
            break;
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
        case 40:
            timePerTurn = std::chrono::milliseconds (2000);
            break;
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
        case 50:
            timePerTurn = std::chrono::milliseconds (1000);
            break;
        default:
            timePerTurn = std::chrono::milliseconds (500);
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