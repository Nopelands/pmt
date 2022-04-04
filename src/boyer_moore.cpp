#include "main.h"

int badChar[AB_SIZE];
vector<int> goodChar;

void buildBoyer(const string &pat) {
    const unsigned patSize = pat.size();

    goodChar.assign(patSize + 1, 0);
    memset(badChar, -1, AB_SIZE * sizeof(badChar[0]));

    for (unsigned i = 0; i < patSize; ++i)
        badChar[(uint8_t)pat[i]] = i;

    for (unsigned i = 0; i <= patSize; ++i) {

        int j, k = patSize - i;
        for (j = patSize - 1; j >= 0; --j)
            if ((j >= k && !pat.compare(i, k, pat,       j - k, k))
            ||  (j <  k && !pat.compare(0, j, pat, patSize - j, j)))
                break;

        goodChar[(i + patSize) % (patSize + 1)] = patSize - j;
    }
}

unsigned BoyerMoore(const string &txt, const string &pat) {

    unsigned occ = 0;
    const int patSize = pat.size();
    const int txtSize = txt.size() - patSize;

    for (int i = 0; i <= txtSize;) {
        int j = patSize - 1;

        while (j >= 0 && pat[j] == txt[i + j])
            j--;

        if (j < 0) [[unlikely]]
            occ++, i += goodChar[patSize];
        else
            i += max(goodChar[j], j - badChar[(uint8_t)txt[i + j]]);
    }

    return occ;
}
