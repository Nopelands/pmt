#ifndef MAIN_H
#define MAIN_H

#include <bitset>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

#define AB_SIZE 128

struct Occurance {
    unsigned index, pat_index;
};

// busca exata
extern void buildKMP(const string &pat);
extern void buildShiftOr(const string &pat);
extern void buildAho(const vector<string> &pats);

extern vector<Occurance> ahoCorasick(const string &txt, const vector<string> &pats);
extern vector<Occurance> BoyerMoore(const string &txt, const string &pat);
extern vector<Occurance> KnuthMorrisPratt(const string &txt, const string &pat);
extern vector<Occurance> ShiftOr(const string &txt, const string &pat);

// busca aproximada
extern void buildWuMamber(const string& pat);
extern void buildUkkonen(const string& pat, const unsigned r);

extern vector<Occurance> Sellers(const string &txt, const string &pat, const unsigned r);
extern vector<Occurance> Ukkonen(const string &txt, const string &pat, const unsigned r);
extern vector<Occurance> WuMamber(const string &txt, const string &pat, const unsigned r);

#endif