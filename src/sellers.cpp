#include "main.h"

vector<unsigned> SS;

vector<Occurance> Sellers(const string &txt, const string &pat, const unsigned r) {

    const unsigned txtSize = txt.size();
    const unsigned patSize = pat.size();
    vector<Occurance> occ;
    SS.resize(patSize + 1);
  
    for (unsigned i = 0; i <= patSize; ++i)
        SS[i] = i;

    for (unsigned i = 0; i < txtSize; ++i) {

        for (unsigned j = 1, previous = 0, temp; j <= patSize; previous = temp, ++j)
            SS[j] = min(previous + (txt[i] != pat[j - 1]), min(SS[j - 1], temp = SS[j]) + 1);

        if (SS[patSize] <= r)
            occ.push_back({i, 0});
    }

    return occ;
}
