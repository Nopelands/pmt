#include "main.h"

uint64_t WM[AB_SIZE];

void buildWuMamber(const string& pat) {
    const unsigned patSize = pat.size();

    memset(WM, -1, AB_SIZE * sizeof(WM[0]));
    
    for (uint64_t i = 0, j = 1; i < patSize; ++i, j <<= 1)
        WM[(uint8_t)pat[i]] &= ~j;

}

vector<Occurance> WuMamber(const string& txt, const string& pat, const unsigned r) {

    const unsigned txtSize = txt.size();
    const unsigned patSize = pat.size();

    const uint64_t check = (1 << (patSize - 1));

    vector<Occurance> occ;
    vector<uint64_t> s(r + 1);
    s[0] = -1ULL;

    for (unsigned i = 1; i <= r; ++i)
        s[i] = s[i - 1] << 1;

    for (unsigned i = 0; i < txtSize; ++i) {
        auto previous = s[0];
        s[0] = (previous << 1) | WM[(uint8_t)txt[i]];

        for (unsigned j = 1, temp; j <= r; ++j, previous = temp)
            s[j] = previous & (previous << 1) & (s[j - 1] << 1) & (((temp = s[j]) << 1) | WM[(uint8_t)txt[i]]);

        if (!(s[r] & check))
            occ.push_back({i, 0});
    }

    return occ;
}
