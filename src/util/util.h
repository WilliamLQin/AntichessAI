//
// Created by William Qin on 2022-10-11.
//

#ifndef ANTICHESSAI_UTIL_H
#define ANTICHESSAI_UTIL_H

namespace util {
    int BitsSetTable256[256];

    void initialize();

    int countSetBits(unsigned long long n);
}

#endif //ANTICHESSAI_UTIL_H
