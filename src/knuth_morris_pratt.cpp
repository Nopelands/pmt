#include "main.h"

uint8_t dfa[256][256];

int KnuthMorrisPratt(const string &txt, const string &pat) {

  unsigned i, j;
  const unsigned txtSize = txt.length();
  const unsigned patSize = pat.length();

  dfa[0][(uint8_t)pat[0]] = 1;

  for (unsigned i = 0, j = 1; j < patSize; j++) {
    memcpy(dfa[j], dfa[i], 256 * sizeof(dfa[0][0]));

    dfa[j][(uint8_t)pat[j]] = j + 1;
    i = dfa[i][(uint8_t)pat[j]];
  }

  for (i = 0, j = 0; i < txtSize && j < patSize; i++)
    j = dfa[j][(uint8_t)txt[i]];

  return j == patSize ? i - j : -1;
}
