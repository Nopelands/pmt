#include "main.h"

vector<int16_t> nxt;

void buildKMP(const string &pat) {
    const unsigned patSize = pat.size();
    nxt.assign(patSize + 1, -1);

    for (unsigned i = 1; i <= patSize; ++i)
        for (unsigned j = 0; j < i; ++j) {
            bool check = true;

            for (unsigned k = 0; k < j && check; ++k)
                if (pat[k] != pat[i - j + k])
                    check = false;

            if (check)
                nxt[i] = j;
        }
}

vector<Occurance> KnuthMorrisPratt(const string &txt, const string &pat) {

    vector<Occurance> occ;
    const unsigned txtSize = txt.size();
    const unsigned patSize = pat.size();

    for (unsigned i = 0, j = 0; i <= txtSize - patSize; ) {

        while (j < patSize && pat[j] == txt[i + j])
            j++;

        if (j == patSize)
            occ.push_back({i, 0});

        i += j - nxt[j];
        j = max((int16_t)0, nxt[j]);
    }
  
    return occ;
}
