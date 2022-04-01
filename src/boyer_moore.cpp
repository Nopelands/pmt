#include "main.h"

int16_t badchar[AB_SIZE];

void buildBoyer(const string &pat) {
    const unsigned patSize = pat.size();

    memset(badchar, -1, AB_SIZE * sizeof(badchar[0]));

    for (unsigned i = 0; i < patSize; ++i)
        badchar[(uint8_t)pat[i]] = i;
}

vector<Occurance> BoyerMoore(const string &txt, const string &pat) {

    vector<Occurance> occ;
    const unsigned patSize = pat.size();
    const unsigned txtSize = txt.size() - patSize;

    for (unsigned i = 0; i <= txtSize;) {
        int j = patSize - 1;

        while (j >= 0 && pat[j] == txt[i + j])
            j--;

        if (j < 0)
            occ.push_back({i, 0}), j = 0;

        i += max(1, j - badchar[(uint8_t)txt[i + j]]);
    }

    return occ;
}
