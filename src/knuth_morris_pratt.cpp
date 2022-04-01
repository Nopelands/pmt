#include "main.h"

int16_t dfa[1024][AB_SIZE];

void buildKMP(const string &pat) {
    const unsigned patSize = pat.size();

    dfa[0][(uint8_t)pat[0]] = 1;

    for (unsigned i = 0, j = 1; j < patSize; j++) {
        memcpy(dfa[j], dfa[i], AB_SIZE * sizeof(dfa[0][0]));

        dfa[j][(uint8_t)pat[j]] = j + 1;
        i = dfa[i][(uint8_t)pat[j]];
    }
}

vector<Occurance> KnuthMorrisPratt(const string &txt, const string &pat) {

    vector<Occurance> occ;
    const unsigned txtSize = txt.size();
    const unsigned patSize = pat.size();

    for (unsigned i = 0, j = 0; i < txtSize; i++) {
        j = dfa[j][(uint8_t)txt[i]];

        if (j >= patSize)
            occ.push_back({i, 0});
            // return i - j;
    }

    return occ;
}
