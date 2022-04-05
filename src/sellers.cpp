#include "main.h"

vector<unsigned> SS;

template<bool count>
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

        if (SS[patSize] <= r) [[unlikely]] {
            if constexpr (!count)
                return 1;

            occ++;
        }
    }
    return occ;
}

unsigned Sellers(bool count, const string &txt, const string &pat, const unsigned r) {
    return count ? Sellers< true>(txt, pat, r)
                 : Sellers<false>(txt, pat, r);
}
