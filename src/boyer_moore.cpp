#include "main.h"

int16_t badchar[256];

int BoyerMoore(const string &txt, const string &pat) {

  const unsigned txtSize = txt.length();
  const unsigned patSize = pat.length();

  memset(badchar, -1, 256 * sizeof(badchar[0]));

  for (unsigned i = 0; i < patSize; ++i)
    badchar[(uint8_t)pat[i]] = i;

  for (unsigned s = 0; s <= txtSize - patSize;) {
    int j = patSize - 1;

    while (j >= 0 && pat[j] == txt[s + j])
      j--;

    if (j < 0)
      return s;

    s += max(1, j - badchar[(uint8_t)txt[s + j]]);
  }

  return -1;
}
