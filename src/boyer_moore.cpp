#include "main.h"

int badchar[AB_SIZE];
vector<int> goodchar;

void buildBoyer(const string &pat) {
    const unsigned patSize = pat.size();

    goodchar.assign(patSize + 1, 0);
    memset(badchar, -1, AB_SIZE * sizeof(badchar[0]));

    for (unsigned i = 0; i < patSize; ++i)
        badchar[(uint8_t)pat[i]] = i;

    for (unsigned i = 0; i <= patSize; ++i) {

        int j, k = patSize - i;
        for (j = patSize - 1; j >= 0; --j)
            if ((j >= k && !memcmp(pat.data() + i, pat.data() + j - k      , k))
            ||  (j <  k && !memcmp(pat.data()    , pat.data() + patSize - j, j)))
                break;

        goodchar[(i + patSize) % (patSize + 1)] = patSize - j;
    }
}

unsigned BoyerMoore(const string &txt, const string &pat) {

    unsigned occ = 0;
    const unsigned patSize = pat.size();
    const unsigned txtSize = txt.size() - patSize;

    for (unsigned i = 0; i <= txtSize;) {
        int j = patSize - 1;

        while (j >= 0 && pat[j] == txt[i + j])
            j--;

        if (j < 0) [[unlikely]]
            occ++, i += goodchar[patSize];
        else
            i += max(goodchar[j], j - badchar[(uint8_t)txt[i + j]]);
    }

    return occ;
}
