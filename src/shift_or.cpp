#include "main.h"

uint64_t unsigned SO[256];

int ShiftOr(const string &txt, const string &pat) {

  const unsigned txtSize = txt.length();
  const unsigned patSize = pat.length();
  const uint64_t lim = -1ULL << (patSize - 1);

  memset(SO, -1, 256 * sizeof(SO[0]));

  for (uint64_t i = 0, j = 1; i < patSize; ++i, j <<= 1)
    SO[(uint8_t)pat[i]] &= ~j;

  for (uint64_t state = -1ULL, j = 0; j < txtSize; ++j) {
    state = (state << 1) | SO[(uint8_t)txt[j]];

    if (state < lim)
      return j - patSize + 1;
  }

  return -1;
}
