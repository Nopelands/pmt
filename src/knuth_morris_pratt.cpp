#include "main.h"

vector<int16_t> nxt;

void buildKMP(const string &pat) {
    const unsigned patSize = pat.size();
    nxt.assign(patSize + 1, -1);

    for (unsigned i = 1; i <= patSize; ++i)
        for (unsigned j = 0; j < i; ++j)
            if (!memcmp(pat.data(), pat.data() + i - j, j))
                nxt[i] = j;
}

unsigned KnuthMorrisPratt(const string &txt, const string &pat) {

    unsigned occ = 0;
    const unsigned txtSize = txt.size();
    const unsigned patSize = pat.size();

    for (unsigned i = 0, j = 0; i <= txtSize - patSize; ) {

        while (j < patSize && pat[j] == txt[i + j])
            j++;

        if (j == patSize) [[unlikely]]
            occ++;

        i += j - nxt[j];
        j = max((int16_t)0, nxt[j]);
    }
  
    return occ;
}
