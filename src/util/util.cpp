//
// Created by William Qin on 2022-10-11.
//

#include "util.h"

void util::initialize() {
    // BitsSetTable256
    BitsSetTable256[0] = 0;
    for (int i = 0; i < 256; i++) {
        BitsSetTable256[i] = (i & 1) + BitsSetTable256[i / 2];
    }
}

int util::countSetBits(unsigned long long n) {
    int ret = 0;
    for (int i = 0; i < 8; i++) {
        ret += BitsSetTable256[(n >> (i*8)) & 0xff];
    }
    return ret;
}
