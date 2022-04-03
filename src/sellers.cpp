#include "main.h"

vector<unsigned> SS;

unsigned Sellers(const string &txt, const string &pat, const unsigned r) {

    unsigned occ = 0;
    const unsigned txtSize = txt.size();
    const unsigned patSize = pat.size();
    SS.resize(patSize + 1);
  
    for (unsigned i = 0; i <= patSize; ++i)
        SS[i] = i;

    for (unsigned i = 0; i < txtSize; ++i) {

        for (unsigned j = 1, previous = 0, temp; j <= patSize; previous = temp, ++j)
            SS[j] = min(previous + (txt[i] != pat[j - 1]), min(SS[j - 1], temp = SS[j]) + 1);

        if (SS[patSize] <= r) [[unlikely]]
            occ++;
    }

    return occ;
}
