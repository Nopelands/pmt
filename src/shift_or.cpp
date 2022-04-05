#include "main.h"

int64_t SO64[AB_SIZE];

#if defined(__GNUC__)
int128_t SO128[AB_SIZE];
vector<int128_t> SOv[AB_SIZE];
#else
vector<int64_t> SOv[AB_SIZE];
#endif

template<typename intType>
void buildShiftOr(const string &pat, intType *SO) {

    memset(SO, -1, AB_SIZE * sizeof(intType));

    intType j = 1;
    for (uint8_t c : pat)
        SO[c] &= ~j, j <<= 1;
}

template<bool count, typename intType>
unsigned ShiftOr(const string &txt, const string &pat, intType *SO) {

    unsigned occ = 0;
    const intType lim = intType(1) << (pat.size() - 1);

    intType state = -1ULL;
    for (uint8_t c : txt) {
        state = (state << 1) | SO[c];

        if (!(state & lim)) [[unlikely]] {
            if constexpr (!count)
                return 1;

            occ++;
        }
    }

    return occ;
}

void buildShiftOrV(const string &pat) {

    unsigned vecSize = ((pat.size() - 1) / sizeInt) + 1;

    for (unsigned i = 0; i < AB_SIZE; ++i)
        SOv[i].assign(vecSize, bigInt(-1));

    vector<bigInt> j(vecSize, 0);
    j.back() = 1;

    for (uint8_t c : pat)
        SOv[c] &= ~j, j <<= 1;    
}

template<bool count>
unsigned ShiftOrV(const string &txt, const string &pat) {
    unsigned occ = 0;
    const bigInt lim = bigInt(1) << ((pat.size() - 1) % sizeInt);

    vector<bigInt> state(((pat.size() - 1) / sizeInt) + 1, bigInt(-1));
    for (uint8_t c : txt) {
        state = (state << 1) | SOv[c];

        if (!(state & lim)) [[unlikely]] {
            if constexpr (!count)
                return 1;

            occ++;
        }
    }

    return occ;
}

void buildShiftOr(const string &pat) {
    if (pat.size() < 64)
        return buildShiftOr<int64_t>(pat, SO64);

#if defined(__GNUC__)
    else if (pat.size() < 128)
        return buildShiftOr<int128_t>(pat, SO128);
#endif

    else
        return buildShiftOrV(pat);
}

unsigned ShiftOr(bool count, const string &txt, const string &pat) {
    if (pat.size() < 64)
        return count ? ShiftOr< true, int64_t>(txt, pat, SO64)
                     : ShiftOr<false, int64_t>(txt, pat, SO64);

#if defined(__GNUC__)
    else if (pat.size() < 128)
        return count ? ShiftOr< true, int128_t>(txt, pat, SO128)
                     : ShiftOr<false, int128_t>(txt, pat, SO128);
#endif
    else
        return count ? ShiftOrV< true>(txt, pat)
                     : ShiftOrV<false>(txt, pat);
}
