#include "main.h"

int64_t WM64[AB_SIZE];

#if defined(__GNUC__)
int128_t WM128[AB_SIZE];
vector<int128_t> WMv[AB_SIZE];
#else
vector<int64_t> WMv[AB_SIZE];
#endif


template<typename intType>
void buildWuManber(const string& pat, intType *WM) {

    memset(WM, -1, AB_SIZE * sizeof(intType));

    intType j = 1;
    for (uint8_t c : pat)
        WM[c] &= ~j, j <<= 1;
}

template<bool count, typename intType>
unsigned WuManber(const string& txt, const string& pat, const unsigned r, intType *WM) {

    const intType lim = intType(1) << (pat.size() - 1);

    unsigned occ = 0;
    vector<intType> s(r + 1);
    s[0] = -1;

    for (unsigned i = 1; i <= r; ++i)
        s[i] = s[i - 1] << 1;

    for (uint8_t c : txt) {
        intType temp, previous = s[0];
        s[0] = (previous << 1) | WM[c];

        for (unsigned j = 1; j <= r; ++j, previous = temp)
            s[j] = previous & (previous << 1) & (s[j - 1] << 1) & (((temp = s[j]) << 1) | WM[c]);

        if (!(s[r] & lim)) [[unlikely]] {
            if constexpr (!count)
                return 1;

            occ++;
        }
    }

    return occ;
}

void buildWuManberV(const string& pat) {

    const unsigned vecSize = ((pat.size() - 1) / sizeInt) + 1;

    for (unsigned i = 0; i < AB_SIZE; ++i)
        WMv[i].assign(vecSize, -1);

    vector<bigInt> j(vecSize, 0);
    j.back() = 1;

    for (uint8_t c : pat)
        WMv[c] &= ~j, j <<= 1;
}

template<bool count>
unsigned WuManberV(const string& txt, const string& pat, const unsigned r) {

    const unsigned vecSize = ((pat.size() - 1) / sizeInt) + 1;
    const bigInt lim = bigInt(1) << ((pat.size() - 1) % sizeInt);

    unsigned occ = 0;
    vector<vector<bigInt>> s(r + 1);
    s[0].assign(vecSize, -1);

    for (unsigned i = 1; i <= r; ++i)
        s[i] = s[i - 1] << 1;

    for (uint8_t c : txt) {
        vector<bigInt> temp, previous = s[0];
        s[0] = (previous << 1) | WMv[c];

        for (unsigned j = 1; j <= r; ++j, previous = temp)
            s[j] = previous & (previous << 1) & (s[j - 1] << 1) & (((temp = s[j]) << 1) | WMv[c]);

        if (!(s[r] & lim)) [[unlikely]] {
            if constexpr (!count)
                return 1;

            occ++;
        }
    }

    return occ;
}

void buildWuManber(const string& pat) {
    if (pat.size() < 64)
        return buildWuManber<int64_t>(pat, WM64);

#if defined(__GNUC__)
    else if (pat.size() < 128)
        return buildWuManber<int128_t>(pat, WM128);
#endif

}

unsigned WuManber(bool count, const string& txt, const string& pat, const unsigned r) {
    if (pat.size() < 64)
        return count ? WuManber< true, int64_t>(txt, pat, r, WM64)
                     : WuManber<false, int64_t>(txt, pat, r, WM64);

#if defined(__GNUC__)
    else if (pat.size() < 128)
        return count ? WuManber< true, int128_t>(txt, pat, r, WM128)
                     : WuManber<false, int128_t>(txt, pat, r, WM128);
#endif

    else
        return count ? WuManberV< true>(txt, pat, r)
                     : WuManberV<false>(txt, pat, r);
}
