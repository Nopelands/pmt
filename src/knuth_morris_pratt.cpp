#include "main.h"

vector<int16_t> nxt;

void buildKMP(const string &pat) {
    const unsigned patSize = pat.size();
    nxt.assign(patSize + 1, -1);

    for (unsigned i = 1; i <= patSize; ++i)
        for (unsigned j = 0; j < i; ++j)
            if (!pat.compare(0, j, pat, i - j, j))
                nxt[i] = j;
}

template<bool count>
unsigned KnuthMorrisPratt(const string &txt, const string &pat) {

    unsigned occ = 0;
    const int patSize = pat.size();
    const int txtSize = txt.size() - patSize;

    for (int i = 0, j = 0; i <= txtSize; ) {

        while (j < patSize && pat[j] == txt[i + j])
            j++;

        if (j == patSize) [[unlikely]] {
            if constexpr (!count)
                return 1;

            occ++;
        }

        i += j - nxt[j];
        j = max((int16_t)0, nxt[j]);
    }
  
    return occ;
}

unsigned KnuthMorrisPratt(bool count, const string &txt, const string &pat) {
    return count ? KnuthMorrisPratt< true>(txt, pat)
                 : KnuthMorrisPratt<false>(txt, pat);
}
