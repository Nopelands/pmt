#ifndef MAIN_H
#define MAIN_H

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

#define AB_SIZE 256

// busca exata
extern void buildBoyer(const string &pat);
extern void buildKMP(const string &pat);
extern void buildShiftOr(const string &pat);
extern void buildAho(const vector<string> &pats);

extern unsigned ahoCorasick(bool count, const string &txt);
extern unsigned BoyerMoore(bool count, const string &txt, const string &pat);
extern unsigned KnuthMorrisPratt(bool count, const string &txt, const string &pat);
extern unsigned ShiftOr(bool count, const string &txt, const string &pat);

// busca aproximada
extern void buildWuManber(const string& pat);
extern void buildUkkonen(const string& pat, const unsigned r);

extern unsigned Sellers(bool count, const string &txt, const string &pat, const unsigned r);
extern unsigned Ukkonen(bool count, const string &txt);
extern unsigned WuManber(bool count, const string &txt, const string &pat, const unsigned r);

#if defined(__GNUC__)
__extension__ typedef __int128_t int128_t;
constexpr int sizeInt = 128;
typedef int128_t bigInt;
#else
typedef int64_t bigInt;
constexpr int sizeInt = 64;
#endif

inline vector<bigInt> operator<<(const vector<bigInt> &v, unsigned shift) {
    vector<bigInt> ans(v.size());
    ans.back() = v.back() << shift;

    for (unsigned i = 0; i < v.size() - 1; ++i)
        ans[i] = (v[i] << shift) | (v[i + 1] >> (sizeInt - shift));

    return ans;
}

inline vector<bigInt> operator<<=(vector<bigInt> &v, unsigned shift) {
    return v = (v << shift);
}

inline vector<bigInt> operator&(const vector<bigInt> &v1, const vector<bigInt> &v2) {
    vector<bigInt> ans(v1.size());

    for (unsigned i = 0; i < v1.size(); ++i)
        ans[i] = v1[i] & v2[i];
    
    return ans;
}

inline vector<bigInt> operator|(const vector<bigInt> &v1, const vector<bigInt> &v2) {
    vector<bigInt> ans(v1.size());

    for (unsigned i = 0; i < v1.size(); ++i)
        ans[i] = v1[i] | v2[i];
    
    return ans;
}

inline vector<bigInt>& operator&=(vector<bigInt> &v1, const vector<bigInt> &v2) {
    return v1 = v1 & v2;
}

inline bool operator&(const vector<bigInt> &v1, const bigInt &b) {
    return v1[0] & b;
}

inline vector<bigInt> operator~(const vector<bigInt> &v) {
    vector<bigInt> ans(v.size());

    for (unsigned i = 0; i < v.size(); ++i)
        ans[i] = ~v[i];
    
    return ans;
}



#endif
