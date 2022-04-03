#include "main.h"

uint64_t SO[AB_SIZE];

void buildShiftOr(const string &pat) {
  
    const unsigned patSize = pat.size();
    
    memset(SO, -1, AB_SIZE * sizeof(SO[0]));

    for (uint64_t i = 0, j = 1; i < patSize; ++i, j <<= 1)
        SO[(uint8_t)pat[i]] &= ~j;
}

unsigned ShiftOr(const string &txt, const string &pat) {

    unsigned occ = 0;
    const unsigned txtSize = txt.size();
    const unsigned patSize = pat.size();
    const uint64_t lim = 1ULL << (patSize - 1);

    uint64_t state = -1ULL;
    for (unsigned i = 0; i < txtSize; ++i) {
        state = (state << 1) | SO[(uint8_t)txt[i]];

      if (!(state & lim)) [[unlikely]]
          occ++;
    }

    return occ;
}
